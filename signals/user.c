#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void	sigusr_handler(int);	/* one handler for both signals */

/******************************************
	实例 10-2
		捕捉 SIGUSR1 和 SIGUSR2 的简单程序
******************************************/
int signal_handler(void)
{
	if (signal(SIGUSR1, sigusr_handler) == SIG_ERR)
		perror("can't catch SIGUSR1");
	
	if (signal(SIGUSR2, sigusr_handler) == SIG_ERR)
		perror("can't catch SIGUSR2");
	
	for ( ; ; )
		pause();
}

static void sigusr_handler(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received signal %d\n", signo);
}
