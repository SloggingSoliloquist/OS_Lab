//The objective of this piece of code is to understand what actually gets copied to the child process
//when it is created by forking the parent process
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
int main()
{
    int local_x = 10;
    pid_t pid = fork();
    if(pid==-1){std::cout<<"Fork failed\n";}
    else if(pid==0){
        std::cout<<"x before updation(child): "<<local_x<<std::endl;
        local_x++;
        std::cout<<"x after updation(child): "<<local_x<<std::endl;
        std::cout<<"child pid: "<<getpid()<<std::endl;
        std::cout<<"child's parent's pid: "<<getppid()<<std::endl;
        exit(12);
    }
    else{
        //parent process
        std::cout<<"parent pid: "<<getpid()<<std::endl;
        std::cout<<"x before updation(parent): "<<local_x<<std::endl;
        local_x++;
        std::cout<<"x after updation(parent): "<<local_x<<std::endl;
        int status;
        pid_t returning_pid=wait(&status);//this status is encoded, so you won't get 12 as status, 
        //but the returning_pid will match the child pid
        std::cout<<"Returned status: "<<status<<std::endl; //encoded, so not the actual returned value
        std::cout<<"Returned status actual value: "<<WEXITSTATUS(status)<<std::endl;//WEXITSTATUS is the macro to get the actual status
        std::cout<<returning_pid<<std::endl;
    }
    return 0;
}