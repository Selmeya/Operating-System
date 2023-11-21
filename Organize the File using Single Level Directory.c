#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_FILES_PER_DIR 10

struct File {
    char filename[MAX_FILENAME_LENGTH];
};

struct Directory {
    struct File files[MAX_FILES_PER_DIR];
    int numFiles;
};

void createFile(struct Directory* dir, const char* filename) {
    if (dir->numFiles < MAX_FILES_PER_DIR) {
        strcpy(dir->files[dir->numFiles].filename, filename);
        dir->numFiles++;
        printf("File '%s' created successfully.\n", filename);
    } else {
        printf("Cannot create more files in the directory.\n");
    }
}

void deleteFile(struct Directory* dir, const char* filename) {
    int i, found = 0;
    for (i = 0; i < dir->numFiles; i++) {
        if (strcmp(dir->files[i].filename, filename) == 0) {
            found = 1;

            for (int j = i; j < dir->numFiles - 1; j++) {
                strcpy(dir->files[j].filename, dir->files[j + 1].filename);
            }
            dir->numFiles--;
            printf("File '%s' deleted successfully.\n", filename);
            break;
        }
    }

    if (!found) {
        printf("File '%s' not found.\n", filename);
    }
}

void listFiles(const struct Directory* dir) {
    printf("Files in directory:\n");
    for (int i = 0; i < dir->numFiles; i++) {
        printf("- %s\n", dir->files[i].filename);
    }
}

int main() {
    struct Directory dir;
    dir.numFiles = 0;

    while (1) {
        printf("\n1. Create File\n2. Delete File\n3. List Files\n4. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    char filename[MAX_FILENAME_LENGTH];
                    printf("Enter the filename: ");
                    scanf("%s", filename);
                    createFile(&dir, filename);
                    break;
                }
            case 2:
                {
                    char filename[MAX_FILENAME_LENGTH];
                    printf("Enter the filename to delete: ");
                    scanf("%s", filename);
                    deleteFile(&dir, filename);
                    break;
                }
            case 3:
                listFiles(&dir);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

