#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "InstructionSet2.h"

void initializeStudentSet(studentset_t *studentSet) {
    // Initialize the student set
    studentSet->head = NULL;  // Initialize the head pointer to NULL
    studentSet->num_students = 0; // Initially, there are no students
}

void addStudent(studentset_t *studentSet) {
    // Increment the number of students
    studentSet->num_students++;

    // Initialize the new student
    student_t *newStudent = (student_t *)malloc(sizeof(student_t));
    newStudent->id = studentSet->num_students;

    // Allocate memory for the name
    newStudent->name = (char *)malloc(50 * sizeof(char));

    // Input validation for name (letters only)
    do {
        printf("Enter student name: ");
        scanf("%s", newStudent->name);

        // Check if the entered name contains only letters
        if (!isAlphaString(newStudent->name)) {
            printf("Invalid input. Name should contain only letters.\n");
        }

    } while (!isAlphaString(newStudent->name));

    // Allocate memory for the surname
    newStudent->surname = (char *)malloc(50 * sizeof(char));

    // Input validation for surname (letters only)
    do {
        printf("Enter student surname: ");
        scanf("%s", newStudent->surname);

        // Check if the entered surname contains only letters
        if (!isAlphaString(newStudent->surname)) {
            printf("Invalid input. Surname should contain only letters.\n");
        }

    } while (!isAlphaString(newStudent->surname));

    // Input validation for age (numbers only)
    do {
        printf("Enter student age: ");

        // Check if the entered age is a number
        if (scanf("%d", &(newStudent->age)) != 1) {
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
            printf("Invalid input. Age should be a number.\n");
            continue;
        }

        // Check if the entered age is non-negative
        if (newStudent->age < 0) {
            printf("Invalid input. Age should be a non-negative number.\n");
            continue;
        }

        // Exit the loop if age is valid
        break;

    } while (1);

    // Initialize the courses structure
    newStudent->courses = (courseset_t *)malloc(sizeof(courseset_t));
    newStudent->courses->head = NULL;
    newStudent->courses->numCourses = 0;

    // Update the newly allocated student in the linked list
    newStudent->next = studentSet->head;
    studentSet->head = newStudent;

    // Sort the linked list of students alphabetically by surname and name
    sortStudents(studentSet);

    printf("Student added successfully\n");
}

void addCourseForStudent(studentset_t *studentset) {
    // Get student search criteria and index
    int studentID;
    char searchKey[50];
    int studentIndex = getStudentSearchCriteria(studentset, &studentID, searchKey);

    // If the student is not found, return from the function
    if (studentIndex == -1) {
        return;
    }

    // Ask for the number of courses to add
    int numCourses;
    printf("Enter the number of courses to add: ");

    // Input validation for the number of courses
    while (scanf("%d", &numCourses) != 1) {
        printf("Invalid input. Please enter a number.\n");

        // Clear the input buffer
        while (getchar() != '\n');
        printf("Enter the number of courses to add: ");
    }

    // Add courses for the student
    for (int i = 0; i < numCourses; i++) {
        course_t *newCourse = (course_t *)malloc(sizeof(course_t));

        // Allocate memory for the course name
        newCourse->name = malloc(50 * sizeof(char));

        // Validate that the course name contains only letters
        do {
            printf("Enter course name for course %d (letters only): ", i + 1);
            scanf("%49s", newCourse->name);

            // Check if the entered course name contains only letters
            if (!isAlphaString(newCourse->name)) {
                printf("Invalid input. Course name should contain only letters.\n");
            }
        } while (!isAlphaString(newCourse->name));

        // Validate the grade input (0-10)
        while (1) {
            printf("Enter grade for course %d (0-10): ", i + 1);

            if (scanf("%d", &(newCourse->grade)) == 1 && newCourse->grade >= 0 && newCourse->grade <= 10) {
                // Valid input, break out of the loop
                break;
            } else {
                printf("Invalid grade. Please enter a number between 0 and 10.\n");

                // Clear the input buffer
                while (getchar() != '\n');
            }
        }

        // Check if the course already exists for the student
        int existingCourseIndex = -1;
        course_t *currentCourse = studentset->head->courses->head;
        int currentCourseIndex = 0;
        while (currentCourse != NULL) {
            if (strcmp(currentCourse->name, newCourse->name) == 0) {
                existingCourseIndex = currentCourseIndex;
                break;
            }
            currentCourse = currentCourse->next;
            currentCourseIndex++;
        }

        if (existingCourseIndex != -1) {
            // Course already exists for the student

            // Ask if the user wants to update the grade
            char updateChoice;
            printf("This course and its grade already exist for the student.\n");
            printf("Do you want to update the grade? If yes, type 'y'; if no, type anything else: ");
            scanf(" %c", &updateChoice);

            if (updateChoice == 'y' || updateChoice == 'Y') {
                // Update the existing grade
                printf("Enter the new grade for course %s: ", newCourse->name);
                scanf("%d", &(currentCourse->grade));
                printf("Grade updated successfully.\n");

                // Free allocated memory and skip adding the course again
                free(newCourse->name);
                free(newCourse);
                continue;
            } else {
                // User doesn't want to update, stop adding this course
                printf("Grade not updated. Skipping the addition of this course.\n");

                // Free allocated memory and break out of the loop
                free(newCourse->name);
                free(newCourse);
                break;
            }
        }

        // Add the course to the student's course set
        newCourse->next = studentset->head->courses->head;
        studentset->head->courses->head = newCourse;

        // Increase the count of courses for the current student
        studentset->head->courses->numCourses++;

        printf("Course '%s' added successfully for the student %s %s!\n", newCourse->name,
               studentset->head->name, studentset->head->surname);
    }
}

void searchStudentById(studentset_t *studentset) {
    // Get student ID from the user
    int studentID;
    printf("Enter student ID: ");
    scanf("%d", &studentID);

    // Find and display the student by ID
    student_t *currentStudent = studentset->head;
    while (currentStudent != NULL) {
        if (currentStudent->id == studentID) {
            // Print student information
            printf("Student found:\n");
            printf("ID: %d\n", currentStudent->id);
            printf("Surname: %s\n", currentStudent->surname);
            printf("Name: %s\n", currentStudent->name);
            printf("Age: %d\n", currentStudent->age);

            // Print courses and grades
            printf("Courses: ");
            course_t *currentCourse = currentStudent->courses->head;
            while (currentCourse != NULL) {
                printf("%s(%d) ", currentCourse->name, currentCourse->grade);
                currentCourse = currentCourse->next;
            }
            printf("\n");

            return;  // Exit the function after finding the student
        }

        // Move to the next student in the linked list
        currentStudent = currentStudent->next;
    }

    // If the loop completes without finding the student, print a message
    printf("Student not found.\n");
}

void searchStudentBySurname(studentset_t *studentset) {
    // Get student surname from the user
    printf("Enter student surname: ");
    char searchKey[50];
    scanf("%49s", searchKey);

    // Find and display the student(s) by surname
    student_t *currentStudent = studentset->head;
    int foundStudents = 0;

    while (currentStudent != NULL) {
        if (strcmp(currentStudent->surname, searchKey) == 0) {
            // Print information for each matching student
            printf("Student found:\n");
            printf("ID: %d\n", currentStudent->id);
            printf("Surname: %s\n", currentStudent->surname);
            printf("Name: %s\n", currentStudent->name);
            printf("Age: %d\n", currentStudent->age);

            // Print courses and grades
            printf("Courses: ");
            course_t *currentCourse = currentStudent->courses->head;
            while (currentCourse != NULL) {
                printf("%s(%d) ", currentCourse->name, currentCourse->grade);
                currentCourse = currentCourse->next;
            }
            printf("\n");

            foundStudents++;
        }

        // Move to the next student in the linked list
        currentStudent = currentStudent->next;
    }

    // Print a message if no students are found with the given surname
    if (foundStudents == 0) {
        printf("No student found with surname '%s'.\n", searchKey);
    }
}

void calculateAverageGrade(studentset_t *studentset) {
    // Get student ID from the user
    int studentID;
    char searchKey[50];
    
    // Call the getStudentSearchCriteria function to get the student index
    int studentIndex = getStudentSearchCriteria(studentset, &studentID, searchKey);
    
    // If the student is not found, return from the function
    if (studentIndex == -1) {
        return;
    }

    // Initialize variables to calculate the average grade
    double totalGrade = 0.0;
    int numCourses = studentset->head->courses->numCourses;

    // Check if the student has no courses
    if (numCourses == 0) {
        printf("Student has no courses to calculate the average grade.\n");
        return;
    }

    // Traverse the courses linked list and calculate the total grade
    course_t *currentCourse = studentset->head->courses->head;
    while (currentCourse != NULL) {
        totalGrade += currentCourse->grade;
        currentCourse = currentCourse->next;
    }

    // Calculate the average grade
    double averageGrade = totalGrade / numCourses;

    // Print the average grade for the student
    printf("Average grade for %s %s is: %.2f\n",
           studentset->head->name,
           studentset->head->surname,
           averageGrade);
}

void deleteStudent(studentset_t *studentset) {
    int studentID;
    char searchKey[50];

    // Call the getStudentSearchCriteria function to get the student index
    int studentIndex = getStudentSearchCriteria(studentset, &studentID, searchKey);

    // If the student is not found, return from the function
    if (studentIndex == -1) {
        return;
    }

    // Free memory for the student's course set
    freeCourseSet(studentset->head->courses);

    // Free memory for the student's name and surname
    free(studentset->head->name);
    free(studentset->head->surname);

    // Remove the student from the linked list by updating pointers
    if (studentIndex == 0) {
        // If the student is the head, update the head pointer
        student_t *nextStudent = studentset->head->next;
        free(studentset->head);
        studentset->head = nextStudent;
    } else {
        // If the student is not the head, update the previous student's next pointer
        student_t *prevStudent = NULL;
student_t *currentStudent = studentset->head;

for (int i = 0; i < studentIndex; i++) {
    prevStudent = currentStudent;
    currentStudent = currentStudent->next;
}
        prevStudent->next = currentStudent->next;
        free(currentStudent);
    }

    // Decrease the count of students
    studentset->num_students--;

    printf("Student deleted successfully!\n");
}

void deleteCourseForStudent(studentset_t *studentset) {
    int studentID;
    char searchKey[50];

    // Call the getStudentSearchCriteria function to get the student index
    int studentIndex = getStudentSearchCriteria(studentset, &studentID, searchKey);

    // If the student is not found, return from the function
    if (studentIndex == -1) {
        return;
    }

    // Ask for the number of courses to delete
    int numCoursesToDelete;
    printf("Enter the number of courses to delete: ");
    scanf("%d", &numCoursesToDelete);

    // Ask for the names of courses to delete
    for (int i = 0; i < numCoursesToDelete; i++) {
        char courseToDelete[50];
        printf("Enter the name of course %d to delete: ", i + 1);
        scanf("%s", courseToDelete);

        // Find the course in the student's course set
        course_t *currentCourse = studentset->head->courses->head;
        course_t *prevCourse = NULL;

        while (currentCourse != NULL) {
            if (strcmp(currentCourse->name, courseToDelete) == 0) {
                // Course found, break out of the loop
                break;
            }

            // Move to the next course in the linked list
            prevCourse = currentCourse;
            currentCourse = currentCourse->next;
        }

        if (currentCourse == NULL) {
            printf("Course '%s' not found for the specified student.\n", courseToDelete);
        } else {
            // Free memory for the course name
            free(currentCourse->name);

            // Remove the course from the linked list
            if (prevCourse == NULL) {
                // If the course is the head, update the head pointer
                studentset->head->courses->head = currentCourse->next;
            } else {
                // If the course is not the head, update the previous course's next pointer
                prevCourse->next = currentCourse->next;
            }

            // Decrease the count of courses for the student
            studentset->head->courses->numCourses--;

            // Free memory for the course node
            free(currentCourse);

            printf("Course '%s' deleted successfully for the specified student!\n", courseToDelete);
        }
    }
}

void saveToFile(studentset_t *studentSet) {
    const char *filename = "list.txt";
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    student_t *currentStudent = studentSet->head;
    while (currentStudent != NULL) {
        fprintf(file, "%d %s %s %d %d ",
                currentStudent->id,
                currentStudent->surname,
                currentStudent->name,
                currentStudent->age,
                currentStudent->courses->numCourses);

        course_t *currentCourse = currentStudent->courses->head;
        while (currentCourse != NULL) {
            fprintf(file, "%s %d ",
                    currentCourse->name,
                    currentCourse->grade);

            currentCourse = currentCourse->next;
        }

        fprintf(file, "\n");

        currentStudent = currentStudent->next;
    }

    fclose(file);
    printf("Data saved to file '%s' successfully.\n", filename);
}

void loadFromFile(studentset_t *studentSet) {
    const char *filename = "list.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Initialize the student set
    initializeStudentSet(studentSet);

    // Temporary variables to store read data
    int id, age;
    char surname[50], name[50];

    // Read student data from the file
    while (fscanf(file, "%d %s %s %d", &id, surname, name, &age) == 4) {
        // Create a new student
        student_t newStudent;
        newStudent.id = id;
        newStudent.age = age;

        // Allocate memory for name and surname
        newStudent.name = malloc(strlen(name) + 1);
        strcpy(newStudent.name, name);

        newStudent.surname = malloc(strlen(surname) + 1);
        strcpy(newStudent.surname, surname);

        // Initialize courses for the student
        newStudent.courses = malloc(sizeof(courseset_t));
        newStudent.courses->head = NULL;
        newStudent.courses->numCourses = 0;

        // Read the number of courses for the current student
        int numCourses;
        fscanf(file, "%d", &numCourses);

        // Read course data from the file
        for (int i = 0; i < numCourses; i++) {
            course_t newCourse;

            // Allocate memory for course name
            newCourse.name = malloc(50 * sizeof(char));

            // Read course data
            fscanf(file, "%s %d", newCourse.name, &newCourse.grade);

            // Add the new course to the courseset
            addCourseToSet(newStudent.courses, newCourse);
        }

        // Add the new student to the student set
        addStudentToSet(studentSet, newStudent);
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
}

void showAllStudents(studentset_t *studentSet) {
    student_t *currentStudent = studentSet->head;
    int studentCount = 1;

    while (currentStudent != NULL) {
        printf("Student %d: %s, %s, ID: %d, Age: %d, Courses: ",
               studentCount,
               currentStudent->surname,
               currentStudent->name,
               currentStudent->id,
               currentStudent->age);

        // Display courses and grades for the student
        course_t *currentCourse = currentStudent->courses->head;
        while (currentCourse != NULL) {
            printf("%s(%d) ", currentCourse->name, currentCourse->grade);

            // Move to the next course in the linked list
            currentCourse = currentCourse->next;
        }

        printf("\n");

        // Move to the next student in the linked list
        currentStudent = currentStudent->next;
        studentCount++;
    }
}

int isAlphaString(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0;  // Not an alphabetical character
        }
        str++;
    }
    return 1;  // All characters are alphabetical
}

void sortStudents(studentset_t *studentSet) {
    // Use a simple bubble sort algorithm for simplicity
    for (int i = 0; i < studentSet->num_students - 1; i++) {
        student_t *currentStudent = studentSet->head;
        student_t *nextStudent = studentSet->head->next;

        for (int j = 0; j < studentSet->num_students - i - 1; j++) {
            // Compare surnames
            int surnameComparison = strcmp(currentStudent->surname, nextStudent->surname);

            if (surnameComparison > 0 || (surnameComparison == 0 && strcmp(currentStudent->name, nextStudent->name) > 0)) {
                // Swap the students if they are out of order
                if (j == 0) {
                    // If the head needs to be swapped, update the head pointer
                    studentSet->head = nextStudent;
                } else {
                    // Otherwise, update the previous student's next pointer
                    student_t *prevStudent = studentSet->head;
                    for (int k = 0; k < j - 1; k++) {
                        prevStudent = prevStudent->next;
                    }
                    prevStudent->next = nextStudent;
                }

                // Perform the swap in the linked list
                student_t *temp = nextStudent->next;
                nextStudent->next = currentStudent;
                currentStudent->next = temp;

                // Update currentStudent and nextStudent pointers for the next iteration
                nextStudent = temp;
            } else {
                // Move to the next pair of students
                currentStudent = nextStudent;
                nextStudent = nextStudent->next;
            }
        }
    }
}

int getStudentSearchCriteria(studentset_t *studentset, int *studentID, char *searchKey) {
    // Ask the user for the search criteria (ID or surname)
    printf("Choose search criteria:\n");
    printf("1. Search by student ID\n");
    printf("2. Search by student surname\n");

    int searchChoice;
    scanf("%d", &searchChoice);

    // Clear the input buffer after reading the choice
    while (getchar() != '\n');

    if (searchChoice == 1) {
        // Validate that ID is numbers only
        printf("Enter student ID: ");
        while (scanf("%d", studentID) != 1) {
            printf("Invalid input. ID should contain only numbers.\n");

            // Clear the input buffer
            while (getchar() != '\n');
            printf("Enter student ID: ");
        }
        // Clear the input buffer after successful input
        while (getchar() != '\n');
    } else if (searchChoice == 2) {
        // Validate that surname is letters only
        int surnameValid = 0;
        do {
            printf("Enter student surname: ");
            if (scanf("%49s", searchKey) == 1 && isalpha(searchKey[0])) {
                surnameValid = 1;
            } else {
                printf("Invalid input. Surname should contain only letters.\n");

                // Clear the input buffer
                while (getchar() != '\n');
            }
        } while (!surnameValid);
    } else {
        printf("Invalid choice.\n");
        return -1;
    }

    // Find the student in the student set
    student_t *currentStudent = studentset->head;
    int studentIndex = 0; // Initialize the index

    while (currentStudent != NULL) {
        if ((searchChoice == 1 && currentStudent->id == *studentID) ||
            (searchChoice == 2 && strcmp(currentStudent->surname, searchKey) == 0)) {
            return studentIndex; // Return the index when the student is found
        }

        // Move to the next student in the linked list
        currentStudent = currentStudent->next;
        studentIndex++;
    }

    printf("Student not found.\n");
    return -1; // Return -1 if the student is not found
}

void addCourseToSet(courseset_t *courseset, course_t newCourse) {
    // Allocate memory for the new course node
    course_t *newCourseNode = (course_t *)malloc(sizeof(course_t));
    if (newCourseNode == NULL) {
        printf("Memory allocation failed. Course not added.\n");
        return;
    }

    // Copy data to the new course node
    newCourseNode->name = strdup(newCourse.name);
    newCourseNode->grade = newCourse.grade;

    // Set the next pointer to the current head of the course set
    newCourseNode->next = courseset->head;

    // Update the head of the course set to the new course node
    courseset->head = newCourseNode;

    // Increment the number of courses in the set
    courseset->numCourses++;
}

void addStudentToSet(studentset_t *studentSet, student_t newStudent) {
    // Allocate memory for the new student node
    student_t *newStudentNode = (student_t *)malloc(sizeof(student_t));
    if (newStudentNode == NULL) {
        printf("Memory allocation failed. Student not added.\n");
        return;
    }

    // Copy data to the new student node
    newStudentNode->id = newStudent.id;
    newStudentNode->age = newStudent.age;
    newStudentNode->name = strdup(newStudent.name);
    newStudentNode->surname = strdup(newStudent.surname);

    // Initialize courses for the new student node
    newStudentNode->courses = (courseset_t *)malloc(sizeof(courseset_t));
    newStudentNode->courses->head = NULL;
    newStudentNode->courses->numCourses = 0;

    // Copy courses from the newStudent to the newStudentNode
    course_t *currentCourse = newStudent.courses->head;
    while (currentCourse != NULL) {
        addCourseToSet(newStudentNode->courses, *currentCourse);
        currentCourse = currentCourse->next;
    }

    // Set the next pointer to the current head of the student set
    newStudentNode->next = studentSet->head;

    // Update the head of the student set to the new student node
    studentSet->head = newStudentNode;

    // Increment the number of students in the set
    studentSet->num_students++;
}

void freeCourseSet(courseset_t *courseset) {
    course_t *current = courseset->head;
    while (current != NULL) {
        course_t *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}

void freeStudentSet(studentset_t *studentset) {
    student_t *currentStudent = studentset->head;
    student_t *nextStudent;

    while (currentStudent != NULL) {
        nextStudent = currentStudent->next;

        // Free the student's name and surname
        free(currentStudent->name);
        free(currentStudent->surname);

        // Free the courses set
        freeCourseSet(currentStudent->courses);

        // Free the student structure
        free(currentStudent);

        currentStudent = nextStudent;
    }

    studentset->head = NULL;
    studentset->num_students = 0;
}