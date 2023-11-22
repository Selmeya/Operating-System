#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> // Add this line to include the necessary header file

int main() {
    int fd;
    char buffer[50];

    // Get input from the user
    printf("Enter some text: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Create a new file
    fd = open("file.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the user's input to the file
    if (write(fd, buffer, sizeof(buffer)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Open the file
    fd = open("file.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the data from the file
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Print the read data
    printf("Data read from file: %s\n", buffer);

    // Delete the file
    if (unlink("file.txt") == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
