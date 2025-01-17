#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "coms.h"

/* 
    a functions that read's a line from stdin and execute the command that has been given according to a set of rules and guidelines

    input:
        vars variables: pointers to the six variables that are used in the commands.
        boolean *is_eof: pointer to a boolean that is changed to TRUE if the line ends in EOF.
    
    output(code):
        Error notice code or approval code.
*/
code execute_line(vars variables, boolean *is_eof);

#endif