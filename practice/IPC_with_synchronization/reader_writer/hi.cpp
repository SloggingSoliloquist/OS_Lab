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
int main(){    key_t shmkey = ftok("shmfile", 69);

        int shmid=shmget(shmkey, sizeof(SharedData), 0666|IPC_CREAT);
    shmctl(shmid, IPC_RMID, NULL);
}