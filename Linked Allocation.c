#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512
#define MAX_BLOCKS 100

// Structure to represent a block in the file
typedef struct Block {
    char data[BLOCK_SIZE];
    struct Block* next;
} Block;

// Structure to represent a file
typedef struct {
    Block* firstBlock;
    Block* lastBlock;
} File;

// Function to initialize a file
void initializeFile(File* file) {
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

// Function to write data to the file
void writeFile(File* file, const char* data) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    if (newBlock == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    snprintf(newBlock->data, BLOCK_SIZE, "%s", data);
    newBlock->next = NULL;

    if (file->firstBlock == NULL) {
        // If it's the first block in the file
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        // If there are already blocks in the file
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }

    printf("Data written to file: %s\n", data);
}

// Function to read data from the file
void readFile(const File* file) {
    Block* currentBlock = file->firstBlock;

    while (currentBlock != NULL) {
        printf("Data in block: %s\n", currentBlock->data);
        currentBlock = currentBlock->next;
    }
}

// Function to free the allocated memory for the file blocks
void freeFile(File* file) {
    Block* currentBlock = file->firstBlock;
    Block* nextBlock;

    while (currentBlock != NULL) {
        nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    // Reset file structure
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

int main() {
    File file;
    initializeFile(&file);

    char choice;
    char data[BLOCK_SIZE];

    do {
        printf("\n1. Write to file\n2. Read from file\n3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter data to write: ");
                scanf(" %[^\n]", data);
                writeFile(&file, data);
                break;
            case '2':
                printf("Reading data from file:\n");
                readFile(&file);
                break;
            case '3':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != '3');

    // Free allocated memory before exiting
    freeFile(&file);

    return 0;
}
