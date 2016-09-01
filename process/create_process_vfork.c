#include "api.h"

int globvar = 0;
char buf[] = "a write to stdout\n";

int main(void)
{
	int autovar;
	pid_t pid;

	autovar = 0;
	printf("before vfork\n");

	if ((pid = vfork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{
		globvar++;
		autovar++;
		_exit(0);
	}

	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, autovar);
	exit(0);
}
