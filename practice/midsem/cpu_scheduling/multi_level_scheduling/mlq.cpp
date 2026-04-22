//Multilevel queue scheduling
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

/*
PRIORITY 1: RR, Time Quantum=2
PRIORITY 2: RR, Time Quantum=4
Priority 3: FCFS
*/

/*
THE IDEA:
There's a Multi-level Scheduler whose task is just to assign priorities and allow higher level queues to finish execution completely before
lower level queues. 
This scheduler calls SINGLE STEPS of the Schedulers that are present for each queue. In this case, it will call one step of RR for the first
queue, one step of RR for the second, and one step of FCFS for the third. 
With each call, it needs to know if the process that was scheduled was finished or not, so these "scheduling step" functions are boolean
functions which return whether the process finished or not. 
It also needs to know which process was completed, because queue-level schedulers only update the current time and the remaining time. 
Every other metric which can only be calculated after the process has completed will be calculated by the Grand Scheduler. 
*/

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

bool rr_step(std::queue<Process> &q, int &current_time, int time_quantum, Process &curr_process)
//It needs the queue itself, the current time that the MLQ Scheduler is at to be able to modify it, the time quantum for RR scheduling,
//and the pointer it needs to update to indicate to the MLQ Scheduler the identity of the completed process
{
    curr_process= q.front();
    q.pop();
    int execution_time = std::min(time_quantum, curr_process.remaining_time);
    curr_process.remaining_time-=execution_time;
    current_time+=execution_time;

    if(curr_process.remaining_time==0)
    {
        return true;
    }
    else{
        // q.push(p);
        //Why did I remove the line above?
        /*If I kept that line, I'm pushing the process which has finished execution before any other new processes arrive within
        that execution time. Let's say this process takes 3 seconds to execute, starting from T=0. This will push q once done.
        But if any processes arrive between T=0 and T=2, they only get pushed AFTER this in the MLQ section. That's a problem, cos
        those processes arrived earlier than this one finished, so this one should be pushed later. 
        */
        return false;
    }
}

bool fcfs_step(std::queue<Process> &q, int &current_time, Process &curr_process)
{
    curr_process= q.front();
    q.pop();
    current_time+=curr_process.remaining_time;
    curr_process.remaining_time=0;
    return true;
}

bool compareArrival(const Process &a, const Process &b) 
{
    return a.arrival_time<b.arrival_time;
}
void mlq_scheduler(std::vector<Process> &processes)
{
    //sort the array of processes based on arrival
    std::sort(processes.begin(), processes.end(), compareArrival);
    //Create the 3 queues
    std::queue<Process> q1;
    std::queue<Process> q2;
    std::queue<Process> q3;
    int completed=0;
    int n = processes.size();
    int current_time=0;
    int i=0;

    for(auto &p: processes)
    {
        p.remaining_time=p.burst_time;
    }

    while(completed<n)
    {
        //now similar to what you've done for all scheduling algorithms, add te ones that have arrived to their queues
        while(i<n && processes[i].arrival_time<=current_time){
            if (processes[i].priority==1)
            {
                q1.push(processes[i]);
            }
            else if(processes[i].priority==2)
            {
                q2.push(processes[i]);
            }
            else
            {
                q3.push(processes[i]);
            }
            i++;
        }
    
    if(q1.empty() && q2.empty() && q3.empty()){
        current_time=processes[i].arrival_time;
        continue;
    }
    Process curr_process;
    bool done=false;
    //now do the scheduling. 
    if(!q1.empty())
    {
        done=rr_step(q1, current_time, 2, curr_process);
    }
    else if(!q2.empty())
    {
        done=rr_step(q2, current_time, 4, curr_process);
    }
    else
    {
        done=fcfs_step(q3, current_time, curr_process);
    }

    //once each scheduler is done with their job, check for any new arrivals of processes and if so, push them to the queue
    while(i<n && processes[i].arrival_time<=current_time){
        if (processes[i].priority==1)
        {
            q1.push(processes[i]);
        }
        else if(processes[i].priority==2)
        {
            q2.push(processes[i]);
        }
        else
        {
            q3.push(processes[i]);
        }
        i++;
    }

    if(done)//if a process is done, update its details
    {
        curr_process.completion_time=current_time;
        curr_process.turnaround_time= curr_process.completion_time-curr_process.arrival_time;
        curr_process.waiting_time= curr_process.turnaround_time-curr_process.burst_time;
        completed++;
        for(auto &p:processes)
        {
            if(p.pid==curr_process.pid)
            {
                p=curr_process;
            }
        }
    }
    else{//if it isn't done, push it back into its respective queue
         if (curr_process.priority==1)
        {
            q1.push(curr_process);
        }
        else if(curr_process.priority==2)
        {
            q2.push(curr_process);
        }
        else
        {
            q3.push(curr_process);
        }
        //DO NOT INCREMENT I HERE. YOU ARE JUST REQUEUING THE PROCESS. 
        
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
    mlq_scheduler(processes);
    displayProcesses(processes);
    return 0;
}