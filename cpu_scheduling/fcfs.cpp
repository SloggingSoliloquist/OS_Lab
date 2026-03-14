//FCFS
//First you need a structure to store all the information about the jobs that you have to schedule.
#include <iostream>
#include<vector>
#include <algorithm>

struct Process{
    //stuff that you know about the process
    int pid;
    int arrival_time;
    int burst_time;
    //stuff that you have to find out about the process after scheduling
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

/*
THE IDEA:
First, get all the processes sorted. 
set the current time to 0. 

now iterate through the sorted array of processes:
for each process in processes: 
     if current_time<arrival_time: 
        current_time=arrival_time (nothing else is being done between the two times so might as well
        advance current_time forward)
    //you know the current time. FCFS is non-preemptive. So the completion time will just be
    the current time+the burst time (the time it takes to execute).
    completion time = current_time+burst_time
    turnaround time = completion_time-arrival_time
    waiting_time = turnaround_time-burst_time

    current_time= completion_time
*/
bool compareArrival(struct Process &a, struct Process &b)
{
    return a.arrival_time<b.arrival_time;
}

void fcfs(std::vector<Process> &processes){
    //what are you sorting based on:? YOu are sorting based on the arrival time of these structs.
    //std::sort allows you to pass your own comparator as an argument, so we can use that. 
    std::sort(processes.begin(), processes.end(), compareArrival);
    int current_time=0;
    for (struct Process &process : processes)
    {
        if(current_time<process.arrival_time)
        {
            current_time=process.arrival_time;
        }

        process.completion_time=current_time+process.burst_time;
        process.turnaround_time=process.completion_time-process.arrival_time;
        process.waiting_time= process.turnaround_time-process.burst_time;
        current_time=process.completion_time;
    }
}

void printProcesses(std::vector<Process>&processes)
{
    std::cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<std::endl;
    for(struct Process process: processes)
    {
        std::cout<<process.pid<<"\t"<<process.arrival_time<<"\t"<<process.burst_time<<"\t"<<process.completion_time<<"\t"<<process.turnaround_time<<"\t"<<process.waiting_time<<std::endl;
    }
}

int main()
{
    int n;
    std::cout<<"Enter number of processes"<<std::endl;
    std::cin>>n;
    
    std::vector<Process> processes(n);
    for(struct Process & process: processes)
    {
        std::cout<<"Enter pid: ";
        std::cin>>process.pid;
        std::cout<<"Arrival time: ";
        std::cin>>process.arrival_time;
        std::cout<<"Burst time: ";
        std::cin>>process.burst_time;
    }

    fcfs(processes);
    printProcesses(processes);
    return 0;
}
