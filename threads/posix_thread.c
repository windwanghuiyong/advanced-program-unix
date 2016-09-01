#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "posix_thread.h"
#include "error_handing.h"

pthread_t new_thread_id;

int pthread_support(void)
{
	/* featrue test macros */
	#ifdef _POSIX_THREADS
	printf("_POSIX_THREADS = %ld\n", _POSIX_THREADS);
	#endif
	/* limits */
	long pthread_version = sysconf(_SC_THREADS);
	printf("pthread_version = %ld\n", pthread_version);
	return 0;
}

void print_thread_ids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid = %lu tid = %lu (0x%lx) \n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void main_thread_task(void)
{
	print_thread_ids("main thread: ");
	printf("m: main thread new_thread_id = %lu\n", (unsigned long)new_thread_id);
}

void *new_thread_task(void *arg)
{
	print_thread_ids("new thread: ");
	printf("n: new_thread_id = %lu\n", (unsigned long)new_thread_id);	// 如果线程还未创建完, 即线程 ID 还未被赋值,则这里可能是错误的值
	printf("n: arg = %s\n", (char *)arg);
	return ((void *)0);
}

void *thread_function1()
{
	printf("thread 1 returning\n");
	return ((void *)1);
}

void *thread_function2()
{
	printf("thread 2 exiting\n");
	pthread_exit((void *)2);
}

int thread_handing()
{
	int err;
	pthread_t tid1, tid2;
	void *thread_rtn;
	char *str = "new thread argument";
	void *net_thread_arg = str;

	pthread_create(&new_thread_id, NULL, new_thread_task, net_thread_arg);
	sleep(1);	// 防止新线程还未执行时,主进程就终止了
	main_thread_task();

	err = pthread_create(&tid1, NULL, thread_function1, NULL);
	if (err != 0)
		prt_err("can't create thread 1");

	err = pthread_create(&tid2, NULL, thread_function2, NULL);
	if (err != 0)
		prt_err("can't create thread 2");

	err = pthread_join(tid1, &thread_rtn);
	if (err != 0)
		prt_err("can't join with thread 1");
	printf("thread 1 exit code %ld\n", (long)thread_rtn);

	err = pthread_join(tid2, &thread_rtn);
	if (err != 0)
		prt_err("can't join with thread 2");
	printf("thread 2 exit code %ld\n", (long)thread_rtn);

	exit (0);
	// return 0;
}
