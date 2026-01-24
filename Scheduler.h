#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <vector>
#include <queue>

class Scheduler {
private:
    std::vector<Process> completedProcesses;  // Processes that finished execution
    int timeQuantum;                          // For Round Robin (time slice)
    
public:
    Scheduler();
    
    // Part A: Two scheduling algorithms
    void priorityScheduling(std::vector<Process>& processes);
    void roundRobinScheduling(std::vector<Process>& processes);
    
    // Display functions
    void displayGanttChart(const std::vector<Process>& processes);
    void calculateStatistics(std::vector<Process>& processes);
    void displayStatistics(const std::vector<Process>& processes);
    
    // Scheduler selection based on number of processes
    void scheduleProcesses(std::vector<Process>& processes);
};

#endif
