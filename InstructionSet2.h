#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

// Initialize Structs
typedef struct Course {
    char *name;    // Name of the course
    int grade;     // grade 0-10
    struct Course *next;  // Pointer to the next course in the linked list
} course_t;

typedef struct CourseSet {
    course_t *head;  // Head of the linked list of courses
    int numCourses;  // Number of courses
} courseset_t;

typedef struct Student {
    int id;
    char *name;
    char *surname;
    int age;
    courseset_t *courses;  // Add this field for the courseset
    struct Student *next;  // Pointer to the next student in the linked list
} student_t;

typedef struct StudentSet {
    student_t *head;  // Head of the linked list of students
    int num_students;  // Number of students
} studentset_t;

// Function prototypes
void initializeStudentSet(studentset_t *studentset);
void addStudent(studentset_t *studentset);
void addCourseForStudent(studentset_t *studentset);
void searchStudentById(studentset_t *studentset);
void searchStudentBySurname(studentset_t *studentset);
void calculateAverageGrade(studentset_t *studentset);
void deleteStudent(studentset_t *studentset);
void deleteCourseForStudent(studentset_t *studentset);
void saveToFile(studentset_t *studentset);
void loadFromFile(studentset_t *studentset);
void showAllStudents(studentset_t *studentSet);
int isAlphaString(const char *str);
int getStudentSearchCriteria(studentset_t *studentset, int *studentID, char *searchKey);
void sortStudents(studentset_t *studentSet);
void freeCourseSet(courseset_t *courseset);
void freeStudentSet(studentset_t *studentset);
void freeCourseSet(courseset_t *courseset);
void freeStudentSet(studentset_t *studentset);
void initializeStudentSet(studentset_t *studentSet);
int isAlphaString(const char *str);
int getStudentSearchCriteria(studentset_t *studentset, int *studentID, char *searchKey);
void sortStudents(studentset_t *studentSet);
void addStudentToSet(studentset_t *studentSet, student_t newStudent);
void addCourseToSet(courseset_t *courseset, course_t newCourse);


#endif
