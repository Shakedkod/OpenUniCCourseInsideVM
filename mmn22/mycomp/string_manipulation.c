#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "string_manipulation.h"

boolean is_all_whitespaces(const char *str)
{
    int i;
    
    if (str == NULL || str[0] == '\0')
        return TRUE;

    for (i = 0; i < strlen(str); i++)
        if (!isspace(str[i]))
            return FALSE;

    return TRUE;
}

code strcmp_for_commands(const char *a, const char *b)
{
    /*
    returns:
        0 - strings are not equal
        1 - strings are equal
        2 - start of string a is equal to string b
        3 - string are equal but a has a comma at the end
    */

    int len_a = strlen(a), len_b = strlen(b), i = 0;

    if (len_a < len_b)
        return CONTINUE;

    if (len_a == len_b)
    {
        for (; i < len_a; i++)
        {
            if (a[i] != b[i])
                return CONTINUE;
        }
        return OK;
    }
    
    for (; i < len_b; i++)
    {
        if (a[i] != b[i])
            return CONTINUE;
    }

    if (a[len_b] == ',')
        return ILLEGAL_COMMA;
    return UNDEFINED_COMMAND;
}