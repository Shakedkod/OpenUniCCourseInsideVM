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

complex get_comp_value(char var, vars variables, code *defined)
{
    switch (var)
    {
    case 'A':
        return *(variables.A);
    case 'B':
        return *(variables.B);
    case 'C':
        return *(variables.C);
    case 'D':
        return *(variables.D);
    case 'E':
        return *(variables.E);
    case 'F':
        return *(variables.F);
    
    default:
        *(defined) = UNDEFINED_VAR;
    }
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
    char var;
    int num_of_vars, i, valueInt;
    double value;
    complex actual_var;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* finding the var name */
    num_of_vars = sscanf(part, "%c", &var);
    if (num_of_vars < 1)
        return MISSING_VAR;
    
    /* getting the value of the var */
    actual_var = get_comp_value(var, variables, &defined);
    if (defined != OK)
        return defined;

    /* no comma or char after var */
    for (i = 1; part[i] != '\0'; i++)
    {
        if (part[i] == ',')
            return ILLEGAL_COMMA;
        
        return EXCESS;
    }

    /* no comma or char after a space */
    part = strtok(NULL, REMOVABLE_TOKENS);
    if (part != NULL)
    {
        if (part[0] == ',')
            return ILLEGAL_COMMA;
        return EXCESS;
    }

    /* executing */
    value = abs_comp(actual_var);
    if ((valueInt = (int)value) == value)
        printf("%d\n", valueInt);
    else
        printf("%.2lf\n", value);
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
    char var;
    int num_of_vars, i;
    complex actual_var;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* finding the var name */
    num_of_vars = sscanf(part, "%c", &var);
    if (num_of_vars < 1)
        return MISSING_VAR;
    
    /* getting the value of the var */
    actual_var = get_comp_value(var, variables, &defined);
    if (defined != OK)
        return defined;

    /* no comma or char after var */
    for (i = 1; part[i] != '\0'; i++)
    {
        if (part[i] == ',')
            return ILLEGAL_COMMA;
        
        return EXCESS;
    }

    /* no comma or char after a space */
    part = strtok(NULL, REMOVABLE_TOKENS);
    if (part != NULL)
    {
        if (part[0] == ',')
            return ILLEGAL_COMMA;
        return EXCESS;
    }

    /* executing */
    print_comp(actual_var);
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