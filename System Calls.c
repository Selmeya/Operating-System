#include <stdio.h>
#include <unistd.h>

int main() {
    // Get the process identifier of the currently running process
    pid_t current_pid = getpid();
    pid_t parent_pid = getpid();

    printf("Current Process: PID=%d\n", current_pid);
    printf("Parent Process: PID=%d\n", parent_pid);

    return 0;
}
