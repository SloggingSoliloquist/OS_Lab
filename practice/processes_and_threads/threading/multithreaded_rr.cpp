#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<algorithm>
struct Process{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;
    int turnaround_time;
    int completion_time;
    int waiting_time;
};

bool compareArrivalPriority(Process &a, Process &b){
    if(a.arrival_time==b.arrival_time){
        return a.priority<b.priority;
    }
    return a.arrival_time<b.arrival_time;
}

void sort_processes(std::vector<Process> &processes){
    for(auto &p:processes){
        p.remaining_time=p.burst_time;
    }
    std::sort(processes.begin(), processes.end(), compareArrivalPriority);
}

void rr(std::vector<Process> &processes, int time_quantum)
{
    std::queue<Process> ready_queue;
    int current_time=0;
    int completed=0;
    int i=0;
    int n=processes.size();
    while(completed<n){
        while(i<n && processes[i].arrival_time<=current_time){
            ready_queue.push(processes[i]);
            i++;
        }
        if(ready_queue.empty()){
            current_time=processes[i].arrival_time;
            continue;
        }

        Process p=ready_queue.front();
        ready_queue.pop();
        int execution_time=std::min(time_quantum, p.remaining_time);
        current_time+=execution_time;
        p.remaining_time-=execution_time;
        while(i<n && processes[i].arrival_time<=current_time){
            ready_queue.push(processes[i]);
            i++;
        }
        if(p.remaining_time==0){
            p.completion_time=current_time;
            p.turnaround_time=p.completion_time-p.arrival_time;
            p.waiting_time=p.turnaround_time=p.burst_time;
            completed++;
            for(auto &proc:processes){
                if(proc.pid==p.pid){
                    proc=p;
                }
            }
        }   
        else{
            ready_queue.push(p);
        }  
    }
        for(auto &proc:processes){
        std::cout<<"ID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWait"<<std::endl;
        std::cout<<proc.pid<<"\t"<<proc.arrival_time<<"\t"<<proc.burst_time<<"\t"<<proc.priority<<
        "\t"<<proc.completion_time<<"\t"<<proc.turnaround_time<<"\t"<<proc.waiting_time<<std::endl;
    }
}


int main(){
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
        std::cout<<"Enter Priority: ";
        std::cin>>process.priority;
    }
    std::thread sorting(sort_processes, std::ref(processes));
    sorting.join();
    std::thread scheduling(rr, std::ref(processes),4);
    scheduling.join();
    return 0;

}