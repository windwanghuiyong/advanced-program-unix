#include "api.h"
#include <sys/wait.h>

void print_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
			WCOREDUMP(status) ? "(core file generated)" : "";
#else
			"");
#endif
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int print_exit_status(void)
{
	pid_t pid;
	int status;

/*****************************/

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		printf("pid4 = %d\n", pid);
		exit(7);						// 正常终止
	}

	sleep(2);
	printf("pid1 = %d\n", pid);
	if (wait(&status) != pid)
		err_sys("wait error");
	print_exit(status);

/*****************************/

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		printf("pid5 = %d\n", pid);
		abort();						// 异常终止
	}

	printf("pid2 = %d\n", pid);
	if (wait(&status) != pid)
		err_sys("wait error");
	print_exit(status);

/*****************************/

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		printf("pid6 = %d\n", pid);
		status /= 0;					// 异常终止
	}

	printf("pid3 = %d\n", pid);
	if (wait(&status) != pid)
		err_sys("wait error");
	print_exit(status);

/*****************************/

	return 0;
}
