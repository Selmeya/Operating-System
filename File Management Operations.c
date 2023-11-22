#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char fileName[] = "os25.txt";

    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "This is a sample text written to the file.\n");
    fprintf(file, "File management operations in C.\n");

    fclose(file);

    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    printf("Contents of the file:\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    file = fopen(fileName, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }


    fclose(file);
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file for reading after appending");
        exit(EXIT_FAILURE);
    }
    printf("\nContents of the file after appending:\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);

    return 0;
}
