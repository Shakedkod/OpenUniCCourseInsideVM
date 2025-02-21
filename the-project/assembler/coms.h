#ifndef COMS_H
#define COMS_H

#define NUMBER_OF_ALPHABETIC_LETTERS 26
#define NUMBER_OF_ALLOWED_NUMBERS 10

#define GET_ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define GET_LETTER_INDEX(c) (c - 'a')

typedef enum
{
    FALSE,
    TRUE
} boolean;

typedef enum
{
    /* OK */
    OK, CONTINUE,

    /* WARNINGS */
        /* reader */
    W_LINE_TOO_LONG,

    /* ERRORS */
        /* macro related */
    E_MACRO_UNNAMED,
    E_MACRO_EXCESS,
    E_MACRO_COMMAND_NAME,
    E_MACRO_DEF_EXCESS,
    E_MACRO_ALREADY_DEFINED,
            /* macro name related */
    E_MACRO_NAME_STARTS_WITH_DIGIT,
    E_MACRO_NAME_ILLEGAL_CHARACTER,

        /* memory */
    E_MEMORY_NEEDED,

        /* reader */
    E_READ_ERROR
} code;

typedef struct
{
    code status;
    char *data;
    int line_num;
} state;

void print_warning(code warning, int line, char *data);
void print_error(code error, int line, char *data);

#endif