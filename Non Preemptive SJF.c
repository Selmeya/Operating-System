#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
} Process;

void swap(Process *xp, Process *yp) {
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void sjf_non_preemptive(Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];

    completion_time[0] = processes[0].burst_time;
    turnaround_time[0] = completion_time[0] - processes[0].arrival_time;
    waiting_time[0] = turnaround_time[0] - processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        completion_time[i] = completion_time[i - 1] + processes[i].burst_time;
        turnaround_time[i] = completion_time[i] - processes[i].arrival_time;
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
    }

    printf("Process\t Arrival Time\t Burst Time\t Completion Time\t Turnaround Time\t Waiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               completion_time[i],
               turnaround_time[i],
               waiting_time[i]);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    printf("Enter the arrival time and burst time for each process:\n");

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    sjf_non_preemptive(processes, n);

    free(processes);

    return 0;
}
