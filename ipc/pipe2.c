#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define	MAXLINE		4096				/* max line length */
#define	DEF_PAGER	"/usr/bin/more"		/* default pager program */

/*************************************
	实例 15-6 Page 433
		将文件复制到分页程序
	功能
		每次一页地显示已产生的输出
	实现方式
		通过管道将输出直接送到分页程序
*************************************/
int main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if (argc != 2)
	{
		printf("usage: a.out <pathname>");
		exit(1);
	}

	if ((fp = fopen(argv[1], "r")) == NULL)
		perror("fopen error");

	if (pipe(fd) < 0)
		perror("pipe error");

	if ((pid = fork()) < 0)
	{
		perror("fork error");
	}

	/* parent */
	else if (pid > 0)
	{
		close(fd[0]);		/* close read end */

		/* parent copies argv[1] to pipe */
		while (fgets(line, MAXLINE, fp) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				perror("write error to pipe");
		}
		if (ferror(fp))
			perror("fgets error");

		close(fd[1]);	/* close write end of pipe for reader */

		if (waitpid(pid, NULL, 0) < 0)
			perror("waitpid error");
		exit(0);
	}

	/* child */
	else
	{
		close(fd[1]);	/* close write end */

		/* 子进程的标准输入作为管道的读端 */
		if (fd[0] != STDIN_FILENO)
		{
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				perror("dup2 error to stdin");
			close(fd[0]);	/* don't need this after dup2 */
		}

		/* get arguments for execl() */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* step past rightmost slash */
		else
			argv0 = pager;	/* no slash in pager */

		/* 执行分页程序 */
		if (execl(pager, argv0, (char *)0) < 0)
			 perror("execl error");
	}
	exit(0);
}
