#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InstructionSet2.h"

int main() {
    studentset_t studentSet;
    initializeStudentSet(&studentSet);

    int choice;

    do {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Add Course for a Student\n");
        printf("3. Search Student by ID\n");
        printf("4. Search Student by Surname\n");
        printf("5. Calculate Average Grade for a Student\n");
        printf("6. Delete Student\n");
        printf("7. Delete Course for a Student\n");
        printf("8. Save to File\n");
        printf("9. Load from File\n");
        printf("10. Show All Students\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&studentSet);
                break;
            case 2:
                addCourseForStudent(&studentSet);
                break;
            case 3:
                searchStudentById(&studentSet);
                break;
            case 4:
                searchStudentBySurname(&studentSet);
                break;
            case 5:
                calculateAverageGrade(&studentSet);
                break;
            case 6:
                deleteStudent(&studentSet);
                break;
            case 7:
                deleteCourseForStudent(&studentSet);
                break;
            case 8:
                saveToFile(&studentSet);
                break;
            case 9:
                loadFromFile(&studentSet);
                break;
            case 10:
                showAllStudents(&studentSet);
                break;
            case 0:
                // Free allocated memory before exiting
                freeStudentSet(&studentSet);
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 11.\n");
        }
    } while (choice != 0);

    return 0;
}
