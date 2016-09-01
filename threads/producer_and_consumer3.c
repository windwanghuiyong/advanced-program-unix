#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t			Mutex;
pthread_mutexattr_t		MutexAttr;
pthread_cond_t			Cond = PTHREAD_COND_INITIALIZER;
int Resource = 0;

void *producer(void *arg)
{
	int id = *(int *)arg;
    while (1)
    {
        pthread_mutex_lock(&Mutex);
        Resource += 1;
		printf("p%d: signal\n", id);
		pthread_cond_signal(&Cond);
        pthread_mutex_unlock(&Mutex);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
	int id = *(int *)arg;
	while (1)
    {
        pthread_mutex_lock(&Mutex);
		pthread_cond_wait(&Cond, &Mutex);
        if (Resource > 0)
        {
            Resource--;
            printf("c%d: %d\n", id, Resource);
        }
		pthread_mutex_unlock(&Mutex);
        sleep(1);
    }
	return NULL;
}

int main(void)
{
	int p[3] = {1, 2, 3};
	void *retval;
    pthread_t tid_p;
	pthread_t tid_c1, tid_c2, tid_c3;

    if (pthread_mutexattr_init(&MutexAttr) == -1)
        perror("pthread_mutexattr_init error");

    if (pthread_mutexattr_settype(&MutexAttr, PTHREAD_MUTEX_NORMAL) == -1)
        perror("pthread_mutexattr_settype error");

    if (pthread_mutex_init(&Mutex, &MutexAttr) == -1)
        perror("pthread_mutex_init error");
	
    if (pthread_create(&tid_p, NULL, producer, &p[0])== -1)
        perror("pthread_create error");
	
    if (pthread_create(&tid_c1, NULL, consumer, &p[0])== -1)
        perror("pthread_create error");
	
    if (pthread_create(&tid_c2, NULL, consumer, &p[1])== -1)
        perror("pthread_create error");
	
    if (pthread_create(&tid_c3, NULL, consumer, &p[2])== -1)
        perror("pthread_create error");
	
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
