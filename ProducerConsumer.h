#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include "Process.h"
#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <vector>

// Buffer size for ready queue
#define BUFFER_SIZE 10

// Shared data structure
struct SharedBuffer {
    std::queue<Process> buffer;      // Bounded buffer (ready queue)
    sem_t empty;                     // Counts empty slots
    sem_t full;                      // Counts filled slots
    pthread_mutex_t mutex;           // Mutual exclusion for buffer access
    bool producerDone;               // Flag to signal producers are done
    int processCounter;              // To generate unique PIDs
};

// Thread function declarations
void* producer(void* arg);
void* consumer(void* arg);

// Initialize and destroy semaphores
void initializeBuffer(SharedBuffer* sharedBuffer);
void destroyBuffer(SharedBuffer* sharedBuffer);

#endif
