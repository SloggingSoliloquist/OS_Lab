#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;
    int period;     // T
    int burst;      // C
    int remaining;  // remaining execution
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int next_release; // next release time
    int deadline;     // absolute deadline
};

void edf(std::vector<Process> &tasks, int simulation_time) {
    int n = tasks.size();
    for(auto &t: tasks) {
        t.remaining = 0;
        t.next_release = 0;
        t.deadline = t.period;
        t.completion_time = 0;
        t.turnaround_time = 0;
        t.waiting_time = 0;
    }

    int current_time = 0;
    while(current_time < simulation_time) {
        // Release new instances
        for(auto &t: tasks) {
            if(current_time == t.next_release) {
                t.remaining = t.burst;
                t.deadline = current_time + t.period;
                t.next_release += t.period;
            }
        }

        // Pick task with earliest deadline among ready tasks
        Process* running = nullptr;
        int earliest_deadline = 1e9;
        for(auto &t: tasks) {
            if(t.remaining > 0 && t.deadline < earliest_deadline) {
                earliest_deadline = t.deadline;
                running = &t;
            }
        }

        if(running) {
            running->remaining--;
            if(running->remaining == 0)
                running->completion_time = current_time + 1;
        }

        current_time++;
    }

    // Compute TAT and WT for last instance
    for(auto &t: tasks) {
        t.turnaround_time = t.completion_time - (t.next_release - t.period);
        t.waiting_time = t.turnaround_time - t.burst;
    }
}

void displayEDF(std::vector<Process> &tasks) {
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

    std::cout << "Enter simulation time: ";
    std::cin >> sim_time;

    edf(tasks, sim_time);
    displayEDF(tasks);

    return 0;
}