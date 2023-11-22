#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

sem_t empty, full;
pthread_mutex_t mutex;

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

int itemsToProduce, itemsToConsume;

void* producer(void* arg) {
    int item = 1;

    for (int i = 0; i < itemsToProduce; ++i) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }

    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < itemsToConsume; ++i) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }

    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread;
    printf("Enter the number of items to produce: ");
    scanf("%d", &itemsToProduce);
    printf("Enter the number of items to consume: ");
    scanf("%d", &itemsToConsume);

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
