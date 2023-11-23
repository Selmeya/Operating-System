#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
    // Open file
    printf("Using open for file: example.txt\n");
    int file_descriptor = open("hello.txt", O_RDWR);
    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    // Seek to the beginning of the file
    printf("Using lseek to move to the beginning of the file\n");
    lseek(file_descriptor, 0, SEEK_SET);

    // Get file information using stat
    printf("Using stat to get file information\n");
    struct stat file_info;
    if (stat("hello.txt", &file_info) == -1) {
        perror("Error getting file information");
        close(file_descriptor);
        return 1;
    }

    printf("File size: %ld bytes\n", file_info.st_size);

    // Open the current directory
    printf("Using opendir for the current directory\n");
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        close(file_descriptor);
        return 1;
    }

    printf("Files in the current directory:\n");

    // Read directory entries
    printf("Using readdir to read directory entries\n");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Clean up
    closedir(dir);
    close(file_descriptor);

    return 0;
}

