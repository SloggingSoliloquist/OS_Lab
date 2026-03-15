#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
/*
THE IDEA:
In Real time scheduling, unlike the other scheduling algorithms, the tasks are periodic. So you can't just keep track of
when the list of tasks is over. Each task has a burst time, a period and a deadline. 
In RMS particularly, the deadline is usually the period, meaning that the current task should finish executing before its next release. 
RMS is a fixed/static priority scheduler, so the priority of each task is decided beforehand, and is the inverse of the task's period. 
*/

/*
Priority queues are great for the other scheduling algorithms because they model the way the scheduler picks a task from the ready queue. 
But that sort of model isn't useful for real time schedulers, which have tasks re-ocurring at fixed periods. So it's better if you just
walk through the hyperperiod and manually pick the higher priority task, cos pushing tasks back into a priority queue gets very messy
cos multiple instances of the exact same task can exist in the queue at the same time. 
*/

struct Process{
    int pid;
    int period;
    int burst_time;

    int next_release;
    int remaining_time;
};

int gcd(int a, int b){return b==0?a:gcd(b, a%b);}
int lcm(int a, int b){return a/gcd(a,b)*b;}

int computeHyperperiod(std::vector<Process> &processes){
    int hyperperiod=processes[0].period;
    for(int i=1; i<processes.size(); i++){
        hyperperiod=lcm(hyperperiod, processes[i].period);
    }
    return hyperperiod;
}

void rms(std::vector<Process> &processes, int hyperperiod){
    int n=processes.size();
    int t=0;
    while(t<hyperperiod){
        //keep checking if any tasks have arrived at their  next_release, then re-release them by updating their 
        //remaining_time and next_release
        for(auto &p:processes){
            if (t==p.next_release){
                if(p.remaining_time>0)std::cout<<"Process "<<p.pid<<" has missed its deadline\n";
                p.remaining_time=p.burst_time;
                p.next_release+=p.period;
            }
        }
        //now select the highest priority task among the ones that haven't completed yet for execution
        //simplest to iterate using an actual integer
        int chosen=-1;
        for(int i=0; i<n; i++){
            if(processes[i].remaining_time>0){
                if(chosen==-1 || processes[i].period<processes[chosen].period){
                    chosen=i;
                }
            }
        } 
        
        if(chosen==-1){
            std::cout<<"Idle"<<std::endl;
        }
        //execute the chosen process for a second
        else{
            std::cout<<"Executing process "<<processes[chosen].pid<<" at time "<<t<<std::endl;
            processes[chosen].remaining_time--;//don't forget
        }
        t++;//don't forget
    }
}

int main(){
    int n;
    std::cout<<"Enter the number of processes: ";
    std::cin>>n;
    std::vector<Process> processes(n);
    for(auto &p:processes){
        std::cout<<"Enter the process ID: ";
        std::cin>>p.pid;
        std::cout<<"Enter the period: ";
        std::cin>>p.period;
        std::cout<<"Enter the burst time: ";
        std::cin>>p.burst_time;
        p.next_release=0;
        p.remaining_time=0;
    }
    int hyperperiod = computeHyperperiod(processes);
    rms(processes, hyperperiod);
    return 0;
}



