#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* 初始化读写锁 */
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
/* 全局资源 */
int Number = 10;

/* 读锁线程函数 */
void *thread_read_lock(void *arg)
{
    char *pthr_name = (char *)arg;

    while (1)
    {
        /* 获取读锁 */
        pthread_rwlock_rdlock(&rwlock);
		printf("%s: enter\n", pthr_name);
        
		/* 读操作 */
		printf("Number = %d\n", Number);
		sleep(1);
        
        /* 解除读锁 */
		printf("%s: leave\n\n", pthr_name);
		pthread_rwlock_unlock(&rwlock);

        sleep(1);
    }

    return NULL;
}

/* 写锁线程函数 */
void *thread_write_lock(void *arg)
{
    char *pthr_name = (char *)arg;

    while (1)
    {
        /* 获取写锁 */
        pthread_rwlock_wrlock(&rwlock);
		printf("%s: enter\n", pthr_name);
		
        /* 写操作 */
        printf("Number = %d\n", ++Number);
        sleep(1);

        /* 解除写锁 */
		printf("%s: leave\n\n", pthr_name);
        pthread_rwlock_unlock(&rwlock);
		
        sleep(2);	//写操作间隔时间，读操作应利用这个时间空隙进行
    }

    return NULL;
}

int main(void)
{
    pthread_t tid_read_1, tid_read_2, tid_write_1, tid_write_2;

    /* 创建4个线程，2个读，2个写 */
    if (pthread_create(&tid_read_1, NULL, thread_read_lock, "read_1") != 0)
        perror("create tid_read_1");

    if (pthread_create(&tid_read_2, NULL, thread_read_lock, "read_2") != 0)
        perror("create tid_read_2");

    if (pthread_create(&tid_write_1, NULL, thread_write_lock, "write_1") != 0)
        perror("create tid_write_1");

    if (pthread_create(&tid_write_2, NULL, thread_write_lock, "write_2") != 0)
        perror("create tid_write_2");

    /* 随便等待一个线程，防止main结束 */
    if (pthread_join(tid_read_1, NULL) != 0)
        perror("pthread_join()");

    return 0;
}
