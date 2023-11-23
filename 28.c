#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read the content of a file line by line
void read_file(char *file_name, char *pattern) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Could not open the file %s\n", file_name);
        return;
    }

    char line[1024];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;

        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", line_number, line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file_name> <pattern>\n", argv[0]);
        return 1;
    }

    char *file_name = argv[1];
    char *pattern = argv[2];

    read_file(file_name, pattern);

    return 0;
}
