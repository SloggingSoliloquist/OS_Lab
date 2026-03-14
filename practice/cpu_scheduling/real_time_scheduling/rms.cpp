#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;
    int period;   
    int burst;       
    int remaining;   
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int arrival_time; 
};

bool comparePeriod(Process &a, Process &b) {
    return a.period < b.period;
}

void rms(std::vector<Process> &tasks, int simulation_time) {
    for(auto &t: tasks)
        t.remaining = 0, t.completion_time = 0, t.turnaround_time = 0, t.waiting_time = 0, t.arrival_time = 0;

    int n = tasks.size();
    int current_time = 0;

    while(current_time < simulation_time) {
        // Release new instances at multiples of period
        for(auto &t: tasks) {
            if(current_time % t.period == 0)
                t.remaining = t.burst;
        }

        // Pick highest-priority ready task (shortest period)
        Process* running = nullptr;
        for(auto &t: tasks) {
            if(t.remaining > 0) {
                running = &t;
                break;
            }
        }

        if(running) {
            running->remaining--;
            if(running->remaining == 0)
                running->completion_time = current_time + 1;
        }

        current_time++;
    }

    //once you get to the laslt instance, calculate the TA and WA
    for(auto &t: tasks) {
        t.turnaround_time = t.completion_time - t.arrival_time;
        t.waiting_time = t.turnaround_time - t.burst;
    }
}

void displayRMS(std::vector<Process> &tasks) {
    std::cout << "ID\tPeriod\tBurst\tCT\tTAT\tWT\n";
    for(auto &t: tasks)
        std::cout << t.id << "\t" << t.period << "\t" << t.burst << "\t" << t.completion_time << "\t" << t.turnaround_time << "\t" << t.waiting_time << "\n";
}

int main() {
    int n, sim_time;
    std::cout << "Enter number of tasks: ";
    std::cin >> n;
    std::vector<Process> tasks(n);

    for(int i = 0; i < n; i++) {
        tasks[i].id = i+1;
        std::cout << "Enter period and burst for task " << tasks[i].id << ": ";
        std::cin >> tasks[i].period >> tasks[i].burst;
    }

    std::sort(tasks.begin(), tasks.end(), comparePeriod);

    std::cout << "Enter simulation time: ";
    std::cin >> sim_time;

    rms(tasks, sim_time);
    displayRMS(tasks);
    return 0;
}