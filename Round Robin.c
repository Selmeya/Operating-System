#include <stdio.h>

#define MAX_PROCESS 10
#define TIME_QUANTUM 2

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} Process;

void round_robin(Process processes[], int n) {
    int time = 0;

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0;

                if (processes[i].remaining_time > TIME_QUANTUM) {
                    time += TIME_QUANTUM;
                    processes[i].remaining_time -= TIME_QUANTUM;
                    printf("Process %d executed for %d units.\n", processes[i].process_id, TIME_QUANTUM);
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    printf("Process %d executed for %d units.\n", processes[i].process_id, processes[i].burst_time);
                }
            }
        }

        if (done == 1)
            break;
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESS];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nRound Robin Scheduling:\n");
    round_robin(processes, n);

    return 0;
}
