/*
Multilevel queues with time-slicing. Allow higher order queue to execute 80% of the time, and lower level queue to execute 20%
of the time. Here only 2 queues.
*/
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
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

bool rr_step(std::queue<Process> &q, int &current_time, int time_quantum, Process &p)
{
    p=q.front();
    q.pop();
    int execution_time=std::min(time_quantum, p.remaining_time);
    current_time+=execution_time;
    p.remaining_time-=execution_time;
    return p.remaining_time==0;
}

bool fcfs_step(std::queue<Process> &q, int &current_time, Process &p)
{
    p=q.front();
    q.pop();
    current_time+=p.burst_time;
    p.remaining_time=0;
    return true;
}

bool compareArrival(const Process &a, const Process &b)
{
    return a.arrival_time<b.arrival_time;
}

void mlq_time_slice(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), compareArrival);
    std::queue<Process> q1;
    std::queue<Process> q2;
    for(auto &p:processes)
    {
        p.remaining_time=p.burst_time;
    }

    int current_time=0;
    int i=0;
    int completed=0;
    int n=processes.size();
    int total_time =0;
    while(completed<n)
    {
        while(i<n && processes[i].arrival_time<=current_time)
        {
            if(processes[i].priority==1)
            {
                q1.push(processes[i]);
            }
            else{
                q2.push(processes[i]);
            }
            i++;
        }
        if(q1.empty() && q2.empty()){
            current_time=processes[i].arrival_time;
            continue;
        }

        Process p;

        bool done=false;
        if(total_time<=3)
        {
            if(!q1.empty()){
                done=rr_step(q1, current_time, 3, p);
            }
            else{
                done=fcfs_step(q2, current_time, p);
        }}
        else{
            if(!q2.empty()){
               done=fcfs_step(q2, current_time, p);            
            }
            else{
                done=rr_step(q1, current_time, 3, p);
        }
        }
        total_time=(total_time+1)%5;
        //push other arrivals to their queues
        while(i<n && processes[i].arrival_time<=current_time)
        {
            if(processes[i].priority==1)
            {
                q1.push(processes[i]);
            }
            else{
                q2.push(processes[i]);
            }
            i++;
        }
        
        if(done){
            p.completion_time=current_time;
            p.turnaround_time=p.completion_time-p.arrival_time;
            p.waiting_time=p.turnaround_time-p.burst_time;
            completed++;
            for(auto  &proc: processes)
            {
                if(p.pid==proc.pid)
                proc=p;
            }
        }
        else{
            if(p.priority==1)
            {
                q1.push(p);
            }
            else{
                q2.push(p);
            }
        }
}
}

void displayProcesses(std::vector<Process> &processes)
{
    std::cout<<"PID\tAT\tBT\tPri\tCT\tTAT\tWT"<<std::endl;
    for(struct Process process: processes)
    {
        std::cout<<process.pid<<"\t"<<process.arrival_time<<"\t"<<process.burst_time<<"\t"<<process.priority<<"\t"<<process.completion_time<<"\t"<<process.turnaround_time<<"\t"<<process.waiting_time<<std::endl;
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
    mlq_time_slice(processes);
    displayProcesses(processes);
    return 0;
}