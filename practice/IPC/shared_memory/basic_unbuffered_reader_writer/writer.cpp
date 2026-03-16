#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<iostream>
int main()
{
    //create the key_t key for accessing shared memory
    key_t shmkey=ftok("shmfile", 69);
    /*
    What's going on?
    ftok() returns a key for accessing shared memory. But a simple integer is far too non-unique for multiple different shared memory segments
    to be uniquely identified by an integer. So ftok() hashes together the inode value of a file and this integer(called a project identifier)
    to make sure that there is a sufficiently large pool of shmkeys that can be generated. Also, for two processes to access the same
    shared memory (by extension, have the same key), as long as they both have the same file passed to ftok and the same project identifier,
    ftok() will return the correct shmkey.
    */
   //now the shmkey is for the programmer to use, but shmid is a kernel internel identifier. THe kernel uses it to distinguish regions
   //of shared memory.
   int shmid=shmget(shmkey, 1024, 0666|IPC_CREAT);
   //0666-> binary 110 110 110, rw-rw-rw-, appended with the IPC_CREAT flag. So the shared memory segment created
   //so IPC_CREAT Is to create the segment, and 0666 is the read write permissions to be provided. 
   char *str=(char *)shmat(shmid, NULL, 0);
   //shmat attaches the created shared memory segment. 
   //It returns a pointer to the region of shared memory created.
   //the second argument is the address, you can specify a particular address to place the shared memory segment in.
   //Third argument is flags of which we need one. 
   //Now str 8s a pointer to the shared memory reagion with the shmid you you got. 
   std::cout<<"Enter the string to pass: ";
   std::cin.getline(str, 100);//not readline
   shmdt(str);//the new address of the shared memory segment was str.
   return 0;
}