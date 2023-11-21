#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int sharedCounter = 0;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int* iterations = (int*)arg;

    for (int i = 0; i < *iterations; ++i) {
        pthread_mutex_lock(&mutex);

        // Critical section
        sharedCounter++;
        printf("Produced: %d\n", sharedCounter);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumer(void* arg) {
    int* iterations = (int*)arg;

    for (int i = 0; i < *iterations; ++i) {
        pthread_mutex_lock(&mutex);

        // Critical section
        printf("Consumed: %d\n", sharedCounter);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int iterations;

    // Get user input for the number of iterations
    printf("Enter the number of iterations: ");
    scanf("%d", &iterations);

    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }

    // Create producer and consumer threads
    if (pthread_create(&threads[0], NULL, producer, &iterations) != 0 ||
        pthread_create(&threads[1], NULL, consumer, &iterations) != 0) {
        fprintf(stderr, "Thread creation failed\n");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

