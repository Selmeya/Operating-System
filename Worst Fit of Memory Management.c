#include <stdio.h>

#define MAX_BLOCKS 5

int memory_blocks[MAX_BLOCKS];
int process_sizes[MAX_BLOCKS];

void initializeMemory() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        memory_blocks[i] = -1; // -1 indicates that the block is unallocated
        process_sizes[i] = 0;
    }
}

void displayMemoryStatus() {
    printf("\nMemory Status:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory_blocks[i] == -1) {
            printf("Block %d: Unallocated\n", i + 1);
        } else {
            printf("Block %d: Allocated, Size: %d\n", i + 1, memory_blocks[i]);
        }
    }
    printf("\n");
}

void worstFit(int process_size) {
    int index = -1;
    int worst_fit_size = -1;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory_blocks[i] == -1) {
            if (worst_fit_size == -1 || process_sizes[i] > worst_fit_size) {
                index = i;
                worst_fit_size = process_sizes[i];
            }
        }
    }

    if (index != -1) {
        memory_blocks[index] = process_size;
        printf("Process of size %d allocated to Block %d using Worst Fit\n", process_size, index + 1);
    } else {
        printf("Unable to allocate process of size %d using Worst Fit\n", process_size);
    }
}


int main() {
    initializeMemory();

    int choice, process_size;

    do {
        printf("1. Allocate Memory\n");
        printf("2. Display Memory Status\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size of the process: ");
                scanf("%d", &process_size);
                worstFit(process_size);
                break;
            case 2:
                displayMemoryStatus();
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
