#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "user_interface.h"
#include "string_manipulation.h"
#include "complex.h"

#define REMOVABLE_TOKENS " \t"
#define NUMBER_OF_FUNCTIONS 9

code call_abs_comp(vars variables);
code call_add_comp(vars variables);
code call_mult_comp_comp(vars variables);
code call_mult_comp_img(vars variables);
code call_mult_comp_real(vars variables);
code call_print_comp(vars variables);
code call_read_comp(vars variables);
code call_stop();
code call_sub_comp(vars variables);

struct function_connect
{
    char *name;
    code (*func)(vars);
} functions[] = {
    {"abs_comp", call_abs_comp},
    {"add_comp", call_add_comp},
    {"mult_comp_comp", call_mult_comp_comp},
    {"mult_comp_img", call_mult_comp_img},
    {"mult_comp_real", call_mult_comp_real},
    {"print_comp", call_print_comp},
    {"read_comp", call_read_comp},
    {"stop", call_stop},
    {"sub_comp", call_sub_comp}
};

typedef enum 
{
    READ_ERROR = -1,
    READ_EOF, /* line ends at EOF */
    READ_NEWLINE,
    READ_TOO_LONG
} read_status;

typedef struct
{
    char line[MAX_LINE_LENGTH + 2];
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
        if (len == 1025)
            result.status = READ_TOO_LONG;
        else if (result.line[len-1] == '\n')
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
    
    case ',':
        *(defined) = EXTRA_COMMA;
        break;
    default:
        *(defined) = UNDEFINED_VAR;
    }
}

complex *get_comp_pointer(char var, vars variables, code *defined)
{
    switch (var)
    {
    case 'A':
        return variables.A;
    case 'B':
        return variables.B;
    case 'C':
        return variables.C;
    case 'D':
        return variables.D;
    case 'E':
        return variables.E;
    case 'F':
        return variables.F;
    
    case ',':
        *(defined) = EXTRA_COMMA;
        break;
    default:
        *(defined) = UNDEFINED_VAR;
    }
}

code execute_line(vars variables, boolean *is_eof)
{
    char *part, c;
    int i;
    code compare;
    line_read read = read_line();
    if (read.status == READ_ERROR)
        return READING_ERROR;
    if (read.status == READ_TOO_LONG)
    {
        printf("%s", read.line);
        while ((c=getchar()) != EOF && c != '\n')
            printf("%c", c);
        printf("\n");

        if (c == EOF)
            *(is_eof) = TRUE;

        return TOO_LONG;
    }
    if (read.status == READ_EOF)
        *(is_eof) = TRUE;
    if (is_all_whitespaces(read.line))
        return EMPTY;

    /* print the command for visibility */
    printf("%s\n", read.line);

    /* get command */
    part = strtok(read.line, REMOVABLE_TOKENS);
    if (part == NULL)
        return UNDEFINED_COMMAND;
    
    /* parse command */
    for (i = 0; i < NUMBER_OF_FUNCTIONS; i++)
    {
        compare = strcmp_for_commands(part, functions[i].name);
        if (compare == OK)
            return (functions[i].func)(variables);
        if (compare != CONTINUE)
            return compare;
    }
    
    return UNDEFINED_COMMAND;
}

/* COMMANDS FUNCTIONS */
code call_abs_comp(vars variables)
{
    int i, valueInt;
    double value;
    complex actual_var;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* getting the value of the var */
    actual_var = get_comp_value(part[0], variables, &defined);
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
    int i;
    complex varA, varB;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* VAR A */
    varA = get_comp_value(part[0], variables, &defined);
    if (defined != OK)
        return defined;

    /* COMMA */
    if (part[1] != '\0' && part[1] != ',')
        return UNDEFINED_VAR;
    if (part[1]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i = 2;
    
    /* VAR B */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        
        varB = get_comp_value(part[0], variables, &defined);
        if (defined != OK)
            return defined;
        
        i = 1;
    }
    else
    {
        varB = get_comp_value(part[i], variables, &defined);
        if (defined != OK)
            return defined;
        i++;
    }

    if (part[i] != '\0' || strtok(NULL, REMOVABLE_TOKENS) != NULL)
        return EXCESS;
    
    /* executing */
    print_comp(add_comp(varA, varB));
    return OK;
}

code call_mult_comp_comp(vars variables)
{
    int i;
    complex varA, varB;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* VAR A */
    varA = get_comp_value(part[0], variables, &defined);
    if (defined != OK)
        return defined;

    /* COMMA */
    if (part[1] != '\0' && part[1] != ',')
        return UNDEFINED_VAR;
    if (part[1]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i = 2;
    
    /* VAR B */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        
        varB = get_comp_value(part[0], variables, &defined);
        if (defined != OK)
            return defined;
        
        i = 1;
    }
    else
    {
        varB = get_comp_value(part[i], variables, &defined);
        if (defined != OK)
            return defined;
        i++;
    }

    if (part[i] != '\0' || strtok(NULL, REMOVABLE_TOKENS) != NULL)
        return EXCESS;
    
    /* executing */
    print_comp(mult_comp_comp(varA, varB));
    return OK;
}

code call_mult_comp_img(vars variables)
{
    int i, increment, movable;
    double varB = 0;
    boolean had_dot, minus;
    complex varA;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* VAR A */
    varA = get_comp_value(part[0], variables, &defined);
    if (defined != OK)
        return defined;

    /* COMMA */
    if (part[1] != '\0' && part[1] != ',')
        return UNDEFINED_VAR;
    if (part[1]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i = 2;
    
    /* VAR B */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        i = 0;
    }
    
    if (part[i] == ',')
        return EXTRA_COMMA;
    if (part[i] == '-')
    {
        minus = TRUE;
        i++;
    }
    else if (!isdigit(part[i]) && part[i] != '.')
        return IP_NOT_A_NUMBER;
    else
        minus = FALSE;

    increment = -1;
    movable = 0;
    had_dot = FALSE;
    while (part[i] != '\0' && part[i] != ',')
    {
        if (!isdigit(part[i]) && part[i] != '.')
            return IP_LETTERS_IN_NUMBER;
        
        if (part[i] == '.')
        {
            if (had_dot)
                return IP_MULTIPLE_DOTS;
            had_dot = TRUE;
        }
        else
        {
            varB += (part[i] - '0') * pow(10, increment);
            
            increment--;
            if (!had_dot)
                movable++;
        }
        i++;
    }
    varB = varB * pow(10, movable);
    if (minus)
        varB = -varB;

    if (part[i] != '\0' || strtok(NULL, REMOVABLE_TOKENS) != NULL)
        return EXCESS;
    
    /* executing */
    print_comp(mult_comp_img(varA, varB));
    return OK;
}

code call_mult_comp_real(vars variables)
{
    int i, increment, movable;
    double varB = 0;
    boolean had_dot, minus;
    complex varA;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* VAR A */
    varA = get_comp_value(part[0], variables, &defined);
    if (defined != OK)
        return defined;

    /* COMMA */
    if (part[1] != '\0' && part[1] != ',')
        return UNDEFINED_VAR;
    if (part[1]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i = 2;
    
    /* VAR B */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        i = 0;
    }
    
    if (part[i] == ',')
        return EXTRA_COMMA;
    if (part[i] == '-')
    {
        minus = TRUE;
        i++;
    }
    else if (!isdigit(part[i]) && part[i] != '.')
        return IP_NOT_A_NUMBER;
    else
        minus = FALSE;

    increment = -1;
    movable = 0;
    had_dot = FALSE;
    while (part[i] != '\0' && part[i] != ',')
    {
        if (!isdigit(part[i]) && part[i] != '.')
            return IP_LETTERS_IN_NUMBER;
        
        if (part[i] == '.')
        {
            if (had_dot)
                return IP_MULTIPLE_DOTS;
            had_dot = TRUE;
        }
        else
        {
            varB += (part[i] - '0') * pow(10, increment);
            
            increment--;
            if (!had_dot)
                movable++;
        }
        i++;
    }
    varB = varB * pow(10, movable);
    if (minus)
        varB = -varB;

    if (part[i] != '\0' || strtok(NULL, REMOVABLE_TOKENS) != NULL)
        return EXCESS;
    
    /* executing */
    print_comp(mult_comp_real(varA, varB));
    return OK;
}

code call_print_comp(vars variables)
{
    int i;
    complex actual_var;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* getting the value of the var */
    actual_var = get_comp_value(part[0], variables, &defined);
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
    int i, increment, movable;
    double varB = 0, varC = 0;
    boolean had_dot, minus;
    complex *var_pointer;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* VAR A */
    var_pointer = get_comp_pointer(part[0], variables, &defined);
    if (defined != OK)
        return defined;

    /* COMMA */
    if (part[1] != '\0' && part[1] != ',')
        return UNDEFINED_VAR;
    if (part[1]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i = 2;
    
    /* VAR B */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        i = 0;
    }
    
    if (part[i] == ',')
        return EXTRA_COMMA;
    if (part[i] == '-')
    {
        minus = TRUE;
        i++;
    }
    else if (!isdigit(part[i]) && part[i] != '.')
        return IP_NOT_A_NUMBER;
    else 
        minus = FALSE;

    increment = -1;
    movable = 0;
    had_dot = FALSE;
    while (part[i] != '\0' && part[i] != ',')
    {
        if (!isdigit(part[i]) && part[i] != '.')
            return IP_LETTERS_IN_NUMBER;
        
        if (part[i] == '.')
        {
            if (had_dot)
                return IP_MULTIPLE_DOTS;
            had_dot = TRUE;
        }
        else
        {
            varB += (part[i] - '0') * pow(10, increment);
            
            increment--;
            if (!had_dot)
                movable++;
        }
        i++;
    }
    varB *= pow(10, movable);
    if (minus)
        varB = -varB;
    
    /* COMMA */
    if (part[i] != '\0' && part[i] != ',')
        return UNDEFINED_VAR;
    if (part[i]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i++;
    
    /* VAR C */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        i = 0;
    }
    
    if (part[i] == ',')
        return EXTRA_COMMA;
    if (part[i] == '-')
    {
        minus = TRUE;
        i++;
    }
    else if (!isdigit(part[i]) && part[i] != '.')
        return IP_NOT_A_NUMBER;
    else 
        minus = FALSE;

    increment = -1;
    movable = 0;
    had_dot = FALSE;
    while (part[i] != '\0' && part[i] != ',')
    {
        if (!isdigit(part[i]) && part[i] != '.')
            return IP_LETTERS_IN_NUMBER;
        
        if (part[i] == '.')
        {
            if (had_dot)
                return IP_MULTIPLE_DOTS;
            had_dot = TRUE;
        }
        else
        {
            varC += (part[i] - '0') * pow(10, increment);
            
            increment--;
            if (!had_dot)
                movable++;
        }
        i++;
    }
    varC *= pow(10, movable);
    if (minus)
        varC = -varC;

    if (part[i] != '\0' || strtok(NULL, REMOVABLE_TOKENS) != NULL)
        return EXCESS;
    
    /* executing */
    *(var_pointer) = read_comp(varB, varC);
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
    int i;
    complex varA, varB;
    code defined = OK;

    char *part = strtok(NULL, REMOVABLE_TOKENS);
    if (part == NULL)
        return MISSING_VAR;
    
    /* VAR A */
    varA = get_comp_value(part[0], variables, &defined);
    if (defined != OK)
        return defined;

    /* COMMA */
    if (part[1] != '\0' && part[1] != ',')
        return UNDEFINED_VAR;
    if (part[1]=='\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL || part[0] != ',')
            return MISSING_COMMA;
        i = 1;
    }
    else
        i = 2;
    
    /* VAR B */
    if (part[i] == '\0')
    {
        part = strtok(NULL, REMOVABLE_TOKENS);
        if (part == NULL)
            return MISSING_VAR;
        
        varB = get_comp_value(part[0], variables, &defined);
        if (defined != OK)
            return defined;
        
        i = 1;
    }
    else
    {
        varB = get_comp_value(part[i], variables, &defined);
        if (defined != OK)
            return defined;
        i++;
    }

    if (part[i] != '\0' || strtok(NULL, REMOVABLE_TOKENS) != NULL)
        return EXCESS;
    
    /* executing */
    print_comp(sub_comp(varA, varB));
    return OK;
}