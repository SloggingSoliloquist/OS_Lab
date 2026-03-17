#include<iostream>
#include<thread>
#include<sys/types.h>
#include<pthread.h>
int shared_counter=0;
pthread_mutex_t counter_mutex=PTHREAD_MUTEX_INITIALIZER;
//the mutex primitive is in the pthread library
//need to get the native handle of the thread to be able to use it
void increment_counter(){
    pthread_mutex_lock(&counter_mutex);
    shared_counter++;
    std::cout<<shared_counter<<std::endl;
    pthread_mutex_unlock(&counter_mutex);
}

void decrement_counter(){
    pthread_mutex_lock(&counter_mutex);
    shared_counter--;
    std::cout<<shared_counter<<std::endl;
    pthread_mutex_unlock(&counter_mutex);
}

int main()
{
    std::thread t1(increment_counter);
    std::thread t2(decrement_counter);

    t1.join();
    t2.join();
    return 0;

}