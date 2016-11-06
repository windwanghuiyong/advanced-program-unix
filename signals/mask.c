#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>  
#include <unistd.h>  

/******************************************
	实例 10-4
		为进程打印信号屏蔽字
******************************************/
void print_mask(const char *str)
{
	sigset_t	sigset;
	int			errno_sv;

	errno_sv = errno;		/* we can be called by signal handlers */
	if (sigprocmask(0, NULL, &sigset) < 0) 
	{
		perror("sigprocmask error");
		exit(1);
	} 
	else 
	{
		printf("%s", str);
		if (sigismember(&sigset, SIGINT))
			printf(" SIGINT");
		if (sigismember(&sigset, SIGQUIT))
			printf(" SIGQUIT");
		if (sigismember(&sigset, SIGUSR1))
			printf(" SIGUSR1");
		if (sigismember(&sigset, SIGALRM))
			printf(" SIGALRM");

		/* remaining signals can go here  */

		printf("\n");
	}

	errno = errno_sv;		/* restore errno */
}
