#ifndef COMS_H
#define COMS_H
/* coms == communication */

typedef enum
{
    /* system codes*/
    OK, CONTINUE, EMPTY,

    /* user error codes */
    ILLEGAL_COMMA,
    UNDEFINED_COMMAND,

    /* machine error codes */
    READING_ERROR,

    /* exit codes */
    EXIT_STOP, EXIT_EOF
} code;

code error_eof(char *line);
code error_error_reading(char *line);

#endif