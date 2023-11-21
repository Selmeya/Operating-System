#include <stdio.h>
#include <stdbool.h>

#define PROCESSES 5
#define RESOURCES 3

bool safeState(int available[], int max[PROCESSES][RESOURCES], int allocation[PROCESSES][RESOURCES]) {
    int work[RESOURCES];
    bool finish[PROCESSES];
    int safe[PROCESSES];
    int count = 0;

    for (int i = 0; i < RESOURCES; i++)
        work[i] = available[i];

    for (int i = 0; i < PROCESSES; i++)
        finish[i] = false;

    while (count < PROCESSES) {
        bool found = false;

        for (int i = 0; i < PROCESSES; i++) {
            if (finish[i] == false) {
                int j;
                for (j = 0; j < RESOURCES; j++) {
                    if (allocation[i][j] > work[j])
                        break;
                }

                if (j == RESOURCES) {
                    safe[count++] = i;
                    finish[i] = true;
                    found = true;

                    for (int k = 0; k < RESOURCES; k++)
                        work[k] += allocation[i][k];
                }
            }
        }

        if (found == false)
            break;
    }

    if (count == PROCESSES)
        return true;
    else
        return false;
}

int main() {
    int available[RESOURCES], max[PROCESSES][RESOURCES], allocation[PROCESSES][RESOURCES];

    printf("Enter the number of available resources: ");
    for (int i = 0; i < RESOURCES; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum resources required for each process:\n");
    for (int i = 0; i < PROCESSES; i++) {
        printf("P%d: ", i + 1);
        for (int j = 0; j < RESOURCES; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter the currently allocated resources for each process:\n");
    for (int i = 0; i < PROCESSES; i++) {
        printf("P%d: ", i + 1);
        for (int j = 0; j < RESOURCES; j++)
            scanf("%d", &allocation[i][j]);
    }

    if (safeState(available, max, allocation))
        printf("System is in safe state.\n");
    else
        printf("System is not in safe state.\n");

    return 0;
}
