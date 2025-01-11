#ifndef COMS_H
#define COMS_H
/* coms == communication */

typedef enum
{
    /* command ran codes*/
    OK,

    /* error codes */
    ILLEGAL_COMMA,
    UNDEFINED_COMMAND,

    /* exit codes */
    EXIT_STOP, EXIT_EOF
} code;

#endif