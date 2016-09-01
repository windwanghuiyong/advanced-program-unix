#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t	Mutex;
sem_t			Cnt;

void *consumer(void *arg)
{
	int id = *(int *)arg;
    while (1)
    {
        sem_wait(&msg_cnt);
        printf("c%d\n", id);
		sleep(1);
    }
    return NULL;
}

void *producer(void *arg)
{
	int id = *(int *)arg;
    while (1)
    {
        printf("p%d\n", id);   
        pthread_mutex_unlock(&Mutex);
        sem_post(&msg_cnt);
		sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid_c1, tid_c2, tid_c3, tid_p;
    void *retval;
	int p[3] = {1, 2, 3};
    
    pthread_mutex_init(&Mutex, NULL);
    pthread_mutex_init(&Mutex, NULL);
    
    sem_init(&Cnt, 0, 10);
    
    pthread_create(&tid_p,  NULL, producer, &p[0]);
    pthread_create(&tid_c1, NULL, consumer, &p[0]);
	pthread_create(&tid_c2, NULL, consumer, &p[1]);
	pthread_create(&tid_c3, NULL, consumer, &p[2]);
    
    pthread_join(tid_p, &retval);
    return 0;
}
