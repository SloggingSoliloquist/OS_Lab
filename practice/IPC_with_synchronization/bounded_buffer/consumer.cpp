#include<iostream>
#include<semaphore.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
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
    int shmid= shmget(key, sizeof(SharedData), 0666);
    data=(SharedData *)shmat(shmid, NULL, 0);
    while(true){
        sem_wait(&data->full);
        sem_wait(&data->mutex);
        //produce
        std::cout<<"read  "<<data->buffer[data->out]<<std::endl;
        data->out=(data->out +1)%5;
        sleep(2);
        sem_post(&data->mutex);
        sem_post(&data->empty);
    }
    shmdt(data);
    return 0;
}