#include<iostream>
#include<semaphore.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>

struct SharedData{
    int val;
};

int main(){
    key_t key= ftok("shmfile", 69);
    int shmid= shmget(key, sizeof(SharedData), 0666);
    SharedData *data= (SharedData *)shmat(shmid, NULL, 0);

    sem_t *semaphore = sem_open("/semaphore_file", 0);

    while(true){
        sem_wait(semaphore);
        std::cout<<"Reader read value: "<<data->val;
        sem_post(semaphore);
    }
    shmdt(data);
    return 0;
}