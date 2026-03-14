//sjf non preemptive
#include <iostream>
#include <algorithm>
#include<vector>
#include<queue>

struct Process{
    int pid;
    int arrival_time;
    int burst_time;

    int completion_time;
    int turnaround_time;
    int waiting_time;
};

/*
THE IDEA:
Similar to fcfs, you again sort processes based on their time of arrival. 
But after that, instead of directly executing, construct a ready queue of processes that have already arrived,
then pick the process with the least burst time from that ready queue to execute. 
*/
//We need two comparators: one for arrival time and one for burst time
bool compareArrival(Process a, Process b)
{
    return a.arrival_time<b.arrival_time;
}

//priority queues need a Functor, not a function. 
struct compareBurst
{
    bool operator()(const Process &a, const Process &b){
    return a.burst_time>b.burst_time; //This comparator is for the priority queue which we are directly taking from the stl. 
    //priority queue implements a max heap, we want a min heap instead. SO we reverse the order. 
}
};

void sjf_nonpreemptive(std::vector<Process>&processes){
    std::sort(processes.begin(), processes.end(), compareArrival);
    std::priority_queue<Process, std::vector<Process>, compareBurst> ready_queue; 
    /*std::priority_queue<type of objects in the queue, the container holding those objects (vector, linked list etc.), comparator (must
    be a functor)*/
    int current_time = 0;
    int i=0;
    int n=processes.size();
    //now start walking through time and seeing which processes to execute
    while(i<n || !ready_queue.empty())
    {
        while(i<n && processes[i].arrival_time<=current_time)//there's a process that has arrived
        {
            ready_queue.push(processes[i]);
            i++;//move on to the next process
        }
        if(ready_queue.empty()){
            //if the ready queue is empty there are no processes that have arrived. just jump to the next processes arrival
            current_time=processes[i].arrival_time;
            continue;//the pushing to the ready queue will happen in the next iteration of the while loop
        }
        //Now do the actual execution
        Process p = ready_queue.top();
        ready_queue.pop();
        p.completion_time= current_time+p.burst_time;
        p.turnaround_time= p.completion_time-p.arrival_time;
        p.waiting_time= p.turnaround_time-p.burst_time;
        current_time= p.completion_time;

        //p is a copy of the actual process we need to modify, so change it back
        for (struct Process &process: processes)
        {
            if(process.pid==p.pid)
            {
                process=p;
                break;
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
    }
    sjf_nonpreemptive(processes);
    displayProcesses(processes);
    return 0;
}