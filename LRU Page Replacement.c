#include <stdio.h>

#define MAX_FRAMES 3

int pageFrames[MAX_FRAMES];
int pageOrder[MAX_FRAMES];
int counter = 0;

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
            // Update page order when the page is accessed
            pageOrder[i] = counter++;
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

// Function to add a page to memory using LRU
void addToMemory(int page) {
    // Find the least recently used page in memory
    int minIndex = 0;
    for (int i = 1; i < MAX_FRAMES; i++) {
        if (pageOrder[i] < pageOrder[minIndex]) {
            minIndex = i;
        }
    }

    // Replace the least recently used page with the new page
    pageFrames[minIndex] = page;
    pageOrder[minIndex] = counter++;
}

int main() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1; // Initialize page frames to -1 (empty)
        pageOrder[i] = 0;   // Initialize page order to 0
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
            addToMemory(pages[i]);
            display();
        } else {
            printf("Page %d is already in memory.\n", pages[i]);
        }
    }

    return 0;
}
