#ifndef BANKERS_ALGORITHM_H
#define BANKERS_ALGORITHM_H

#include "Process.h"
#include <vector>

class BankersAlgorithm {
private:
    std::vector<int> available;        // Available resources
    int numResources;                  // Number of resource types
    std::vector<int> safeSequence;     // Safe sequence of process execution
    std::vector<int> blockedProcesses; // Processes that cannot be granted resources
    
public:
    BankersAlgorithm(int numResourceTypes);
    
    // Set available resources
    void setAvailableResources(const std::vector<int>& resources);
    
    // Check if system is in safe state
    bool isSafe(std::vector<Process>& processes);
    
    // Check if a process can be granted resources
    bool canAllocate(const Process& process);
    
    // Display safe sequence
    void displaySafeSequence();
    
    // Display blocked processes
    void displayBlockedProcesses();
    
    // Get safe sequence
    std::vector<int> getSafeSequence() { return safeSequence; }
};

#endif
