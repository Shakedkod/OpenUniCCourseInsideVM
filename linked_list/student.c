#include "student.h"

#define CHECK_ALLOCATION(pointer) \
{ \
    if (pointer == NULL) \
    { \
        printf("allocation failed"); \
        exit(1); \
    } \
}

void printStudent(void *s)
{
    Student *temp = (Student *)s;
    printf("id: %d\tname: %s\tage: %d\tgrade: %lf", 
        temp->id, temp->name, temp->age, temp->grade
    );
}

char *getName()
{
    char c;
    char *name;
    char *temp;

    name = (char *)malloc(sizeof(char));
    CHECK_ALLOCATION(name);
    
    printf("Please enter your name: ");
    while((c=getchar())!=EOF && c!='\n')
    {
        temp = (char *)realloc(name, sizeof(char) * (strlen(name) + 2));
        if (temp == NULL)
        {
            free(name);
            exit(1);
        }

        name = temp;
        *(name+strlen(name)+1) = '\0';
        *(name+strlen(name)) = c;
    }

    return name;
}

void *newStudent()
{
    static int runID = 0;
    Student *newStudentCreation;
    runID++;

    newStudentCreation = (Student *)malloc(sizeof(Student));
    CHECK_ALLOCATION(newStudentCreation);

    newStudentCreation->grade = 100.0;
    newStudentCreation->id = runID;
    newStudentCreation->age = 17;
    newStudentCreation->name = getName();

    return (void *)newStudentCreation;
}

void deleteStudent(void **s)
{
    Student **temp1 = (Student **)s;
    Student *temp2 = *temp1;
    free(temp2->name);
    free(temp2);
    *temp1 = NULL;
}

int getId(void *s)
{
    Student *temp = (Student *)s;
    return temp->id;
}