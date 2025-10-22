## Student Management System (C Project)

### Project Summary

This project is a console-based **Student Management System** written in the C programming language. It utilizes **singly linked lists** to dynamically manage information about students and their associated courses.
The program allows users to add, search, sort, modify, and delete both student and course data, as well as save and load the complete dataset from a text file to ensure data persistence across program executions.

---

### Core Features

* Add new students with validated name, surname, and age input.
* Add courses (including course name and grade) for individual students.
* Search for students by their unique ID or surname.
* Calculate the average grade for a specific student.
* Delete individual students or specific courses.
* Sort students alphabetically by surname and name.
* Save and load all student and course data to and from an external file (`list.txt`).
* Display all stored student information along with enrolled courses.
* Manage dynamic memory allocation and deallocation to prevent memory leaks.

---

### Key Methods and Algorithms

* **Linked Lists:**
  The program defines two separate singly linked lists — one for students (`student_t`) and another for courses (`course_t`). Each student node contains a nested linked list of courses, forming a hierarchical data structure.

* **Sorting Algorithm:**
  Implements a custom bubble sort algorithm to order student records alphabetically by surname and, when equal, by name.

* **File Input/Output:**
  Employs formatted text-based I/O operations (`fprintf`, `fscanf`) to store and retrieve student and course information from a file.

* **Input Validation:**
  Ensures that names and surnames contain only alphabetic characters and that numeric fields (such as age and grades) are validated for correctness.

* **Dynamic Memory Handling:**
  Utilizes `malloc()`, `free()`, and `strdup()` to allocate, copy, and release memory dynamically, ensuring efficient and safe memory management.

---

### Skills Demonstrated

* Implementation of fundamental C programming concepts.
* Design and manipulation of singly linked lists.
* Construction of nested and dynamically allocated data structures.
* Application of memory management techniques and error handling.
* User input validation and menu-driven interaction.
* File handling and persistent data management.
* Modular program design using multiple source and header files.
* Application of sorting and searching algorithms in a data structure context.

---

### File Overview

| File Name          | Description                                                        |
| ------------------ | ------------------------------------------------------------------ |
| **student.c**      | Contains the main program and the user interaction menu.           |
| **instructions.c** | Implements all functional logic for managing students and courses. |
| **instructions.h** | Defines data structures and declares function prototypes.          |

---

### How to Compile and Run

1. Compile the program using a C compiler such as GCC:

   ```bash
   gcc student.c instructions.c -o student_management
   ```

2. Execute the compiled program:

   ```bash
   ./student_management
   ```

3. Follow the on-screen menu prompts to add, search, modify, or display student and course information.

---

