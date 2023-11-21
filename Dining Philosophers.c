#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 2

pthread_mutex_t forks[MAX_PHILOSOPHERS];
pthread_t philosophers[MAX_PHILOSOPHERS];

struct ThreadData {
    pthread_t id;
    int philosopher_id;
};

void think(int philosopher_id) {
    printf("Philosopher %d is thinking\n", philosopher_id);
    sleep(rand() % 3 + 1);
}

void eat(int philosopher_id) {
    printf("Philosopher %d is eating\n", philosopher_id);
    sleep(rand() % 3 + 1);
}

void *philosopher(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int philosopher_id = data->philosopher_id;
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % MAX_PHILOSOPHERS;

    while (1) {
        think(philosopher_id);

        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d picked up left fork %d\n", philosopher_id, left_fork);

        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up right fork %d\n", philosopher_id, right_fork);

        eat(philosopher_id);

        pthread_mutex_unlock(&forks[left_fork]);
        printf("Philosopher %d put down left fork %d\n", philosopher_id, left_fork);

        pthread_mutex_unlock(&forks[right_fork]);
        printf("Philosopher %d put down right fork %d\n", philosopher_id, right_fork);
    }
}

int main() {
    srand(time(NULL));

    int num_philosophers;

    // Get the number of philosophers from the user
    printf("Enter the number of philosophers (up to %d): ", MAX_PHILOSOPHERS);
    scanf("%d", &num_philosophers);

    if (num_philosophers <= 1 || num_philosophers > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Exiting...\n");
        return 1;
    }

    for (int i = 0; i < num_philosophers; ++i) {
        pthread_mutex_init(&forks[i], NULL);
    }

    struct ThreadData thread_data[num_philosophers];

    for (int i = 0; i < num_philosophers; ++i) {
        thread_data[i].philosopher_id = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&thread_data[i]);
    }

    for (int i = 0; i < num_philosophers; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < num_philosophers; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
