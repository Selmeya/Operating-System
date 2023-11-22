#include <stdio.h>
#include <pthread.h>

// Structure to hold data passed to the thread
struct ThreadData {
    int threadNumber;
    char message[100];
};

// Thread function
void *threadFunction(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    printf("Thread %d: %s\n", data->threadNumber, data->message);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;
    struct ThreadData data1, data2;

    // (i) Create: Taking input from the user
    printf("Enter message for thread 1: ");
    fgets(data1.message, sizeof(data1.message), stdin);
    data1.threadNumber = 1;

    printf("Enter message for thread 2: ");
    fgets(data2.message, sizeof(data2.message), stdin);
    data2.threadNumber = 2;

    // Creating two threads
    if (pthread_create(&tid1, NULL, threadFunction, (void *)&data1) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    if (pthread_create(&tid2, NULL, threadFunction, (void *)&data2) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 2;
    }

    // (iii) Equal: Check if two threads are equal
    if (pthread_equal(tid1, tid2)) {
        printf("Threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }

    // (ii) Join: Wait for the threads to finish
    if (pthread_join(tid1, NULL) != 0) {
        fprintf(stderr, "Error joining thread 1\n");
        return 3;
    }

    if (pthread_join(tid2, NULL) != 0) {
        fprintf(stderr, "Error joining thread 2\n");
        return 4;
    }

    // (iv) Exit: The main thread is about to exit
    printf("Back in the main thread. Main thread is about to exit.\n");

    return 0;
}
