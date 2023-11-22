#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 3

int pageFrames[MAX_FRAMES];

// Function to display the content of page frames
void display() {
    printf("Page Frames: ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", pageFrames[i]);
        }
    }
    printf("\n");
}

// Function to check if a page is already in memory
int isInMemory(int page) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (pageFrames[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

// Function to find the page that will not be used for the longest time
int findOptimalPage(int pages[], int start, int end) {
    int farthest = start;
    int farthestIndex = -1;

    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = start; j < end; j++) {
            if (pageFrames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    farthestIndex = i;
                }
                break;
            }
        }

        // If the page is not found in future, it's the optimal page to replace
        if (j == end) {
            return i;
        }
    }

    // If all pages will be used in the future, replace the farthest one
    return farthestIndex;
}

int main() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1; // Initialize page frames to -1 (empty)
    }

    int totalRequests;

    printf("Enter the total number of page requests: ");
    scanf("%d", &totalRequests);

    int pages[totalRequests];

    printf("Enter the page requests (separated by spaces):\n");
    for (int i = 0; i < totalRequests; i++) {
        scanf("%d", &pages[i]);
    }

    for (int i = 0; i < totalRequests; i++) {
        printf("Page Request: %d\n", pages[i]);

        if (!isInMemory(pages[i])) {
            printf("Page Fault! Adding page %d to memory.\n", pages[i]);

            // Find the optimal page to replace
            int index = findOptimalPage(pages, i + 1, totalRequests);

            // Replace the optimal page with the new page
            pageFrames[index] = pages[i];
            display();
        } else {
            printf("Page %d is already in memory.\n", pages[i]);
        }
    }

    return 0;
}
