#ifndef PROCESS_H
#define PROCESS_H

#include <vector>

// This struct represents a single process in the system
struct Process {
    // Part A: Basic Scheduling Info
    int pid;                      // Process ID (unique identifier)
    int arrivalTime;              // When process arrives in system
    int burstTime;                // Total CPU time needed
    int remainingTime;            // For Round Robin (time left to execute)
    int priority;                 // Priority level (lower number = higher priority)
    
    // Part C: Resource Management (Banker's Algorithm)
    std::vector<int> maxNeed;         // Maximum resources this process might need
    std::vector<int> allocation;      // Resources currently held by this process
    std::vector<int> remainingNeed;   // How much more it needs (Max - Allocation)
    
    // Statistics for final report
    int waitingTime;              // Time spent waiting in queue
    int turnaroundTime;           // Total time from arrival to completion
    
    // Constructor to initialize a process
    Process() {
        pid = 0;
        arrivalTime = 0;
        burstTime = 0;
        remainingTime = 0;
        priority = 0;
        waitingTime = 0;
        turnaroundTime = 0;
    }
};

#endif
