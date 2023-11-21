#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

void addEmployee(FILE *file) {
    struct Employee employee;

    printf("Enter Employee ID: ");
    scanf("%d", &employee.empId);
    printf("Enter Employee Name: ");
    scanf("%s", employee.empName);
    printf("Enter Employee Salary: ");
    scanf("%f", &employee.empSalary);

    fseek(file, 0, SEEK_END);

    fwrite(&employee, sizeof(struct Employee), 1, file);

    printf("Employee added successfully.\n");
}

void displayAllEmployees(FILE *file) {
    struct Employee employee;

    fseek(file, 0, SEEK_SET);

    printf("\nEmployee Records:\n");
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", employee.empId, employee.empName, employee.empSalary);
    }
}

void updateEmployee(FILE *file) {
    int empId;
    printf("Enter Employee ID to update: ");
    scanf("%d", &empId);

    struct Employee employee;
    int found = 0;

    fseek(file, 0, SEEK_SET);

    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.empId == empId) {
            found = 1;

            printf("Enter new Employee Name: ");
            scanf("%s", employee.empName);
            printf("Enter new Employee Salary: ");
            scanf("%f", &employee.empSalary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);

            fwrite(&employee, sizeof(struct Employee), 1, file);

            printf("Employee updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", empId);
    }
}

// Function to delete an employee record based on the employee ID
void deleteEmployee(FILE *file) {
    int empId;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &empId);

    struct Employee employee;
    int found = 0;

    fseek(file, 0, SEEK_SET);

    FILE *tempFile = fopen("temp.dat", "wb");

    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.empId != empId) {
            fwrite(&employee, sizeof(struct Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("employee.dat");

    rename("temp.dat", "employee.dat");

    if (found) {
        printf("Employee with ID %d deleted successfully.\n", empId);
    } else {
        printf("Employee with ID %d not found.\n", empId);
    }
}

int main() {
    FILE *file = fopen("employee.dat", "ab+");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int choice;

    do {
        printf("\nEmployee Record Management\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                displayAllEmployees(file);
                break;
            case 3:
                updateEmployee(file);
                break;
            case 4:
                deleteEmployee(file);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    fclose(file);

    return 0;
}
