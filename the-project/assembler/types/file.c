#include "file.h"

int num_of_lines(FILE *file)
{
    /* counts the number of lines in a file */
    int ch, lines = 1;
    
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
        return 0;
    fseek(file, 0, SEEK_SET);
    
    while ((ch = fgetc(file)) != EOF)
        if (ch == '\n')
            lines++;

    fseek(file, 0, SEEK_SET);
    return lines;
}

line_read read_line(FILE *file) 
{
    int len;
    line_read result;
    result.status = READ_ERROR;

    if (fgets(result.line, sizeof(result.line), file) != NULL)
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
        result.status = feof(file) ? READ_EOF : READ_ERROR;
        result.line[0] = '\0';
    }

    return result;
}

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
