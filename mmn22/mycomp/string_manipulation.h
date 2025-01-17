#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#include "coms.h"

/*
    checks if a string is just whitespaces == spaces or tabs.

    input:
        char *str: the string to be checked.
    
    output(boolean):
        TRUE if all whitespaces. FALSE if not.
*/
boolean is_all_whitespaces(const char *str);

/*
    compers two strings and returns a fitting code.

    input:
        char *a: the string to be compered to.
        char *b: the string to be compered against.
    
    output(code):
        OK if they are equal.
        CONTINUE if they are not equal.
        ILLEGAL_COMMA if the start of a is equal to b, but a has a comma after.
        UNDEFINED_COMMAND if the start of a is equal to b, but has excess.
*/
code strcmp_for_commands(const char *a, const char *b);

#endif