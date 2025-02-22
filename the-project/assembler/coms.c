#include <stdio.h>

#include "coms.h"

state get_new_state()
{
    state output = DEFAULT_STATE;
    return output;
}

typedef enum 
{
    PATTERN_D,
    PATTERN_S,
    PATTERN_D_S,
    PATTERN_S_D,
    PATTERN_NONE
} format_pattern;

struct code_to_message
{
    code status;
    const char *msg;
    format_pattern pattern;
} messages[] = {
    /* WARNING */
        /* reader */
    {W_LINE_TOO_LONG, "Line %d is too long.", PATTERN_D},

    /* ERROR */
        /* macro related */
    {E_MACRO_UNNAMED, "The macro defined in line %d needs a name.", PATTERN_D},
    {E_MACRO_EXCESS, "In line %d at the call of macro '%s', there is excess characters after the name.", PATTERN_D_S},
    {E_MACRO_COMMAND_NAME, "In line %d the macro name '%s' is a command name, and thus not allowed.", PATTERN_D_S},
    {E_MACRO_DEF_EXCESS, "In line %d at the definiton of macro '%s', there is excess characters after the name.", PATTERN_D_S},
    {E_MACRO_ALREADY_DEFINED, "The macro %s, defined in line %d, is already defined.", PATTERN_S_D},
            /* macro name related */
    {E_MACRO_NAME_STARTS_WITH_DIGIT, "The macro defined in line %d, has an illegal name - Macros can't start with a digit.", PATTERN_D},
    {E_MACRO_NAME_ILLEGAL_CHARACTER, "The macro defined in line %d, has an illegal name - Illegal character '%s'.", PATTERN_D_S},
    
        /* memory */
    {E_MEMORY_NEEDED, "There isn't enough memory to assemble the program you entered. reached memory capacity at line %d.", PATTERN_D},
    
        /* reader */
    {E_READ_ERROR, "There was a reading error at line %d.", PATTERN_D}
};

void print_pattern(code warning, int line, char *data, boolean is_error)
{
    const char *msg;
    format_pattern patt;
    int i;
    boolean found = FALSE;

    for (i = 0; (!found) && (i < GET_ARRAY_LENGTH(messages)); i++)
    {
        if (messages[i].status == warning)
        {
            found = TRUE;
            msg = messages[i].msg;
            patt = messages[i].pattern;
        }
    }

    if (!found)
    {
        if (is_error)
            fprintf(stderr, "Unknown.\n");
        else
            printf("Unknown.\n");
        return;
    }

    if (is_error)
    {
        switch (patt)
        {
        case PATTERN_D:
            fprintf(stderr, msg, line);
            break;
        case PATTERN_S:
            fprintf(stderr, msg, data);
            break;
        case PATTERN_D_S:
            fprintf(stderr, msg, line, data);
            break;
        case PATTERN_S_D:
            fprintf(stderr, msg, data, line);
            break;
        case PATTERN_NONE:
            fputs(msg, stderr);
            break;
        
        default:
            fprintf(stderr, "Unknown.");
            break;
        }
        fprintf(stderr, "\n");
    }
    else
    {
        switch (patt)
        {
        case PATTERN_D:
            printf(msg, line);
            break;
        case PATTERN_S:
            printf(msg, data);
            break;
        case PATTERN_D_S:
            printf(msg, line, data);
            break;
        case PATTERN_S_D:
            printf(msg, data, line);
            break;
        case PATTERN_NONE:
            fputs(msg, stdout);
            break;
        
        default:
            printf("Unknown.");
            break;
        }
        printf("\n");
    }
}

void print_warning(code warning, int line, char *data)
{
    printf("WARNING: ");
    print_pattern(warning, line, data, FALSE);
}

void print_error(code error, int line, char *data)
{
    fprintf(stderr, "ERROR: ");
    print_pattern(error, line, data, TRUE);
}