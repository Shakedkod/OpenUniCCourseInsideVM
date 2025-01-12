#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "string_manipulation.h"

char *to_lowercase(char *str) 
{
    int i = 0;
    
    if (!str)
        return NULL;
    
    while (str[i] != '\0') 
    {
        str[i] = tolower((unsigned char)str[i]);
        i++;
    }
    
    return str;
}

char *remove_prefix(char *str, int n)
{
    int length, i;
    
    if (!str || n < 0)
        return NULL;
    
    length = strlen(str);
    if (n >= length) 
    {
        str[0] = '\0';
        return str;
    }
    
    i = 0;
    while (str[i + n] != '\0') 
    {
        str[i] = str[i + n];
        i++;
    }

    str[i] = '\0';
    return str;
}

int is_all_whitespaces(const char *str)
{
    int i;
    if (str == NULL || str[0] == '\0')
        return 1;
    
    for (i = 0; i < strlen(str); i++)
        if (!isspace(str[i]))
            return 0;

    return 1;
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

char *get_string_until_first_space(char *str)
{

}