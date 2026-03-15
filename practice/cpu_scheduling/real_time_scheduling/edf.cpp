#include<vector>
#include<iostream>

/*
Almost identical to RMS, but while selecting the process to execute, select the one with the least next_release instead of the least period
*/

struct Process{
    int pid;
    int burst_time;
    int period;

    int remaining_time;
    int next_release;
};

int gcd(int a, int b){return b==0?a:gcd(b, a%b);}
int lcm(int a, int b){return a/gcd(a, b)*b;}
int computeHyperperiod(std::vector<Process> &processes){
    int hyperperiod=processes[0].period;
    for(int i=1;i<processes.size();i++){
        hyperperiod=lcm(hyperperiod, processes[i].period);
    }
    return hyperperiod;
}
void edf(std::vector<Process> &processes, int hyperperiod){
    int n=processes.size();
    int t=0;
    while(t<hyperperiod){
        //check for any processes that need to be re-released
        for(auto &p:processes){
            if(t==p.next_release){
            if(p.remaining_time>0)std::cout<<"Process "<<p.pid<<" has failed to meet its deadline\n";
            p.remaining_time=p.burst_time;
            p.next_release+=p.period;
        }
    }
        //select the highest priority(least next_release) task to execute
        int chosen=-1;
        for(int i=0; i<n; i++){
            if(processes[i].remaining_time>0){
                if(chosen==-1 || processes[i].next_release<processes[chosen].next_release){
                    chosen=i;
                }
            }
        }
        //display the state of the scheduler
        if(chosen==-1){
            std::cout<<"Idle"<<std::endl;
        }
        else{
            std::cout<<"Process "<<processes[chosen].pid<<" is executing at time "<<t<<std::endl;
            processes[chosen].remaining_time--;
        }
        t++;
    }
}

int main(){
    int n;
    std::cout<<"Enter the number of processes: ";
    std::cin>>n;
    std::vector<Process> processes(n);
    for(auto &p:processes){
        std::cout<<"Enter the PID: ";
        std::cin>>p.pid;
        std::cout<<"Enter the burst time: ";
        std::cin>>p.burst_time;
        std::cout<<"Enter the period: ";
        std::cin>>p.period;
        p.remaining_time=0;
        p.next_release=0;
    }
    int hyperperiod=computeHyperperiod(processes);
    edf(processes, hyperperiod);
    return 0;
}