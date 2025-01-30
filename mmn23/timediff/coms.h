#ifndef COMS_H
#define COMS_H

typedef enum
{
    OK,

    /* ERROR CODES */
    MISSING_ARGUMENT,
    TOO_MANY_ARGUMENTS,
    MISSING_FILE,
    UNREADABLE_FILE,
    LINE_TOO_LONG,
    MISSING_NUMBER,
    TOO_MANY_NUMBERS,
    INCORRECT_MONTH,
    INCORRECT_HOUR,
    INCORRECT_DAY,
    INCORRECT_MINUTE,
    INCORRECT_SECOND,

    /* EXIT CODES */
    EXIT_EOF, EMPTY_FILE
} code;

typedef enum
{
    FALSE,
    TRUE
} boolean;

/* 
    prints an error based on a code given and a line given. 

    input:
        1. code status: the status of the program. can be an error.
        2. int line: the line where the status originates from.
*/
void print_error(code status, int line);

#endif