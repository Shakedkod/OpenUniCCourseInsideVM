#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int id;
    int age;
    double grade;
    char* name;
} Student;

void printStudent(void *);
void *newStudent();
void deleteStudent(void **);
int getId(void *);

#endif