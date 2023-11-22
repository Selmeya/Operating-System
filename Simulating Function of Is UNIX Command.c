#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void listDirectoryContents(const char *path) {
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(path);
    if (directory == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read and print the directory contents
    printf("Contents of directory '%s':\n", path);
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directory);
}

int main(int argc, char *argv[]) {
    // If a directory is provided as a command-line argument, use it; otherwise, use the current directory
    const char *directoryPath = (argc > 1) ? argv[1] : ".";

    listDirectoryContents(directoryPath);

    return 0;
}
