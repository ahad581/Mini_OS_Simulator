#include "BankersAlgorithm.h"
#include <iostream>
#include <algorithm>

using namespace std;

BankersAlgorithm::BankersAlgorithm(int numResourceTypes) {
    numResources = numResourceTypes;
    available.resize(numResources, 0);
}

void BankersAlgorithm::setAvailableResources(const vector<int>& resources) {
    available = resources;
}

// Check if system is in safe state using Banker's Algorithm
bool BankersAlgorithm::isSafe(vector<Process>& processes) {
    int n = processes.size();
    vector<bool> finished(n, false);
    vector<int> work = available;  // Work is a copy of available
    safeSequence.clear();
    blockedProcesses.clear();
    
    cout << "\n========== BANKER'S ALGORITHM - SAFETY CHECK ==========\n";
    cout << "Available Resources: [";
    for (int i = 0; i < numResources; i++) {
        cout << available[i];
        if (i < numResources - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    int count = 0;
    
    // Try to find a safe sequence
    while (count < n) {
        bool found = false;
        
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                // Check if process can finish with available resources
                bool canFinish = true;
                
                for (int j = 0; j < numResources; j++) {
                    if (processes[i].remainingNeed[j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                
                if (canFinish) {
                    // Process can finish - add its resources back to work
                    cout << "Process P" << processes[i].pid << " can finish. ";
                    cout << "Need: [";
                    for (int j = 0; j < numResources; j++) {
                        cout << processes[i].remainingNeed[j];
                        if (j < numResources - 1) cout << ", ";
                    }
                    cout << "]" << endl;
                    
                    for (int j = 0; j < numResources; j++) {
                        work[j] += processes[i].allocation[j];
                    }
                    
                    safeSequence.push_back(processes[i].pid);
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        
        if (!found) {
            // No process could finish - system is in unsafe state
            cout << "\nSystem is in UNSAFE state!" << endl;
            
            for (int i = 0; i < n; i++) {
                if (!finished[i]) {
                    blockedProcesses.push_back(processes[i].pid);
                }
            }
            return false;
        }
    }
    
    cout << "\nSystem is in SAFE state!" << endl;
    return true;
}

bool BankersAlgorithm::canAllocate(const Process& process) {
    for (int i = 0; i < numResources; i++) {
        if (process.remainingNeed[i] > available[i]) {
            return false;
        }
    }
    return true;
}

void BankersAlgorithm::displaySafeSequence() {
    if (safeSequence.empty()) {
        cout << "No safe sequence found." << endl;
        return;
    }
    
    cout << "\n========== SAFE SEQUENCE ==========\n";
    cout << "< ";
    for (size_t i = 0; i < safeSequence.size(); i++) {
        cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1) cout << " -> ";
    }
    cout << " >" << endl;
}

void BankersAlgorithm::displayBlockedProcesses() {
    if (blockedProcesses.empty()) {
        cout << "\nNo blocked processes." << endl;
        return;
    }
    
    cout << "\n========== BLOCKED PROCESSES ==========\n";
    for (int pid : blockedProcesses) {
        cout << "Process P" << pid << " is BLOCKED (insufficient resources)" << endl;
    }
}
