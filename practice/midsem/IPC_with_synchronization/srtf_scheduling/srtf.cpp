#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<unistd.h>
#include<algorithm>
struct Process{
    int pid; 
    int arrival_time;
    int burst_time;

    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(Process &a, Process &b){
    return a.arrival_time<b.arrival_time;
}

struct compareRemainingTime{
    bool operator()(Process &a, Process &b){
        return a.remaining_time>b.remaining_time;
    }
};

void srtf(std::vector<Process> &processes){
    std::sort(processes.begin(), processes.end(), compareArrival);
    for(auto &el:processes){
        el.remaining_time=el.burst_time;
    }
    std::priority_queue<Process, std::vector<Process>, compareRemainingTime> ready_queue;
    int i=0;
    int completed=0;
    int current_time=0;
    int n=processes.size();
    while(completed<n){
        while(i<n && processes[i].arrival_time<=current_time){
            ready_queue.push(processes[i]);
            i++;
        }
        if(ready_queue.empty()){
            current_time++;
            continue;
        }

        Process p=ready_queue.top();
        ready_queue.pop();
        p.remaining_time--;
        current_time++;
        if(p.remaining_time==0){
            p.completion_time=current_time;
            p.turnaround_time=p.completion_time-p.arrival_time;
            p.waiting_time=p.turnaround_time-p.burst_time;
            completed++;
            for(auto &proc:processes){
                if(p.pid==proc.pid){
                    proc=p;
                }
            }
        }
        else{
            ready_queue.push(p);
        }
    }
}

void displayProcesses(std::vector<Process> &p){
    for(auto &proc:p){
        std::cout<<"ID\tArrival\tBurst\tCompletion\tTurnaround\tWait"<<std::endl;
        std::cout<<proc.pid<<"\t"<<proc.arrival_time<<"\t"<<proc.burst_time<<
        "\t"<<proc.completion_time<<"\t"<<proc.turnaround_time<<"\t"<<proc.waiting_time<<std::endl;
    }
}

int main(int argc, char *argv[]){
    int fd=atoi(argv[1]);
    int n;
    read(fd, &n, sizeof(int));
    std::vector<Process> processes(n);
    read(fd, processes.data(), n*sizeof(Process));
    srtf(processes);
    displayProcesses(processes);
    return 0;
}