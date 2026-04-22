#include<iostream>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<fcntl.h> //needed for flags like O_CREAT, O_WRONLY etc.
#include<unistd.h>
#include<semaphore.h>
struct SharedData{
    int val;
};

int main(){
    key_t shmkey = ftok("shmfile", 69);
    int shmid=shmget(shmkey, sizeof(SharedData), 0666|IPC_CREAT);//NOT O_CREAT
    SharedData *data= (SharedData *)shmat(shmid,NULL, 0);
    sem_unlink("/semaphore_file");  //if the semaphore persists in memory it might cause problems
    //between runs
    sem_t *semaphore=sem_open("/semaphore_file", O_CREAT, 0666, 1);//this gives you a pointer 
    //to the semaphore file created
    data->val=0;
    while(true){
        sem_wait(semaphore);//sem_wait requires a pointer to the semaphore
        data->val++;
        std::cout<<"Writer wrote value: "<<data->val<<std::endl;
        sem_post(semaphore);
    }
    sem_unlink("/semaphore_file");
shmctl(shmid, IPC_RMID, NULL);
    shmdt(data);
    return 0;
}