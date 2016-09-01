#include <pthread.h>
#include <stdio.h>

void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
}

void *thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");

	// if (arg)					// 返回, 不会调用清理处理程序
	// 	return((void *)1);

	pthread_cleanup_pop(0);
	printf("a\n");
	pthread_cleanup_pop(0);
	printf("b\n");
	return((void *)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");

	if (0)
	// if (arg)						//退出, 会调用清理处理程序
	{
		printf("e\n");
		pthread_exit((void *)2);
		printf("f\n");
	}

	pthread_cleanup_pop(0);
	printf("c\n");
	pthread_cleanup_pop(0);
	printf("d\n");
	pthread_exit((void *)2);
}

int pthread_cleanup_handler(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	pthread_create(&tid2, NULL, thr_fn2, (void *)2);
	pthread_join(tid1, &tret);
	printf("thread 1 exit code %ld\n", (long)tret);
	pthread_join(tid2, &tret);
	printf("thread 2 exit code %ld\n", (long)tret);
	return 0;
}
