#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int Resource = 0;
pthread_mutex_t Mutex;

void *producer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&Mutex);
        if (Resource == 0)
        {
            Resource += 5;
			printf("producer\n");
        }
        pthread_mutex_unlock(&Mutex);
        sleep(5);
    }
    return NULL;
}

void *consumer(void *arg)
{
	int t = *(int *)arg;
    while (1)		// 在生产者解锁的5s期间，不断地进行加锁和解锁，互斥地执行，造成资源浪费
    {
		// printf("%d: lock\n", t);
        pthread_mutex_lock(&Mutex);
        if (Resource > 0)
        {
            Resource--;
			printf("%d: consumer\n", t);
        }
		// printf("%d: unlock\n", t);
        pthread_mutex_unlock(&Mutex);
        sleep(1);
    }
    return NULL;
}

//主函数
int main()
{
	void		*retval;
    pthread_t	tid_p;
	pthread_t	tid_c1, tid_c2, tid_c3;
	int			p[3] = {1, 2, 3};
    
    pthread_mutex_init(&Mutex, NULL);
    
    pthread_create(&tid_p,  NULL, producer, NULL);
	
	/* 消费者会进行竞争 */
    pthread_create(&tid_c1, NULL, consumer, &p[0]);
	pthread_create(&tid_c2, NULL, consumer, &p[1]);
	pthread_create(&tid_c3, NULL, consumer, &p[2]);

    pthread_join(tid_p,  &retval);
	printf("retval = %d\n", *(int *)retval);
    pthread_join(tid_c1, &retval);
	printf("retval = %d\n", *(int *)retval);
	pthread_join(tid_c2, &retval);
	printf("retval = %d\n", *(int *)retval);
    pthread_join(tid_c3, &retval);
	printf("retval = %d\n", *(int *)retval);

    return 0;
}
