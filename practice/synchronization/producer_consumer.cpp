#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<vector>
#include<thread>
#include<semaphore.h>
#include<queue>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
const int BUFFER_LEN =4;
sem_t full;
sem_t empty;//declare them here and initalize them later
std::queue<int> buffer;
void consume(){
    int el;
    do{
    std::cout<<"Consumer is waiting to consume...\n";
    //first acquire the semaphore empty
    sem_wait(&full);
    //once you acquire the semaphore, acquire the mutex to access the shared buffer.
    //Pop an element out of the buffer
    pthread_mutex_lock(&mutex);
    el = buffer.front();
    buffer.pop();
    sem_post(&empty);
    std::cout<<"Consumed "<<el<<std::endl;
    pthread_mutex_unlock(&mutex);
    }while(el!=-1);
}
void produce(){
    for(int i=8; i>-2; i--){
    //first acquire the semaphore empty
    sem_wait(&empty);
    //once you acquire the semaphore, acquire the mutex to access the shared buffer.
    //Pop an element out of the buffer
    pthread_mutex_lock(&mutex);
    buffer.push(i);
    std::cout<<"Produced "<<i<<std::endl;
    sem_post(&full);
    pthread_mutex_unlock(&mutex);
    //done lol
    }
}
int main()
{
    //Two threads, reader and writer
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_LEN);
    std::thread consumer(consume);
    std::thread producer(produce);

    consumer.join();
    producer.join();
    return 0;

}