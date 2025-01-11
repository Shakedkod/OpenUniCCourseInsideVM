#include <stdio.h>

#include "user_interface.h"
#include "string_manipulation.h"
#include "coms.h"

code read_line()
{
    char *command;
    
    /* removing all of the whitespaces */
    scanf("%s", command);
    while (is_all_whitespaces(command))
        scanf("%s", command);
    
    if (command[0] == ',')
        return ILLEGAL_COMMA;
    
    

    return OK;
}

/* COMMANDS FUNCTIONS */
