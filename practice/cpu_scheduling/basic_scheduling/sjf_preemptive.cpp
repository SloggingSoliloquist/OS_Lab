#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

struct Process{
    int pid;
    int arrival_time;
    int burst_time;

    int remaining_time;

    int turnaround_time;
    int completion_time;
    int waiting_time;
};

bool compareArrival(Process a, Process b)
{
    return a.arrival_time<b.arrival_time;
}

struct compareRemainingTime{
    bool operator()(Process a, Process b){
        return a.remaining_time>b.remaining_time;
    }
};

void sjf_preemptive(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), compareArrival);
    std::priority_queue<Process, std::vector<Process>, compareRemainingTime> ready_queue;
    for(Process &process:processes)
    {
        process.remaining_time=process.burst_time;
    }
    int i =0;
    int n = processes.size();
    int current_time=0;
    int completed=0;

    while(completed<n){
        while(i<n && processes[i].arrival_time<=current_time)
        {
            ready_queue.push(processes[i]);
            i++;
        }
        if(ready_queue.empty())
        {
            current_time++; //NOT current_time = processes[i].arrival_time
            continue;
        }

        Process p=ready_queue.top();
        ready_queue.pop();
        p.remaining_time--;
        current_time++;
        if(p.remaining_time==0)
        {
            p.completion_time=current_time;
            p.turnaround_time=p.completion_time-p.arrival_time;
            p.waiting_time=p.turnaround_time-p.burst_time;
            completed++;
            for(auto &process:processes)
            {
                if(p.pid==process.pid)
                {
                    process=p;
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
    sjf_preemptive(processes);
    displayProcesses(processes);
    return 0;
}