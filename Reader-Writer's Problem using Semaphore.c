#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 10
#define MAX_WRITERS 10
#define MAX_ITERATIONS 5

pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
sem_t mutex, write_mutex;
int data = 0, readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    int i;
    for (i = 0; i < MAX_ITERATIONS; i++) {
        usleep(1000000); // Simulate some work

        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&write_mutex);
        }
        sem_post(&mutex);

        // Read data
        printf("Reader %d read data: %d\n", reader_id, data);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&write_mutex);
        }
        sem_post(&mutex);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    int i;
    for (i = 0; i < MAX_ITERATIONS; i++) {
        usleep(1500000); // Simulate some work

        sem_wait(&write_mutex);

        // Write data
        data++;
        printf("Writer %d wrote data: %d\n", writer_id, data);

        sem_post(&write_mutex);
    }
    pthread_exit(NULL);
}

int main() {
    int num_readers, num_writers, i, reader_id[MAX_READERS], writer_id[MAX_WRITERS];

    printf("Enter the number of readers (up to %d): ", MAX_READERS);
    scanf("%d", &num_readers);

    printf("Enter the number of writers (up to %d): ", MAX_WRITERS);
    scanf("%d", &num_writers);

    if (num_readers <= 0 || num_writers <= 0) {
        printf("Invalid number of readers or writers. Exiting.\n");
        return 1;
    }

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    for (i = 0; i < num_readers; i++) {
        reader_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    for (i = 0; i < num_writers; i++) {
        writer_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_id[i]);
    }

    for (i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    for (i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_mutex);

    return 0;
}
