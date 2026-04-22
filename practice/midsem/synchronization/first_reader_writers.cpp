#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<thread>
#include<unistd.h>
#include<vector>
sem_t rw_mutex;
sem_t mutex;

int shared_data=0;
int num_readers=0;
void writer(){
    do{
        sem_wait(&rw_mutex);
        shared_data++;
        sem_post(&rw_mutex);
    }while(true);
}

void reader(int reader_id){
    do{
        sem_wait(&mutex);
        num_readers++;
        if(num_readers==1){
            sem_wait(&rw_mutex);//only the first reader checks if writer is writing or not
        }
        sem_post(&mutex);
        // take 2 seconds to read
        std::cout<<"Reader "<<reader_id<<" is reading the value "<<shared_data<<std::endl;
        sleep(2);
        sem_wait(&mutex);
        num_readers--;
        if(num_readers==0){
            sem_post(&rw_mutex);//no readers->writer can write if it wants
        }
        sem_post(&mutex);
    }while(true);
}

int main(){
    sem_init(&rw_mutex, 0,1);
    sem_init(&mutex, 0,1);


    std::vector<std::thread> readers;
    for(int i=0; i<5; i++){
        readers.emplace_back(reader, i);
    }
    std::thread writer_thread(writer);
    writer_thread.join();
    for(auto &reader:readers){
        reader.join();
    }
}