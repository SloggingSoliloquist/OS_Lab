#include<iostream>
#include<vector>
#include<unistd.h>
#include<sys/types.h>

struct Process{
    int pid; 
    int arrival_time;
    int burst_time;

    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main(){

    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid==0){
        char fd_char[10];
        sprintf(fd_char, "%d", fd[0]);
        char * arg[]={(char *)"srtf", fd_char, NULL};
        execv("./srtf", arg);
        perror("Exec failed");
    }
    else{
        close(fd[0]);
    int n;
    std::cout<<"Enter the number of processes: ";
    std::cin>>n;
    std::vector<Process> processes(n);
    for(auto &process:processes){
        std::cout<<"Enter pid: ";
        std::cin>>process.pid;
        std::cout<<"Enter arrival time: ";
        std::cin>>process.arrival_time;
        std::cout<<"Enter burst time: ";
        std::cin>>process.burst_time;
    }
    write(fd[1], &n, sizeof(int));
    write(fd[1], processes.data(), n*sizeof(Process));
    close(fd[1]);
    return 0;
}
}