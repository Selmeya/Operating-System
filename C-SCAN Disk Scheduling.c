#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement in C-SCAN
int calculateTotalHeadMovement(const int requestQueue[], int numRequests, int initialHeadPosition, int maxCylinder) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;

    // Sort the request queue
    int *sortedRequests = (int *)malloc(numRequests * sizeof(int));
    for (int i = 0; i < numRequests; ++i) {
        sortedRequests[i] = requestQueue[i];
    }
    // Simple bubble sort for demonstration purposes (you may want to use a more efficient sorting algorithm in practice)
    for (int i = 0; i < numRequests - 1; ++i) {
        for (int j = 0; j < numRequests - i - 1; ++j) {
            if (sortedRequests[j] > sortedRequests[j + 1]) {
                // Swap elements if they are in the wrong order
                int temp = sortedRequests[j];
                sortedRequests[j] = sortedRequests[j + 1];
                sortedRequests[j + 1] = temp;
            }
        }
    }

    // Simulation of C-SCAN algorithm
    int i;
    for (i = 0; i < numRequests; ++i) {
        if (sortedRequests[i] >= currentHeadPosition) {
            // Move to the current request position
            totalHeadMovement += abs(sortedRequests[i] - currentHeadPosition);
            currentHeadPosition = sortedRequests[i];
            printf("Servicing request at cylinder %d\n", currentHeadPosition);
        }
    }

    // Move to the beginning of the disk (cylinder 0)
    totalHeadMovement += abs(0 - currentHeadPosition);
    currentHeadPosition = 0;

    // Continue scanning in the same direction
    for (i = 0; i < numRequests; ++i) {
        if (sortedRequests[i] >= currentHeadPosition) {
            // Move to the current request position
            totalHeadMovement += abs(sortedRequests[i] - currentHeadPosition);
            currentHeadPosition = sortedRequests[i];
            printf("Servicing request at cylinder %d\n", currentHeadPosition);
        }
    }

    // Free dynamically allocated memory
    free(sortedRequests);

    return totalHeadMovement;
}

int main() {
    int numRequests;

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0) {
        printf("Invalid number of requests. Exiting program.\n");
        return 1;
    }

    int *requestQueue = (int *)malloc(numRequests * sizeof(int));

    if (requestQueue == NULL) {
        fprintf(stderr, "Memory allocation error. Exiting program.\n");
        return 1;
    }

    printf("Enter the disk request queue:\n");
    for (int i = 0; i < numRequests; ++i) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requestQueue[i]);
    }

    int initialHeadPosition, maxCylinder;
    printf("Enter the initial head position: ");
    scanf("%d", &initialHeadPosition);

    printf("Enter the maximum cylinder: ");
    scanf("%d", &maxCylinder);

    // Calculate total head movement using C-SCAN algorithm
    int totalHeadMovement = calculateTotalHeadMovement(requestQueue, numRequests, initialHeadPosition, maxCylinder);

    // Display the result
    printf("Total head movement using C-SCAN: %d\n", totalHeadMovement);

    // Free dynamically allocated memory
    free(requestQueue);

    return 0;
}
