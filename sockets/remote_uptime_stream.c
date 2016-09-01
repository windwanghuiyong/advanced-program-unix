#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#include "prototype.h"
#include "macro.h"

/********************************************
	实例 16-16
		用于从服务器获取正常运行时间的客户端命令
********************************************/
int main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, errno_tmp;

	if (argc != 2)
	{
		printf("usage: ruptime hostname\n");
		exit(1);
	}
	
	/* 初始化链表结构 */
	memset(&hint, 0, sizeof(hint));
	hint.ai_socktype  = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr      = NULL;
	hint.ai_next      = NULL;
	
	if ((errno_tmp = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
	{
		printf("getaddrinfo error: %s\n", gai_strerror(errno_tmp));
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) 
	{
		if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0, aip->ai_addr, aip->ai_addrlen)) < 0) 
		{
			errno_tmp = errno;
		} 
		else 
		{
			print_uptime(sockfd);
			exit(0);
		}
	}
	printf("can't connect to %s", argv[1]);
	exit(1);
}

/**********************************
	从字节流套接字(面向连接)接收数据
**********************************/
void print_uptime(int sockfd)
{
	int		n;
	char	buf[BUFLEN];

	while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0)
	{
		write(STDOUT_FILENO, buf, n);
	}
	if (n < 0)
	{
		perror("recv error");
		exit(1);
	}
}
