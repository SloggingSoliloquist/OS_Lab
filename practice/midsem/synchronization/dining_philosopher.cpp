#include<iostream>
#include<vector>
#include<pthread.h>
#include<thread>
#include<semaphore.h>
#include<unistd.h>

//mutexes for all the forks
const int NUM_PHILOSOPHERS=5;
pthread_mutex_t forks[NUM_PHILOSOPHERS];
//semaphore to enture only 4 philosopher eat at a time
sem_t p_sem;

void philosopher(int id){
    int left=id;
    int right = (id+1)%NUM_PHILOSOPHERS;
    while(true){
        //before picking up fork check if 4 philosophers are already eating
        std::cout<<"Philosopher "<<id+1<<" is thinking..."<<std::endl;
        sleep(2);
        sem_wait(&p_sem);

        //now pick up forks. Need to acquire the mutex lock for each
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);
        //eat
        std::cout<<"Philosopher "<<id+1<<" is eating"<<std::endl;
        sleep(5);
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        sem_post(&p_sem);
    }
}

int main(){
    sem_init(&p_sem, 0, 4);
    for(auto &fork:forks){
        pthread_mutex_init(&fork, NULL);
    }
    std::vector<std::thread> philosophers;
    for(int i=0; i<5; i++){
        philosophers.emplace_back(philosopher, i);
}
for(auto &p:philosophers){
    p.join();
}

}