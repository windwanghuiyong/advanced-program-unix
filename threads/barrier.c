#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* 屏障总数 */
#define PTHREAD_BARRIER_SIZE 4

/* 定义屏障 */
pthread_barrier_t barrier;

void *thread_fun(void *arg)
{
    int result;
    char *thr_name = (char *)arg;
	
	sleep(1);
    /* something work */

    printf("%s: done\n", thr_name);

    /* 等待屏障 */
    result = pthread_barrier_wait(&barrier);
    if (result == PTHREAD_BARRIER_SERIAL_THREAD)
        printf("%s: return first\n", thr_name);
    else if (result == 0)
        printf("%s: return 0\n", thr_name);

    return NULL;
}

int main(void)
{
    pthread_t tid_1, tid_2, tid_3;

    /* 初始化屏障 */
    pthread_barrier_init(&barrier, NULL, PTHREAD_BARRIER_SIZE);

    if (pthread_create(&tid_1, NULL, thread_fun, "1") != 0)
        perror("create thread 1");

    if (pthread_create(&tid_2, NULL, thread_fun, "2") != 0)
        perror("create thread 2");

    if (pthread_create(&tid_3, NULL, thread_fun, "3") != 0)
        perror("create thread 3");

    /* 主线程等待工作完成 */
    pthread_barrier_wait(&barrier);
    printf("all done\n");

    sleep(1);
    return 0;
}
