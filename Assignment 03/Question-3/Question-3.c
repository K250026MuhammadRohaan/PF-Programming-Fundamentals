#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee e[], int n);
void findHighestSalary(struct Employee e[], int n);
void searchEmployee(struct Employee e[], int n);
void updateLowSalaries(struct Employee e[], int n, float threshold);
void clearStdin();

int main() {
    int n;
    printf("Enter number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }
    clearStdin();

    struct Employee *emp = malloc(n * sizeof(struct Employee));
    if (!emp) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Employee %d ---\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &emp[i].id);
        clearStdin();

        printf("Enter Name: ");
        fgets(emp[i].name, sizeof(emp[i].name), stdin);
        emp[i].name[strcspn(emp[i].name, "\n")] = 0;

        printf("Enter Designation: ");
        fgets(emp[i].designation, sizeof(emp[i].designation), stdin);
        emp[i].designation[strcspn(emp[i].designation, "\n")] = 0;

        printf("Enter Salary: ");
        scanf("%f", &emp[i].salary);
        clearStdin();
    }

    int choice;
    while (1) {
        printf("\n--- Employee Management Menu ---\n");
        printf("1. Display all employees\n");
        printf("2. Find employee with highest salary\n");
        printf("3. Search employee\n");
        printf("4. Update salaries below threshold (+10%% bonus)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearStdin();
            printf("Invalid input. Try again.\n");
            continue;
        }
        clearStdin();

        switch (choice) {
            case 1:
                displayEmployees(emp, n);
                break;
            case 2:
                findHighestSalary(emp, n);
                break;
            case 3:
                searchEmployee(emp, n);
                break;
            case 4: {
                float threshold;
                printf("Enter salary threshold: ");
                if (scanf("%f", &threshold) != 1) {
                    clearStdin();
                    printf("Invalid input.\n");
                    break;
                }
                clearStdin();
                updateLowSalaries(emp, n, threshold);
                printf("Salaries updated successfully.\n");
                break;
            }
            case 5:
                free(emp);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void displayEmployees(struct Employee e[], int n) {
    if (n == 0) {
        printf("No employee records found.\n");
        return;
    }

    printf("\n%-10s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-20s %-10.2f\n", e[i].id, e[i].name, e[i].designation, e[i].salary);
    }
}

void findHighestSalary(struct Employee e[], int n) {
    if (n == 0) {
        printf("No employee records.\n");
        return;
    }

    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (e[i].salary > e[idx].salary) {
            idx = i;
        }
    }

    printf("\nEmployee with highest salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           e[idx].id, e[idx].name, e[idx].designation, e[idx].salary);
}

void searchEmployee(struct Employee e[], int n) {
    if (n == 0) {
        printf("No employee records.\n");
        return;
    }

    int choice;
    printf("Search by: 1) ID  2) Name : ");
    if (scanf("%d", &choice) != 1) {
        clearStdin();
        printf("Invalid input.\n");
        return;
    }
    clearStdin();

    if (choice == 1) {
        int id;
        printf("Enter Employee ID: ");
        if (scanf("%d", &id) != 1) {
            clearStdin();
            printf("Invalid input.\n");
            return;
        }
        clearStdin();

        for (int i = 0; i < n; i++) {
            if (e[i].id == id) {
                printf("Employee Found!\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       e[i].id, e[i].name, e[i].designation, e[i].salary);
                return;
            }
        }
        printf("Employee NOT FOUND.\n");
    } else if (choice == 2) {
        char name[50];
        printf("Enter Employee Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        for (int i = 0; i < n; i++) {
            if (strcmp(e[i].name, name) == 0) {
                printf("Employee Found!\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       e[i].id, e[i].name, e[i].designation, e[i].salary);
                return;
            }
        }
        printf("Employee NOT FOUND.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void updateLowSalaries(struct Employee e[], int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (e[i].salary < threshold) {
            e[i].salary += e[i].salary * 0.10f;
        }
    }
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}