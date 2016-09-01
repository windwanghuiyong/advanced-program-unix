#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	MAXLINE	4096			/* max line length */

/**************************************
	实例 15-5	Page 432
		经由管道从父进程向子进程传送数据
***************************************/
int main(void)
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe(fd) < 0)
		perror("pipe error");
	if ((pid = fork()) < 0)
	{
		perror("fork error");
	}
	else if (pid > 0)
	{					/* parent */
		close(fd[0]);
		write(fd[1], "hello world\n", 12);
	}
	else
	{					/* child */
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
