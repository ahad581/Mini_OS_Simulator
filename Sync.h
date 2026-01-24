#ifndef SYNC_H
#define SYNC_H

#include <semaphore.h>
#include <pthread.h>
#include <queue>
#include "Process.h"

// The Bounded Buffer (Ready Queue)
const int BUFFER_SIZE = 10; // You can change this size
extern std::queue<Process> readyQueue;

// Synchronization Tools
extern sem_t emptySlots;  // Tracks how many empty spaces are in the buffer
extern sem_t fullSlots;   // Tracks how many processes are ready to be picked up
extern pthread_mutex_t queueLock; // Ensures only one thread touches the queue at a time

#endif
