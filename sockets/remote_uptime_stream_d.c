#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <signal.h>

#include "prototype.h"
#include "macro.h"

/***********************************************************
    实例 16-17
        该服务器用来提供 uptime 命令的输出到客户端程序
    参数
        套接字类型, 通用套接字地址结构, 套接字地址长度, 请求数量
***********************************************************/
int main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;
	
	/* 服务器进程不需要任何参数 */
	if (argc != 1)
	{
		printf("usage: remote_uptime_daemon");
		exit(1);
	}
	/* 主机名最大长度 */
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
	{
		n = HOST_NAME_MAX;
	}
	/* 主机名动态分配内存 */
	if ((host = malloc(n)) == NULL)
	{
		perror("malloc error");
		exit(1);
	}
	/* 获取主机名 */
	if (gethostname(host, n) < 0)
	{
		perror("gethostname error");
		exit(1);
	}
	else
		printf("rusd: hostname =  %s\n", host);
	daemonize("ruptimed");
	
	/* 初始化链表结构 */
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags     = AI_CANONNAME;
	hint.ai_socktype  = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr      = NULL;
	hint.ai_next      = NULL;
	
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) 
	{
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) 
	{
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN)) >= 0) 
		{
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
}

void serve(int sockfd)
{
	int		clientfd;
	FILE	*fp;
	char	buf[BUFLEN];

	set_cloexec(sockfd);
	for (;;)
	{
		if ((clientfd = accept(sockfd, NULL, NULL)) < 0) 
		{
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
		set_cloexec(clientfd);
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) 
		{
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clientfd, buf, strlen(buf), 0);
		} 
		else 
		{
			while (fgets(buf, BUFLEN, fp) != NULL)
				send(clientfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(clientfd);
	}
}

/**********************
	使进程成为后台进程
**********************/
void daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;	// 资源限制
	struct sigaction sa;

	/* 清除文件创建掩模 */
	umask(0);

	/* 获取文件描述符最大数量 */
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		printf("%s: can't get file limit", cmd);
		exit(1);
	}

	/* Become a session leader to lose controlling TTY */
	if ((pid = fork()) < 0)
	{
		printf("%s: can't fork", cmd);
		exit(1);
	}
	else if (pid != 0) /* parent */
	{
		exit(0);	// 使父进程终止，让Daemon在子进程中后台执行
	}
	
	setsid();		// 使进程成为会话组长

	/* Ensure future opens won't allocate controlling TTYs */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
	{
		printf("%s: can't ignore SIGHUP", cmd);
		exit(1);
	}
	if ((pid = fork()) < 0)
	{
		printf("%s: can't fork", cmd);
		exit(1);
	}
	else if (pid != 0) /* parent */
		exit(0);

	/*
	 * Change the current working directory to the root so
	 * we won't prevent file systems from being unmounted.
	 */
	if (chdir("/") < 0)
	{
		printf("%s: can't change directory to /", cmd);
		exit(1);
	}

	/* Close all open file descriptors */
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/* Attach file descriptors 0, 1, and 2 to /dev/null */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/* Initialize the log file */
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
		  fd0, fd1, fd2);
		exit(1);
	}
}

int set_cloexec(int fd)
{
	int		val;

	if ((val = fcntl(fd, F_GETFD, 0)) < 0)
		return(-1);

	val |= FD_CLOEXEC;		/* enable close-on-exec */

	return(fcntl(fd, F_SETFD, val));
}
