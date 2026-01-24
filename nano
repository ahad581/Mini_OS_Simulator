#include "ProducerConsumer.h"
#include <iostream>
#include <unistd.h>  // for sleep()
#include <cstdlib>   // for rand()

using namespace std;

// Initialize semaphores and mutex
void initializeBuffer(SharedBuffer* sharedBuffer) {
    sem_init(&sharedBuffer->empty, 0, BUFFER_SIZE);  // Initially all slots empty
    sem_init(&sharedBuffer->full, 0, 0);              // Initially no items
    pthread_mutex_init(&sharedBuffer->mutex, NULL);
    sharedBuffer->producerDone = false;
    sharedBuffer->processCounter = 1;
}

// Destroy semaphores and mutex
void destroyBuffer(SharedBuffer* sharedBuffer) {
    sem_destroy(&sharedBuffer->empty);
    sem_destroy(&sharedBuffer->full);
    pthread_mutex_destroy(&sharedBuffer->mutex);
}

// Producer thread function
void* producer(void* arg) {
    SharedBuffer* sharedBuffer = (SharedBuffer*)arg;
    
    // Each producer creates 3 processes
    for (int i = 0; i < 3; i++) {
        // Create a new process
        Process p;
        
        // Wait for empty slot (P operation on empty semaphore)
        sem_wait(&sharedBuffer->empty);
        
        // Lock the buffer (enter critical section)
        pthread_mutex_lock(&sharedBuffer->mutex);
        
        // === CRITICAL SECTION START ===
        
        p.pid = sharedBuffer->processCounter++;
        p.arrivalTime = rand() % 10;
        p.burstTime = 1 + rand() % 10;
        p.priority = 1 + rand() % 5;
        p.remainingTime = p.burstTime;
        
        // Initialize resource needs (3 resource types)
        p.maxNeed = {rand() % 5, rand() % 5, rand() % 5};
        p.allocation = {0, 0, 0};
        p.remainingNeed = p.maxNeed;
        
        // Add process to buffer
        sharedBuffer->buffer.push(p);
        
        cout << "[PRODUCER " << pthread_self() << "] Created Process P" << p.pid 
             << " (Burst=" << p.burstTime << ", Priority=" << p.priority << ")" << endl;
        
        // === CRITICAL SECTION END ===
        
        // Unlock the buffer (exit critical section)
        pthread_mutex_unlock(&sharedBuffer->mutex);
        
        // Signal that buffer has one more item (V operation on full semaphore)
        sem_post(&sharedBuffer->full);
        
        sleep(1);  // Simulate time between creating processes
    }
    
    cout << "[PRODUCER " << pthread_self() << "] Finished creating processes" << endl;
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    SharedBuffer* sharedBuffer = (SharedBuffer*)arg;
    vector<Process>* processList = new vector<Process>();
    
    while (true) {
        // Wait for filled slot (P operation on full semaphore)
        sem_wait(&sharedBuffer->full);
        
        // Lock the buffer (enter critical section)
        pthread_mutex_lock(&sharedBuffer->mutex);
        
        // === CRITICAL SECTION START ===
        
        if (sharedBuffer->buffer.empty()) {
            // No more processes to consume
            pthread_mutex_unlock(&sharedBuffer->mutex);
            break;
        }
        
        // Fetch process from buffer
        Process p = sharedBuffer->buffer.front();
        sharedBuffer->buffer.pop();
        
        cout << "[CONSUMER] Fetched Process P" << p.pid << " from buffer" << endl;
        
        processList->push_back(p);
        
        // === CRITICAL SECTION END ===
        
        // Unlock the buffer (exit critical section)
        pthread_mutex_unlock(&sharedBuffer->mutex);
        
        // Signal that buffer has one more empty slot (V operation on empty semaphore)
        sem_post(&sharedBuffer->empty);
    }
    
    cout << "[CONSUMER] Finished fetching all processes" << endl;
    return (void*)processList;
}
