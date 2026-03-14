#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#define TIME_QUANTUM 3
struct Process{
    int pid;
    int arrival_time;
    int burst_time;

    int completion_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(Process &a, Process &b)
{
    return a.arrival_time<b.arrival_time;
}

void rr(std::vector<Process> &processes) //rr is very similar to priority_p and srtf. 
{
    std::sort(processes.begin(), processes.end(),compareArrival);
    std::queue<Process> ready_queue;
    int i=0;
    int current_time=0;
    int completed=0;
    int n=processes.size();
    for(auto &p:processes)
    {
        p.remaining_time=p.burst_time;
    }
    while(completed<n)
    {
        while(i<n && processes[i].arrival_time<=current_time){
            ready_queue.push(processes[i]);
            i++;
        }
        if(ready_queue.empty()){
            current_time=processes[i].arrival_time;
            continue;
        }
    //Now pick the process at the front of the queue and execute it for: either the time quantum, or if 
    //the remaining time of execution is less than the time quantum, the remaining time. 
    Process p = ready_queue.front();
    ready_queue.pop();
    int exec_time = std::min(p.remaining_time, TIME_QUANTUM);
    current_time+=exec_time;
    p.remaining_time-=exec_time;
    //Now, new processes might have arrived during this time, so check for them and add them to the queue again
    while(i<n && processes[i].arrival_time<=current_time)
    {
        ready_queue.push(processes[i]);
        i++;
    }
    //now check if the process you just executed has finished executing or not. 
    if(p.remaining_time==0){
        p.completion_time=current_time;
        p.turnaround_time=p.completion_time-p.arrival_time;
        p.waiting_time=p.turnaround_time-p.burst_time;
        completed++;
        for(auto &proc:processes)
        {
            if(proc.pid==p.pid)
            {
                proc=p;
                break;
            }
        }
    }
    else{
        ready_queue.push(p);
    }
}
}

void displayProcesses(std::vector<Process> &processes)
{
    std::cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<std::endl;
    for(struct Process process: processes)
    {
        std::cout<<process.pid<<"\t"<<process.arrival_time<<"\t"<<process.burst_time<<"\t"<<process.completion_time<<"\t"<<process.turnaround_time<<"\t"<<process.waiting_time<<std::endl;
    }
}

int main(){
    int n;
    std::cout<<"Enter number of processes: ";
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
    rr(processes);
    displayProcesses(processes);
    return 0;
}