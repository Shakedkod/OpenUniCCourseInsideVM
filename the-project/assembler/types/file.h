#ifndef FILE_H
#define FILE_H
#include <stdio.h>

#include "../coms.h"

#define MAX_LINE_LENGTH 80
#define WHITESPACES " \t"

typedef enum 
{
    READ_ERROR = -1,
    READ_EOF, /* line ends at EOF */
    READ_NEWLINE,
    READ_TOO_LONG
} read_status;

typedef struct
{
    char line[MAX_LINE_LENGTH + 2];
    read_status status;
} line_read;

int num_of_lines(FILE *file);
line_read read_line(FILE *file);

/*
    checks if a string is just whitespaces == spaces or tabs.

    input:
        char *str: the string to be checked.
    
    output(boolean):
        TRUE if all whitespaces. FALSE if not.
*/
boolean is_all_whitespaces(const char *str);

#endif