#include <stdio.h>
#include <stdlib.h>

// Structure to represent a file record
struct Record {
    int recordNumber;
    // Add other fields as needed
};

// Function to write a record to the file
void writeRecord(FILE *file, const struct Record *record) {
    fwrite(record, sizeof(struct Record), 1, file);
}

int main() {
    // File pointer
    FILE *file;

    // Open the file in binary mode for reading and writing
    file = fopen("file.dat", "rb+");

    // Check if the file exists; if not, create it
    if (file == NULL) {
        file = fopen("file.dat", "wb+");
        if (file == NULL) {
            fprintf(stderr, "Error opening file.\n");
            exit(1);
        }
    }

    // Simulation: Write records to the file
    struct Record records[3];  // Assuming 3 records for simplicity

    for (int i = 0; i < 3; ++i) {
        printf("Enter details for Record %d:\n", i + 1);
        printf("Record Number: ");
        scanf("%d", &records[i].recordNumber);
        // Add code to input other fields as needed

        writeRecord(file, &records[i]);
    }

    // Move the file pointer to the beginning of the file
    rewind(file);

    // Read and print each record
    struct Record readRecord;

    // Read records from the file
    while (fread(&readRecord, sizeof(struct Record), 1, file) == 1) {
        printf("Record Number: %d\n", readRecord.recordNumber);
        // Print other fields as needed
    }

    // Close the file
    fclose(file);

    return 0;
}
