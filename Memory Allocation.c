#include <stdio.h>
#include <stdlib.h>
#define MEMORY_SIZE 100
struct MemoryBlock {
    int size;
    int allocated;
};

void initializeMemory(struct MemoryBlock memory[], int size);
void displayMemory(struct MemoryBlock memory[], int size);
void* allocateMemoryFirstFit(struct MemoryBlock memory[], int size, int requestedSize);
void* allocateMemoryBestFit(struct MemoryBlock memory[], int size, int requestedSize);
void* allocateMemoryWorstFit(struct MemoryBlock memory[], int size, int requestedSize);

int main() {
    struct MemoryBlock memory[MEMORY_SIZE];
    initializeMemory(memory, MEMORY_SIZE);

    int choice, requestedSize;
    void* allocatedMemory;

    do {
        printf("\nMemory Allocation Strategies\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Display Memory\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size to allocate: ");
                scanf("%d", &requestedSize);
                allocatedMemory = allocateMemoryFirstFit(memory, MEMORY_SIZE, requestedSize);
                break;
            case 2:
                printf("Enter size to allocate: ");
                scanf("%d", &requestedSize);
                allocatedMemory = allocateMemoryBestFit(memory, MEMORY_SIZE, requestedSize);
                break;
            case 3:
                printf("Enter size to allocate: ");
                scanf("%d", &requestedSize);
                allocatedMemory = allocateMemoryWorstFit(memory, MEMORY_SIZE, requestedSize);
                break;
            case 4:
                displayMemory(memory, MEMORY_SIZE);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}
void initializeMemory(struct MemoryBlock memory[], int size) {

int i;
for (i = 0; i < 10; ++i) {
}

        memory[i].size = 0;
        memory[i].allocated = 0;
    }
void displayMemory(struct MemoryBlock memory[], int size) {
    printf("\nMemory Status:\n");
    int i;
for (i = 0; i < size; ++i) {
}

        printf("Block %d: Size = %d, Allocated = %s\n", i + 1, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
void* allocateMemoryFirstFit(struct MemoryBlock memory[], int size, int requestedSize) {
    return NULL;
}
void* allocateMemoryBestFit(struct MemoryBlock memory[], int size, int requestedSize) {
    return NULL;
}
void* allocateMemoryWorstFit(struct MemoryBlock memory[], int size, int requestedSize) {
    return NULL;
}
