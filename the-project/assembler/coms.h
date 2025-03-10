#ifndef COMS_H
#define COMS_H

#define NUMBER_OF_ALPHABETIC_LETTERS 26
#define NUMBER_OF_ALLOWED_NUMBERS    10

#define DEFAULT_STATE {OK, "\0", 1}

#define GET_ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define GET_LETTER_INDEX(c)     (c - 'a')

#define PRINT_WARNING(status) print_warning(status.status, status.line_num, status.data)
#define PRINT_ERROR(status)   print_error(status.status, status.line_num, status.data)

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
    E_MACRO_DEF_END_EXCESS,
    E_MACRO_ALREADY_DEFINED,
    E_MACRO_NOT_CLOSED,
            /* macro name related */
    E_MACRO_NAME_STARTS_WITH_DIGIT,
    E_MACRO_NAME_ILLEGAL_CHARACTER,

        /* memory */
    E_MEMORY_NEEDED,

        /* files */
    E_FILE_INVALID_PATH,
    E_FILE_UNRECOGNIZED_FILE_TYPE,
    E_FILE_NO_FILE_ENTERED,

        /* reader */
    E_READ_ERROR,
    E_WRITE_ERROR,

        /* system */
    E_SYSTEM_UNUSABLE_TEMP_FILE
} code;

typedef struct
{
    code status;
    char *data;
    int line_num;
} state;

void zeroize_state(state *status);

void print_warning(code warning, int line, char *data);
void print_error(code error, int line, char *data);

#endif