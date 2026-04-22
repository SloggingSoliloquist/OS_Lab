#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

struct Process{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(Process &a, Process &b)
{
    return a.arrival_time<b.arrival_time;
}

struct comparePriority{
    bool operator()(Process &a, Process &b)
    {
        if (a.priority==b.priority)
        return a.arrival_time>b.arrival_time; //if two processes have same priority, break the tie using FCFS.
        return a.priority>b.priority; //a should have lower priority than b if a.priority>b.priority (so lower priority number=higher priority)
    }
};

void priority_np(std::vector<Process> &processes)
{
    //sort based on arrival time
    std::sort(processes.begin(), processes.end(), compareArrival);
    //create a priority queue based on the priority field provided
    std::priority_queue<Process, std::vector<Process>, comparePriority> ready_queue;
    int current_time=0;
    int i=0;
    int n=processes.size();
    while(i<n || !ready_queue.empty())
    {
        while(i<n && processes[i].arrival_time<=current_time)
        {
            ready_queue.push(processes[i]);
            i++;
        }
        if(ready_queue.empty())
        {
            current_time=processes[i].arrival_time;
            continue;
        }

        Process p = ready_queue.top();
        ready_queue.pop();
        p.completion_time = current_time+p.burst_time;
        p.turnaround_time= p.completion_time-p.arrival_time;
        p.waiting_time= p.turnaround_time-p.burst_time;
        current_time= p.completion_time;

        for(auto &proc:processes)
        {
            if(proc.pid==p.pid)
            {
                proc=p;
            }
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
    priority_np(processes);
    displayProcesses(processes);
    return 0;
}