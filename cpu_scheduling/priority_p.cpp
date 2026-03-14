#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

struct Process{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int waiting_time;
    int completion_time;
    int turnaround_time;
    int remaining_time;
};

bool compareArrival(Process &a, Process &b)
{
    return a.arrival_time<b.arrival_time;
}

struct comparePriority{
    bool operator()(Process &a, Process &b)
    {
        return a.priority>b.priority;
    }
};
void priority_preemptive(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), compareArrival);
    std::priority_queue<Process, std::vector<Process>, comparePriority> ready_queue;
    int i=0;
    int completed =0;
    int n=processes.size();
    int current_time=0;
    for(auto &p:processes)
    {
        p.remaining_time=p.burst_time;
    }

    while(completed<n)
    {
        while(i<n && processes[i].arrival_time<=current_time)
        {
            ready_queue.push(processes[i]);
            i++;
        }
        if(ready_queue.empty())
        {
            current_time++;//do NOT skip forward by more than one step. 
            continue;
        }

    Process p=ready_queue.top();
    ready_queue.pop();
    p.remaining_time--;
    current_time++;
    if(p.remaining_time==0)
    {
        p.completion_time= current_time;
        p.turnaround_time= p.completion_time-p.arrival_time;
        p.waiting_time= p.turnaround_time-p.burst_time;
        completed++;
        for(auto &proc:processes)
        {
            if(proc.pid==p.pid)
            {
                proc=p;
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
        std::cout<<"Enter the priority: ";
        std::cin>>process.priority;
    }
    priority_preemptive(processes);
    displayProcesses(processes);
    return 0;
}