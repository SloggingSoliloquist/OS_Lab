#include<iostream>
#include<semaphore.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
int i=0;
struct SharedData{
    int in;
    int out;
    int buffer[5];
    sem_t full;
    sem_t empty;
    sem_t mutex;
};
int main(){
    key_t key =ftok("somefile", 10);
    SharedData *data;
    int shmid= shmget(key, sizeof(SharedData), 0666|IPC_CREAT);
    data=(SharedData *)shmat(shmid, NULL, 0);
    data->in=0;
    data->out=0;
    sem_init(&data->full, 1, 0);
    sem_init(&data->empty, 1, 5);
    sem_init(&data->mutex, 1, 1);
    while(true){
        sem_wait(&data->empty);
        sem_wait(&data->mutex);
        //produce
        data->buffer[data->in]=i;
        i=(i+1)%10;
        data->in=(data->in +1)%5;
        std::cout<<"Produced  "<<i<<std::endl;
        sleep(2);
        sem_post(&data->mutex);
        sem_post(&data->full);
    }
    shmctl(shmid, IPC_RMID, NULL);
    shmdt(data);
    return 0;
}