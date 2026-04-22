#include<sys/types.h>//all data structures relevant 
#include<sys/wait.h>//wait() system call
#include<iostream>
#include<unistd.h>//a lot of POSIX API system calls

/*
Parent creates child processes...child processes create more child processes..child processes create more child processes........
*/
int main(){
    for(int i=0; i<3; i++)
    {
        pid_t pid= fork();
        if(pid==-1){
            std::cout<<"COuldn't create child";
        }
        if (pid==0){
            std::cout<<"Child PID: "<<getpid()<<std::endl;
            std::cout<<"Child's parent: "<<getppid()<<std::endl;
        }
    }
}
/*
The intent was to create only 3 child processes. But because those 3 child processes didn't exit(), and because they share the same
program as the parent, the child processes also call fork() in the loop. so each child again forks. 

interation 1 of the for loop:
parent creates a child
Parent
└── Child1
But now this child won't exit, and will continue execution the same program as the parent at the same point (i.e. after the first iteration
of the for loop)

So now on iteration 2, Parent creates its own child, and Child1 creates a child of its own. 
P
├─ C1
│   └─ C3
└─ C2

And now on iteration 3, each child again forks itself along with the parent
P
├─ C1
│   ├─ C3
│   │   └─ C7
│   └─ C5
├─ C2
│   └─ C6
└─ C4

So you'll see 8 different processes (2^3).
If you added exit(status) at the end of each child's section, only 3 processes will be created(the child won't fork after its section   )
*/
