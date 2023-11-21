#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main() {
    char *shared_memory = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write data to the shared memory
    printf("Enter data to write to shared memory: ");
    fgets(shared_memory, SHM_SIZE, stdin);

    // Process 2
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process reads from shared memory
        sleep(1); // Ensure that the parent has written to shared memory
        printf("Child Process: Data read from shared memory: %s", shared_memory);
    } else {
        // Parent process waits for the child to finish
        wait(NULL);
    }

    munmap(shared_memory, SHM_SIZE); // Unmap the shared memory

    return 0;
}
