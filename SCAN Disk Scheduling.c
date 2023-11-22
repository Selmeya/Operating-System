#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total head movement in SCAN
int calculateTotalHeadMovement(const int requestQueue[], int numRequests, int initialHeadPosition, int maxCylinder) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;

    // Flag to represent the direction of movement (1 for increasing, -1 for decreasing)
    int direction = 1;

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

    // Simulation of SCAN algorithm
    while (1) {
        // Scan in the current direction
        for (int i = 0; i < numRequests; ++i) {
            if ((direction == 1 && sortedRequests[i] >= currentHeadPosition) ||
                (direction == -1 && sortedRequests[i] <= currentHeadPosition)) {
                // Move to the current request position
                totalHeadMovement += abs(sortedRequests[i] - currentHeadPosition);
                currentHeadPosition = sortedRequests[i];
                printf("Servicing request at cylinder %d\n", currentHeadPosition);

                // Mark this request as serviced
                sortedRequests[i] = -1;
            }
        }

        // Change direction if necessary
        direction = -direction;

        // Check if there are still requests to be serviced in the opposite direction
        int remainingRequests = 0;
        for (int i = 0; i < numRequests; ++i) {
            if (sortedRequests[i] != -1) {
                remainingRequests = 1;
                break;
            }
        }

        // Break the loop if there are no more requests
        if (!remainingRequests) {
            break;
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

    // Calculate total head movement using SCAN algorithm
    int totalHeadMovement = calculateTotalHeadMovement(requestQueue, numRequests, initialHeadPosition, maxCylinder);

    // Display the result
    printf("Total head movement using SCAN: %d\n", totalHeadMovement);

    // Free dynamically allocated memory
    free(requestQueue);

    return 0;
}
