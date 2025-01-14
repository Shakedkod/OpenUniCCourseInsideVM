#ifndef COMS_H
#define COMS_H
/* coms == communication */

#include "complex.h"

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
    ILLEGAL_COMMA,
    UNDEFINED_COMMAND,
    EXCESS,
    MISSING_VAR,
    UNDEFINED_VAR,

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

/* debug functions - remove */
char *code_to_str(code value);

#endif