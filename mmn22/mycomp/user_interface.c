#include <stdio.h>
#include <string.h>

#include "user_interface.h"
#include "string_manipulation.h"
#include "complex.h"

#define REMOVABLE_TOKENS " \t"

code call_abs_comp();
code call_add_comp();
code call_mult_comp_comp();
code call_mult_comp_img();
code call_mult_comp_real();
code call_print_comp();
code call_read_comp();
code call_stop();
code call_sub_comp();

typedef enum 
{
    READ_ERROR = -1,
    READ_EOF = 0, /* line ends at EOF */
    READ_NEWLINE = 1
} read_status;

typedef struct
{
    char line[1024];
    read_status status;
} line_read;

line_read read_line() 
{
    int len;
    line_read result;
    result.status = READ_ERROR;

    if (fgets(result.line, sizeof(result.line), stdin) != NULL)
    {
        /* Check if we found newline */
        len = strlen(result.line);
        if (result.line[len-1] == '\n')
        {
            result.line[len-1] = '\0';
            result.status = READ_NEWLINE;
        }
        else
            result.status = READ_EOF;
    }
    else
    {
        /* Nothing read - EOF or error */
        result.status = feof(stdin) ? READ_EOF : READ_ERROR;
        result.line[0] = '\0';
    }

    return result;
}

code execute_line(char line[1024])
{
    char *part;
    code compare;
    line_read read = read_line();
    if (read.status == READ_ERROR)
        return READING_ERROR;
    if (is_all_whitespaces(read.line))
        return EMPTY;

    /* print the command for visibility */
    printf("%s\n", read.line);

    /* get command */
    strcpy(line, read.line);
    part = strtok(read.line, REMOVABLE_TOKENS);
    if (part == NULL)
        return UNDEFINED_COMMAND;
    
    /* check for EOF */
    if (read.status == READ_EOF)
        if (strcmp_for_commands(part, "stop") == OK)
            return call_stop(1);
        else
            return EXIT_EOF;
    
    /* parse command */
    compare = strcmp_for_commands(part, "abs_comp");
    if (compare == OK)
        return call_abs_comp();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "add_comp");
    if (compare == OK)
        return call_add_comp();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "mult_comp_comp");
    if (compare == OK)
        return call_mult_comp_comp();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "mult_comp_img");
    if (compare == OK)
        return call_mult_comp_img();
    if (compare != CONTINUE)
        return compare;

    compare = strcmp_for_commands(part, "mult_comp_real");
    if (compare == OK)
        return call_mult_comp_real();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "print_comp");
    if (compare == OK)
        return call_print_comp();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "read_comp");
    if (compare == OK)
        return call_read_comp();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "stop");
    if (compare == OK)
        return call_stop(0);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "sub_comp");
    if (compare == OK)
        return call_sub_comp();
    if (compare != CONTINUE)
        return compare;

    return UNDEFINED_COMMAND;
}

/* COMMANDS FUNCTIONS */
code call_abs_comp()
{
    return OK;
}

code call_add_comp()
{
    return OK;
}

code call_mult_comp_comp()
{
    return OK;
}

code call_mult_comp_img()
{
    return OK;
}

code call_mult_comp_real()
{
    return OK;
}

code call_print_comp()
{
    return OK;
}

code call_read_comp()
{
    return OK;
}

code call_stop(int is_eof)
{
    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part != NULL)
        return (is_eof) ? EXIT_EXCESS_AND_EOF : EXCESS;

    return EXIT_STOP;
}

code call_sub_comp()
{
    return OK;
}