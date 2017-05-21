
// NOT FINISHED!!!

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE} Subject;

typedef struct {
    Subject subject;
    int value;
}Grade;

typedef struct{
    char name[128];
    int age;
    Grade* grades;
    int grade_count;
}Student;

// TODO:
// Create a function that constructs a Student (returns a pointer to a new student)
// It should take their name and their age as parameters
// It should allocate 5 grades
// It should set the grade_count to 0
Student* create_student(char* _name, int _age) {

    Grade* grades = calloc(5, sizeof(Grade));

    Student* _student = malloc(sizeof(Student));

    strcpy(_student->name, _name);
    _student->age = _age;
    _student->grade_count = 0;

    return _student;
}

// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments
void grader(Student* _student, Subject _subject, int _grade) {


}

// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in

// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself

int main() {

    return 0;
}
