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

void print_error(code status, int line);

#endif