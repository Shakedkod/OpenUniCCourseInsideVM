#ifndef COMS_H
#define COMS_H

#define NUMBER_OF_ALPHABETIC_LETTERS 26
#define NUMBER_OF_ALLOWED_NUMBERS    10
#define MAX_LINE_LENGTH 80
#define MAX_SYMBOL_NAME_LENGTH 31
#define INSTRUCTION_COUNTER_START 100
#define DATA_COUNTER_START 0

#define DEFAULT_STATE {OK, "\0", 1}

#define GET_ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define GET_LETTER_INDEX(c)     (c - 'a')

typedef enum
{
    FALSE,
    TRUE
} boolean;

typedef enum
{
    /* OK */
    OK,

    /* WARNINGS */
        /* reader */
    W_LINE_TOO_LONG,
        /* directive */
            /* extern */
    W_EXTERN_SYMBOL_DEF,

    /* ERRORS */
        /* macro */
    E_MACRO_UNNAMED,
    E_MACRO_EXCESS,
    E_MACRO_COMMAND_NAME,
    E_MACRO_DEF_EXCESS,
    E_MACRO_DEF_END_EXCESS,
    E_MACRO_ALREADY_DEFINED,
    E_MACRO_NOT_CLOSED,
            /* macro name */
    E_MACRO_NAME_STARTS_WITH_DIGIT,
    E_MACRO_NAME_ILLEGAL_CHARACTER,

        /* symbol */
    E_SYMBOL_SPACE_BEFORE_COLON,
    E_SYMBOL_ALREADY_EXISTS,
    E_SYMBOL_MACRO_DEFINED,
    E_SYMBOL_COMMAND_NAME,
    E_SYMBOL_MISSING_DEFINITON,
    E_SYMBOL_NOT_FOUND,
            /* symbol name */
    E_SYMBOL_NAME_START_ILLEGAL,
    E_SYMBOL_NAME_ILLEGAL_CHARACTER,
    E_SYMBOL_NAME_ILLEGAL_LENGTH,
    
        /* directive */
            /* data */
    E_DATA_MISSING,
    E_DATA_UNKNOWN_TYPE,
                /* integer */
    E_DATA_INTEGER_PLUS_MINUS_IN_THE_MIDDLE,
    E_DATA_INTEGER_NOT_DIGIT,
    E_DATA_INTEGER_SPACE_IN_THE_MIDDLE,
    E_DATA_INTEGER_NOT_FOUND,
    E_DATA_INTEGER_LARGER_THEN_MAX,
                /* string */
    E_DATA_STRING_EXTRA_STRING,
    E_DATA_STRING_NOT_CLOSED,
    E_DATA_STRING_NO_START_QUOTE,
            /* extern */
    E_EXTERN_MISSING_SYMBOL,
    E_EXTERN_EXCESS,
            /* entry */
    E_ENTRY_MISSING_SYMBOL,
    E_ENTRY_EXCESS,
    E_ENTRY_SYMBOL_NOT_FOUND,
            /* instruction */
    E_INSTRUCTION_MISSING_PARAM,
    E_INSTRUCTION_MISSING_SECOND_PARAMETER,
    E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED,
    E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED,
    E_INSTRUCTION_INPUT_IMMEDIATE_NOT_ALLOWED,
    E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED,
    E_INSTRUCTION_INPUT_STRAIGHT_REGISTER_NOT_ALLOWED,
    E_INSTRUCTION_OUTPUT_STRAIGHT_REGISTER_NOT_ALLOWED,
    E_INSTRUCTION_EXCESS,
    E_RELATIVE_SYMBOL_EXTERN,
                /* command */
    E_INSTRUCTION_COMMAND_ABSENT,
                /* register */
    E_INSTRUCTION_REGISTER_ILLEGAL,

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
    char data[MAX_LINE_LENGTH + 2]; /* MAX_LINE_LENGTH + \n\0 + padding */
    size_t line_num;
} state;

/*
    resets the state.

    input:
        1. state *status: the state to be reset.
*/
void zeroize_state(state *status);

/*
    prints the message connected to the status given.

    input:
        1. state status: the state to be printed.
*/
void print_status(state status);

#endif