#ifndef COMS_H
#define COMS_H

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
        /* macro related */
    W_MACRO_DOUBLE_DEF_SAME_CONTENTS,

        /* reader */
    W_LINE_TOO_LONG,

    /* ERRORS */
        /* macro related */
    E_MACRO_DOUBLE_DEF,
    E_MACRO_UNNAMED,
    E_MACRO_EXCESS,
    E_MACRO_COMMAND_NAME,
    E_MACRO_ILLEGAL_NAME,
    E_MACRO_DEF_EXCESS,

        /* memory */
    E_MEMORY_NEEDED,

        /* reader */
    E_READ_ERROR
} code;

#endif