#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include "Sync.h"

// Producer Logic: Adds processes to the buffer [cite: 90, 94]
void* producer(void* arg) {
    int id = *((int*)arg);
    while(true) {
        Process p;
        p.pid = rand() % 1000;
        p.burstTime = (rand() % 10) + 1;
        p.priority = (rand() % 5) + 1; // Priority for Part A [cite: 68]
        
        sem_wait(&emptySlots); // Part B: Wait for empty space [cite: 100]
        pthread_mutex_lock(&queueLock); // Part B: Lock buffer [cite: 101]
        
        readyQueue.push(p);
        std::cout << "\n[Producer " << id << "] Created Process ID: " << p.pid << std::endl;
        
        pthread_mutex_unlock(&queueLock); // Unlock [cite: 101]
        sem_post(&fullSlots); // Signal ready [cite: 100]
        
        sleep(2); // Prevent overwhelming the terminal
    }
    return NULL;
}

void* consumer(void* arg) {
    while(true) {
        sem_wait(&fullSlots); // Wait for a process to be available
        pthread_mutex_lock(&queueLock);

        // Part A: Scheduler Selection Rule
        int count = readyQueue.size();
        Process p = readyQueue.front();
        readyQueue.pop();

        if (count <= 5) {
            std::cout << "\n[CPU] Using PRIORITY Scheduling (Count: " << count << ")";
            std::cout << "\n[CPU] Executing PID: " << p.pid << " (Priority: " << p.priority << ")";
        } else {
            std::cout << "\n[CPU] Using ROUND ROBIN Scheduling (Count: " << count << ")";
            std::cout << "\n[CPU] Executing PID: " << p.pid << " (Time Quantum)";
        }

        pthread_mutex_unlock(&queueLock);
        sem_post(&emptySlots); // Signal space is free
        
        sleep(3); // Simulate CPU processing time
    }
    return NULL;
}
