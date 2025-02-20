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

struct code_to_message
{
    code status;
    const char *msg;
    /* ADD THE %S %D SHIT HERE*/
} messages[] = {
    /* WARNING */
        /* reader */
    {W_LINE_TOO_LONG, "Line %d is too long."},

    /* ERROR */
        /* macro related */
    {E_MACRO_UNNAMED, "The macro defined in line %d needs a name."},
    {E_MACRO_EXCESS, "In line %d at the call of macro '%s', there is excess characters after the name."},
    {E_MACRO_COMMAND_NAME, "In line %d the macro name '%s' is a command name, and thus not allowed."},
    {E_MACRO_DEF_EXCESS, "In line %d at the definiton of macro '%s', there is excess characters after the name."},
    {E_MACRO_ALREADY_DEFINED, "The macro %s, defined in line %d, is already defined"}
};

typedef struct
{
    code status;
    char *line;
    int line_num;
} state;

#endif