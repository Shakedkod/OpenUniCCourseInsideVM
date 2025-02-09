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

    /* ERRORS */
        /* macro related */
    E_MACRO_DOUBLE_DEF,
} code;

#endif