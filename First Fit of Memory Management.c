#include <stdio.h>

struct Block {
    int size;
    int allocated;
};

void firstFit(struct Block blocks[], int m, int processSize[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blocks[j].allocated == 0 && blocks[j].size >= processSize[i]) {
                blocks[j].allocated = 1;

                printf("Process %d allocated to block %d\n", i + 1, j + 1);
                break;
            }
        }
    }
}

int main() {

    int m;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Block blocks[m];
    int processSize[n];

    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0;
    }

    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    firstFit(blocks, m, processSize, n);

    return 0;
}
