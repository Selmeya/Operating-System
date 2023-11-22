#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement in FCFS
int calculateTotalHeadMovement(const int requestQueue[], int numRequests, int initialHeadPosition) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;

    for (int i = 0; i < numRequests; ++i) {
        // Calculate the absolute difference between the current request and the current head position
        totalHeadMovement += abs(requestQueue[i] - currentHeadPosition);

        // Move the head to the current request position
        currentHeadPosition = requestQueue[i];
    }

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

    int initialHeadPosition;
    printf("Enter the initial head position: ");
    scanf("%d", &initialHeadPosition);

    // Calculate total head movement using FCFS algorithm
    int totalHeadMovement = calculateTotalHeadMovement(requestQueue, numRequests, initialHeadPosition);

    // Display the result
    printf("Total head movement using FCFS: %d\n", totalHeadMovement);

    // Free dynamically allocated memory
    free(requestQueue);

    return 0;
}
