#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 100
#define INDEX_BLOCK_SIZE 10

typedef struct {
    int index_block[INDEX_BLOCK_SIZE];
    char data_blocks[NUM_BLOCKS][BLOCK_SIZE];
} File;

void initializeFile(File *file) {
    for (int i = 0; i < INDEX_BLOCK_SIZE; ++i) {
        file->index_block[i] = -1;
    }

    for (int i = 0; i < NUM_BLOCKS; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            file->data_blocks[i][j] = '\0';
        }
    }
}

void writeFile(File *file) {
    int blockNumber;
    char data[BLOCK_SIZE];

    printf("Enter block number: ");
    scanf("%d", &blockNumber);

    if (blockNumber < 0 || blockNumber >= INDEX_BLOCK_SIZE) {
        printf("Invalid block number\n");
        return;
    }

    if (file->index_block[blockNumber] != -1) {
        printf("Block %d is already allocated\n", blockNumber);
        return;
    }

    printf("Enter data: ");
    scanf(" %[^\n]", data);

    file->index_block[blockNumber] = blockNumber;
    snprintf(file->data_blocks[blockNumber], BLOCK_SIZE, "%s", data);
    printf("Data written to block %d: %s\n", blockNumber, data);
}

void readFile(const File *file) {
    int blockNumber;

    printf("Enter block number: ");
    scanf("%d", &blockNumber);

    if (blockNumber < 0 || blockNumber >= INDEX_BLOCK_SIZE) {
        printf("Invalid block number\n");
        return;
    }

    if (file->index_block[blockNumber] == -1) {
        printf("Block %d is not allocated\n", blockNumber);
        return;
    }

    printf("Data in block %d: %s\n", blockNumber, file->data_blocks[blockNumber]);
}

int main() {
    File file;
    initializeFile(&file);

    char choice;
    do {
        printf("\n1. Write to file\n2. Read from file\n3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                writeFile(&file);
                break;
            case '2':
                readFile(&file);
                break;
            case '3':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != '3');

    return 0;
}
