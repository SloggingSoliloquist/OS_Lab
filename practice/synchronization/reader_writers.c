#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include<unistd.h>

sem_t mutex;
sem_t rw_mutex;
int rc = 0;
int data = 0;
void *reader(void *arg)
{
    do
    {
        sem_wait(&mutex);
        rc++;
        if (rc == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);

        printf("Reader reading data: %d\n",data);
        sleep(1);
        sem_wait(&mutex);
        rc--;
        if (rc == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);
    }while(1);
}

void *writer(void *arg)
{
    do
    {
        sem_wait(&rw_mutex);
        printf("Writing data: %d\n",data);
        data++;
        sleep(1);
        sem_post(&rw_mutex);
    } while (1);
}

int main()
{
    pthread_t r,w;
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0 ,1);
    pthread_create(&r,NULL,reader,NULL);
    pthread_create(&w,NULL,writer,NULL);
    pthread_join(r,NULL);
    pthread_join(w,NULL);
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
}