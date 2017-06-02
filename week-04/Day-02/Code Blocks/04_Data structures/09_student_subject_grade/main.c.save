#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE} subject_t;

typedef struct {
    subject_t subject;
    int value;
} grade_t;

typedef struct {
    char name[128];
    int age;
    grade_t *grades;
    int grade_count;
} student_t;

// TODO:
// Create a function the constructs a Student (returns a pointer to a new student)
// It should take it's name and it's age as parameter
// It should allocate 5 grades
// It should set the grade_count to 0
student_t *create_student(char *name, int age)
{
    student_t *result = malloc(sizeof(student_t));

    strcpy(result->name, name);
    result->age = age;
    result->grades = calloc(5, sizeof(grade_t));
    result->grade_count = 0;

    return result;
}

// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments
void set_grade(student_t *student, subject_t subject, int grade)
{
    student->grades[student->grade_count].subject = subject;
    student->grades[student->grade_count].value = grade;
    student->grade_count++;
}

// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in
subject_t worst_subject(student_t *student)
{
    subject_t result;
    int worst = 5;
    int index = 0;

    for (int i = 0; i < student->grade_count; i++) {
        if (student->grades[i].value < worst) {
            worst = student->grades[i].value;
            index = i;
        }
    }
    result = student->grades[index].subject;

    return result;
}

// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself
void deconstruct(student_t *student)
{
    free(student->grades);
    free(student);
}

int main()
{
    student_t *student = create_student("Pistike", 12);

    set_grade(student, MATH, 3);
/*
    set_grade(student, HISTORY, 2);
    set_grade(student, ENGLISH, 4);
    set_grade(student, SCIENCE, 3);
 */
    switch (worst_subject(student)) {
    case 0:
        printf("The worst subject of %s is math\n", student->name);
        break;
    case 1:
        printf("The worst subject of %s is history\n", student->name);
        break;
    case 2:
        printf("The worst subject of %s is English\n", student->name);
        break;
    case 3:
        printf("The worst subject of %s is science\n", student->name);
        break;
    default:
        printf("I fucked up...\n");
    }

    deconstruct(student);

    return 0;
}
