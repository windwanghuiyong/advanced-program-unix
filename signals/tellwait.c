#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;	// 信号屏蔽字

static void sigusr_handler(int signo)	/* one signal handler for SIGUSR1 and SIGUSR2 */
{
	sigflag = 1;
}

void initSigSetHandler(void)
{
	/* 设置信号处理程序 */
	if (signal(SIGUSR1, sigusr_handler) == SIG_ERR)
		perror("signal(SIGUSR1) error");
	
	if (signal(SIGUSR2, sigusr_handler) == SIG_ERR)
		perror("signal(SIGUSR2) error");
	
	sigemptyset(&zeromask);
	
	/* 初始化信号集 newmask, 并添加 SIGUSR1 和 SIGUSR1 到信号集*/
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* Block SIGUSR1 and SIGUSR2, and save current signal mask */
	
	/* 添加希望阻塞的信号 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		perror("SIG_BLOCK error");
}

void tellParent(pid_t pid)
{
	kill(pid, SIGUSR2);		/* tell parent we're done */
}

void waitParent(void)
{
	while (sigflag == 0)
		sigsuspend(&zeromask);	/* and wait for parent */
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");
}

void tellChild(pid_t pid)
{
	kill(pid, SIGUSR1);			/* tell child we're done */
}

void waitChild(void)
{
	while (sigflag == 0)
		sigsuspend(&zeromask);	/* and wait for child */
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");
}
