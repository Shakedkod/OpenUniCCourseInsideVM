#include <stdio.h>
#include <string.h>

#include "user_interface.h"
#include "string_manipulation.h"
#include "complex.h"

#define REMOVABLE_TOKENS " \t"

code call_abs_comp(vars variables);
code call_add_comp(vars variables);
code call_mult_comp_comp(vars variables);
code call_mult_comp_img(vars variables);
code call_mult_comp_real(vars variables);
code call_print_comp(vars variables);
code call_read_comp(vars variables);
code call_stop();
code call_sub_comp(vars variables);

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

code execute_line(vars variables, boolean *is_eof)
{
    char *part;
    code compare;
    line_read read = read_line();
    if (read.status == READ_ERROR)
        return READING_ERROR;
    if (is_all_whitespaces(read.line))
        return EMPTY;
    if (read.status == READ_EOF)
        *(is_eof) = TRUE;

    /* print the command for visibility */
    printf("%s\n", read.line);

    /* get command */
    part = strtok(read.line, REMOVABLE_TOKENS);
    if (part == NULL)
        return UNDEFINED_COMMAND;
    
    /* parse command */
    compare = strcmp_for_commands(part, "abs_comp");
    if (compare == OK)
        return call_abs_comp(variables);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "add_comp");
    if (compare == OK)
        return call_add_comp(variables);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "mult_comp_comp");
    if (compare == OK)
        return call_mult_comp_comp(variables);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "mult_comp_img");
    if (compare == OK)
        return call_mult_comp_img(variables);
    if (compare != CONTINUE)
        return compare;

    compare = strcmp_for_commands(part, "mult_comp_real");
    if (compare == OK)
        return call_mult_comp_real(variables);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "print_comp");
    if (compare == OK)
        return call_print_comp(variables);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "read_comp");
    if (compare == OK)
        return call_read_comp(variables);
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "stop");
    if (compare == OK)
        return call_stop();
    if (compare != CONTINUE)
        return compare;
    
    compare = strcmp_for_commands(part, "sub_comp");
    if (compare == OK)
        return call_sub_comp(variables);
    if (compare != CONTINUE)
        return compare;

    return UNDEFINED_COMMAND;
}

/* COMMANDS FUNCTIONS */
code call_abs_comp(vars variables)
{
    return OK;
}

code call_add_comp(vars variables)
{
    return OK;
}

code call_mult_comp_comp(vars variables)
{
    return OK;
}

code call_mult_comp_img(vars variables)
{
    return OK;
}

code call_mult_comp_real(vars variables)
{
    return OK;
}

code call_print_comp(vars variables)
{
    char var; /* 1013 = 1024 - 11(the length of "print_comp ")*/
    char *part = strtok(NULL, REMOVABLE_TOKENS);
    complex actual_var;
    int num_of_vars;
    if (part == NULL)
        return MISSING_VAR;
    
    num_of_vars = fscanf((FILE *)part, "%c", &var);
    printf("num_of_vars: %d\n", num_of_vars);
    if (num_of_vars < 1)
        return MISSING_VAR;
    if (num_of_vars > 1)
        return EXCESS;
    
    switch (var)
    {
    case 'A':
        actual_var = *(variables.A);
        break;
    case 'B':
        actual_var = *(variables.B);
        break;
    case 'C':
        actual_var = *(variables.C);
        break;
    case 'D':
        actual_var = *(variables.D);
        break;
    case 'E':
        actual_var = *(variables.E);
        break;
    case 'F':
        actual_var = *(variables.F);
        break;
    
    default:
        return UNDEFINED_VAR;
    }

    /* no comma or var after var */

    part = strtok(NULL, REMOVABLE_TOKENS);

    return OK;
}

code call_read_comp(vars variables)
{
    return OK;
}

code call_stop()
{
    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part != NULL)
        return EXCESS;

    return EXIT_STOP;
}

code call_sub_comp(vars variables)
{
    return OK;
}