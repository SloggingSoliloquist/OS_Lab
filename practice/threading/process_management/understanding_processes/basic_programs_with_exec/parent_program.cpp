#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t pid=fork();
    if(pid==-1) std::cout<<"Fork failed\n";
    else if(pid==0){
        char *args[]={(char*)"banana", (char*)"you're dumb", (char*)"I'm not exaggerating",(char*)"how did you get this far lol", NULL};
        execv("./child", args);
        std::cout<<"exec failed"<<std::endl;
        return 0;
    }
    else{
        int status;
        pid_t returning_process=wait(&status);
        if(WIFEXITED(status)){
            std::cout<<"Child process exited with status "<<WEXITSTATUS(status)<<std::endl;
        }
    }
}