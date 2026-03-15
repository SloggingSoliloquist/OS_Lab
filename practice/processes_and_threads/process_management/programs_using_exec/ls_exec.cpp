#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
#include<vector>
#include<string>

int main()
{
    pid_t pid=fork();
    if(pid==0){
        const char *args[]={"ls","-l", NULL};
        execvp("ls", (char *const *)args);//needs to be char*
        exit(12);
    }
    else{
        int status;
        pid_t returning_pid=wait(&status);
        if(WIFEXITED(status)){
            std::cout<<"Child process: "<<returning_pid<<" exited with status "<<WEXITSTATUS(status);
            //since execvp() succeeded, exit(12) is never executed
            //exec() replaces the entire program in the process. 
            //so exit(12) is not part of the program (unless exec() fails)
            //so you get the exit status 0 from ls, the program which got loaded into the process.
        }
    }
}