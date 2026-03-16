#include<unistd.h>
#include<iostream>
#include<sys/types.h>
int main(){
    int pipefd[2];
    pipe(pipefd);//this creates a pipe. Now when this process creates a child, the child process will inherit this pipe as well (cos its a file)
    pid_t pid = fork();
    if(pid==-1){
        std::cout<<"Fork failed\n";
    }
    else if(pid==0){
        close(pipefd[1]);
        char buffer[100];
        read(pipefd[0], buffer, 100*sizeof(char));
        std::cout<<"Child received: "<<buffer<<std::endl;
        close(pipefd[0]);
    }
    else{
        close(pipefd[0]);
        write(pipefd[1], "Hello", sizeof("Hello"));
        close(pipefd[1]);
    }
}