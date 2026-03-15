#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<iostream>
#include<vector>

int main()
{
    std::vector<pid_t> returned_pids(3);
    for(int i=0; i<3; i++)
    {
        pid_t pid=fork();
        if(pid==-1){
            std::cout<<"COuldn't create process\n";
        }
        else if(pid==0){
            std::cout<<"Child Process: "<<getpid()<<" of Parent: "<<getppid()<<std::endl;
            exit(1);
        }
        else{
            returned_pids.push_back(pid);
        }

    }
    //now that you have all the pids, you can explicitly wait for them to finish one by one
    for(auto pid:returned_pids){
        waitpid(pid, NULL, 0);
    }
}