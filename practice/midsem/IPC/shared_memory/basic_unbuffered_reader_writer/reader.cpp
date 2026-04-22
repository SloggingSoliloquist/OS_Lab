#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<iostream>
#include<cstring>

int main(){
    key_t shmkey = ftok("shmfile", 69);
    //pass same filename and project identifier.
    int shmid= shmget(shmkey, 1024, 0666);
    char *read_str= (char*)shmat(shmid, NULL, 0);
    std::cout<<read_str;
    shmdt(read_str);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}