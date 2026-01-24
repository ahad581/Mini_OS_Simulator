#include "Scheduler.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

Scheduler::Scheduler() {
    timeQuantum = 2;  // Round Robin time slice = 2 units
}

// Priority Scheduling (Non-preemptive)
// Lower priority number = Higher priority
void Scheduler::priorityScheduling(vector<Process>& processes) {
    cout << "\n========== PRIORITY SCHEDULING ==========\n";
    
    // Sort processes by priority (lower number first)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority < b.priority;  // Sort ascending by priority
    });
    
    int currentTime = 0;
    
    for (auto& p : processes) {
        // If process hasn't arrived yet, CPU is idle
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        
        // Calculate waiting time = current time - arrival time
        p.waitingTime = currentTime - p.arrivalTime;
        // Execute the process
        currentTime += p.burstTime;
        // Calculate turnaround time = waiting time + burst time
        p.turnaroundTime = p.waitingTime + p.burstTime;
        
        cout << "Process P" << p.pid << " executed from time "
             << (currentTime - p.burstTime) << " to " << currentTime << "\n";
    }
}

// Round Robin Scheduling (Preemptive)
void Scheduler::roundRobinScheduling(vector<Process>& processes) {
    cout << "\n========== ROUND ROBIN SCHEDULING (Quantum = 2) ==========\n";
    
    queue<Process*> readyQueue;
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    // Initialize remaining time for all processes
    for (auto& p : processes) {
        p.remainingTime = p.burstTime;
    }
    
    vector<bool> inQueue(n, false);
    
    // Add first process to queue
    readyQueue.push(&processes[0]);
    inQueue[0] = true;
    
    while (completed < n) {
        if (readyQueue.empty()) {
            currentTime++;
            // Check if any process has arrived
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
                    readyQueue.push(&processes[i]);
                    inQueue[i] = true;
                }
            }
            continue;
        }
        
        Process* current = readyQueue.front();
        readyQueue.pop();
        
        // Execute for time quantum or remaining time (whichever is smaller)
        int execTime = min(timeQuantum, current->remainingTime);
        cout << "Process P" << current->pid << " executed from time "
             << currentTime << " to " << (currentTime + execTime) << "\n";
        
        current->remainingTime -= execTime;
        currentTime += execTime;
        
        // Check for newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(&processes[i]);
                inQueue[i] = true;
            }
        }
        
        // If current process is not finished, add back to queue
        if (current->remainingTime > 0) {
            readyQueue.push(current);
        } else {
            // Process completed
            completed++;
            current->turnaroundTime = currentTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
        }
    }
}

// Display Gantt Chart
void Scheduler::displayGanttChart(const vector<Process>& processes) {
    cout << "\n========== GANTT CHART ==========\n";
    cout << "|";
    for (const auto& p : processes) {
        cout << " P" << p.pid << " |";
    }
    cout << endl;
}

// Calculate statistics for all processes
void Scheduler::calculateStatistics(vector<Process>& processes) {
    // Statistics are calculated during scheduling
    // This function can be used for additional calculations if needed
}

// Display statistics
void Scheduler::displayStatistics(const vector<Process>& processes) {
    cout << "\n========== STATISTICS ==========\n";
    cout << left << setw(10) << "PID" 
         << setw(15) << "Burst Time" 
         << setw(15) << "Waiting Time" 
         << setw(18) << "Turnaround Time" << endl;
    cout << string(58, '-') << endl;
    
    int totalWT = 0, totalTAT = 0;
    
    for (const auto& p : processes) {
        cout << left << setw(10) << p.pid 
             << setw(15) << p.burstTime 
             << setw(15) << p.waitingTime 
             << setw(18) << p.turnaroundTime << endl;
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }
    
    cout << string(58, '-') << endl;
    cout << "Average Waiting Time: " << (double)totalWT / processes.size() << "\n";
    cout << "Average Turnaround Time: " << (double)totalTAT / processes.size() << "\n";
}

// Schedule based on number of processes - AUTOMATIC SELECTION
void Scheduler::scheduleProcesses(vector<Process>& processes) {
    int numProcesses = processes.size();
    
    cout << "\n========================================\n";
    cout << "  AUTOMATIC SCHEDULER SELECTION\n";
    cout << "========================================\n";
    cout << "Ready Processes: " << numProcesses << "\n";
    
    if (numProcesses <= 5) {
        cout << "Selected Algorithm: PRIORITY SCHEDULING\n";
        cout << "Reason: ≤ 5 processes in ready queue\n";
        cout << "========================================\n\n";
        priorityScheduling(processes);
    } else {
        cout << "Selected Algorithm: ROUND ROBIN\n";
        cout << "Reason: > 5 processes in ready queue\n";
        cout << "Time Quantum: 2 units\n";
        cout << "========================================\n\n";
        roundRobinScheduling(processes);
    }
    
    displayGanttChart(processes);
    displayStatistics(processes);
}
