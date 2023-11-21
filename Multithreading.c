#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_MESSAGE_SIZE 100
struct ThreadData {
    pthread_t id;
    char message[MAX_MESSAGE_SIZE];
};
void *printMessage(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    printf("Thread ID %lu Message: %s\n", data->id, data->message);
    pthread_exit(NULL);
}

int main() {
    struct ThreadData thread1, thread2;
    printf("Enter message for Thread 1: ");
    fgets(thread1.message, MAX_MESSAGE_SIZE, stdin);
    printf("Enter message for Thread 2: ");
    fgets(thread2.message, MAX_MESSAGE_SIZE, stdin);
    if (pthread_create(&thread1.id, NULL, printMessage, (void *)&thread1) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread2.id, NULL, printMessage, (void *)&thread2) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_join(thread1.id, NULL);
    pthread_join(thread2.id, NULL);

    printf("Main Thread: All threads have finished.\n");

    return 0;
}
