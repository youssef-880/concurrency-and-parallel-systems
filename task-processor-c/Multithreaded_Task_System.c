#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_WORKERS 4
#define TOTAL_TASKS 12

int task_list[TOTAL_TASKS];
int next_task_index = 0;

// 1. Mutex: Prevents "Race Conditions" when picking a task
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

// 2. Semaphore: Controls the flow of available work
sem_t tasks_available;

void* start_worker(void* arg) {
    int id = *(int*)arg;
    
    while (1) {
        // 3. Semaphore Wait: Worker sleeps if no tasks are ready
        sem_wait(&tasks_available);

        pthread_mutex_lock(&queue_lock);
        
        // Check if all work is done
        if (next_task_index >= TOTAL_TASKS) {
            pthread_mutex_unlock(&queue_lock);
            break;
        }

        // Process the task
        int task_id = task_list[next_task_index];
        printf("[Worker %d] Processing Task #%d...\n", id, task_id);
        next_task_index++;

        pthread_mutex_unlock(&queue_lock);

        // Simulate varying processing times (0.1 to 0.5 seconds)
        usleep((rand() % 400 + 100) * 1000);
    }
    
    printf("Worker %d: All assigned tasks complete. Powering down.\n", id);
    return NULL;
}

int main() {
    pthread_t workers[NUM_WORKERS];
    int worker_ids[NUM_WORKERS];

    // Initialize shared task list
    for (int i = 0; i < TOTAL_TASKS; i++) task_list[i] = i + 1;

    // Initialize synchronization tools
    sem_init(&tasks_available, 0, 0);

    // Create worker threads
    for (int i = 0; i < NUM_WORKERS; i++) {
        worker_ids[i] = i + 1;
        pthread_create(&workers[i], NULL, start_worker, &worker_ids[i]);
    }

    // "Release" tasks to the workers
    for (int i = 0; i < TOTAL_TASKS; i++) {
        sem_post(&tasks_available);
    }

    // 4. Thread Join: Ensures main program doesn't exit early
    for (int i = 0; i < NUM_WORKERS; i++) {
        pthread_join(workers[i], NULL);
    }

    printf("\n--- System Shutdown: All tasks processed successfully ---\n");

    sem_destroy(&tasks_available);
    pthread_mutex_destroy(&queue_lock);

    return 0;
}