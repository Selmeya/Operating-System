#include <stdio.h>

#define MAX_FRAMES 3

int pageFrames[MAX_FRAMES];
int pageQueue[MAX_FRAMES];
int front = -1, rear = -1;

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

// Function to add a page to memory using FIFO
void addToMemory(int page) {
    if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX_FRAMES;
        if (front == rear) {
            front = (front + 1) % MAX_FRAMES;
        }
    }

    pageFrames[rear] = page;
    pageQueue[rear] = page;
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
            addToMemory(pages[i]);
            display();
        } else {
            printf("Page %d is already in memory.\n", pages[i]);
        }
    }

    return 0;
}
