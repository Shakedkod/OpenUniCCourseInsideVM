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
    EXCESS,

    /* machine error codes */
    READING_ERROR,

    /* exit codes */
    EXIT_STOP, EXIT_EOF, EXIT_EXCESS_AND_EOF
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

code error_eof(char *line);
code error_reading(char *line);

/* debug functions - remove */
char *code_to_str(code value);

#endif