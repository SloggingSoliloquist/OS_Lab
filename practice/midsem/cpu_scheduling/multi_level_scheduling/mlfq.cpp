#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

struct Process{
    int pid;
    int arrival_time;
    int burst_time;
    //no priority field, priorities will be handled by just moving the process to a different queue
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};

bool compareArrival(const Process &a, const Process &b)
{
    return a.arrival_time<b.arrival_time;
}

bool rr_step(std::queue<Process> &q, int &current_time, Process &p, int time_quantum){
    p=q.front();
    q.pop();
    int execution_time=std::min(time_quantum, p.remaining_time);
    current_time+=execution_time;
    p.remaining_time-=execution_time;
    return p.remaining_time==0;
}

bool fcfs_step(std::queue<Process> &q, int &current_time, Process &p){
    p=q.front();
    q.pop();
    current_time+=p.remaining_time;
    p.remaining_time=0;
    return true;
}

void mlfq(std::vector<Process> &processes)
{
    std::sort(processes.begin(), processes.end(), compareArrival);
    std::queue<Process> q1;//RR, TQ=2
    std::queue<Process> q2;//RR, TQ=4
    std::queue<Process> q3;//FCFS
    int current_time=0;
    int completed=0;
    int i=0;
    int n=processes.size();
    for(auto &p: processes){
        p.remaining_time=p.burst_time;
    }
    while(completed<n)
    {
        //push everything to the highest level queue
        while(i<n && processes[i].arrival_time<=current_time)
        {
            q1.push(processes[i]);
            i++;
        }
        if(q1.empty() && q2.empty() && q3.empty())
        {
            current_time=processes[i].arrival_time;
            continue;
        }
        Process p;
        int q_num;
        bool done=false;
        //same as MLQ, just execute each queue, higher order first. While executing the queue, record the queue number so 
        //that you know where to push any any processes that get demoted from that queue.
        if(!q1.empty())
        {
            q_num=1;
            done=rr_step(q1, current_time, p, 2);
        }
        else if(!q2.empty()){
            q_num=2;
            done=rr_step(q2, current_time, p, 4);
        }
        else{
            q_num=3;
            done=fcfs_step(q3, current_time, p);
        }
        //again, just like MLQ, add new processes. But unlike MLQ, add everything to the highest queue. 
        while(i<n && processes[i].arrival_time<=current_time)
        {
            q1.push(processes[i]);
            i++;
        }  
        
        if(done){
            p.completion_time=current_time;
            p.turnaround_time=p.completion_time-p.arrival_time;
            p.waiting_time=p.turnaround_time-p.burst_time;
            completed++;
            for(Process &proc:processes)
            {
                if(proc.pid==p.pid){
                    proc=p;
                }
            }
        }
        else{
            if(q_num==1)//not 0
            {
                q2.push(p);
            }
            else
            {
                q3.push(p);
            }//there are only two places the processes can get demoted to: q2 or q3. 
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
    mlfq(processes);
    displayProcesses(processes);
    return 0;
}