#ifndef COMS_H
#define COMS_H
/* coms == communication */

#include "complex.h"

#define MAX_LINE_LENGTH 1024

typedef struct 
{
    complex *A;
    complex *B;
    complex *C;
    complex *D;
    complex *E;
    complex *F;
} vars;

typedef enum
{
    FALSE, TRUE
} boolean;

typedef enum
{
    /* system codes*/
    OK, CONTINUE, EMPTY,

    /* user error codes */
    TOO_LONG,
    MISSING_COMMA,
    ILLEGAL_COMMA,
    EXTRA_COMMA,
    UNDEFINED_COMMAND,
    EXCESS,
    MISSING_VAR,
    UNDEFINED_VAR,
    IP_LETTERS_IN_NUMBER,
    IP_NOT_A_NUMBER,
    IP_MULTIPLE_DOTS,

    /* machine error codes */
    READING_ERROR,

    /* exit codes */
    EXIT_STOP
} code;

typedef enum
{
    /* empty codes */
    NONE,

    /* excepted types codes */
    CHARACTER,
    NUMBER,

    /* not-excepted types codes */
    STRING,

    /* error codes */
    COMMA
} var_type;

void print_error(code error);

#endif