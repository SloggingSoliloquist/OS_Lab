#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<semaphore.h>
#include<vector>
#include<thread>
#include<unistd.h>
sem_t pool_sem;
const int NUM_WORKERS=10;
const int NUM_RESOURCES=3; //This is the actual value of the semaphre
//Uuse const int instead of define because most functions require integer values

void access_resource(int worker_id){
    std::cout<<"Worker "<<worker_id<<" is waiting for the resource\n";
    sem_wait(&pool_sem);
    //you enter this section once the semaphore is acquired
    std::cout<<"Worker "<<worker_id<<" acquired resource\n";
    sleep(2);
    sem_post(&pool_sem);//release the acquired semaphore
    std::cout<<"Worker "<<worker_id<<" released resource\n";
}

int main(){
    sem_init(&pool_sem, 0, NUM_RESOURCES);
    //create an empty vector of threads
    std::vector<std::thread> workers;
    for(int i=0; i<NUM_WORKERS; i++){
        workers.emplace_back(access_resource, i);
    }
    //wait for all threads to join
    for(auto &thread:workers){//you have to access the threads by reference
        thread.join();
    }
    return 0;
}