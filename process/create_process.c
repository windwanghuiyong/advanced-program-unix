#include <unistd.h>
#include <stdlib.h>

#include "stdio.h"

#include "error_handing.h"
#include "console_color.h"

char buf[] = "a write to stdout\n";

int globvar = 0;		/* external variable in initialized data */

/************************************
    实例 8-1 使用 fork 函数创建新进程
************************************/
void create_process(void)
{
	int		autovar;		/* automatic variable on the stack */
	pid_t	pid;

	autovar = 0;

	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		prt_err("write error");

	/* 父进程数据空间复制到子进程中, 即此打印会复制到子进程*/
	printf("before fork\n");	/* we don't flush stdout */

	if ((pid = fork()) < 0)
		prt_err("fork error");
	else if (pid == 0)			/* child process */
	{
		printf(YELLOW"child process\n"GRAY);
		globvar++;				/* modify variables */
		autovar++;
	}
	else
	{
		sleep(2);				/* parent process */
		printf(YELLOW"parent process\n"GRAY);
	}
	printf("pid = %ld, globvar = %d, autovar = %d\n", (long)getpid(), globvar, autovar);
}

/***********************************
    实例 1-6 打印进程 ID
************************************/
int print_processid()
{
    printf("hello world from process ID %ld\n", (long)getpid());
    return 0;
}

int print_uid_gid(void)
{
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	return 0;
}
