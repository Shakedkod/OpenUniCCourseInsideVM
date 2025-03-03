#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

char *get_extention_for_type(file_type type)
{
    switch (type)
    {
    case FILE_AS:
        return ".as";
    case FILE_AM:
        return ".am";
    case FILE_ENT:
        return ".ent";
    case FILE_EXT:
        return ".ext";
    case FILE_OB:
        return ".ob";
    
    default:
        return NULL;
    }
}

code get_file(char *path, FILE **output, file_type type)
{
    char *filename = malloc(sizeof(char) * (strlen(path) + 4));
    if (filename == NULL)
        return E_MEMORY_NEEDED;
    
    strcpy(filename, path);

    switch (type)
    {
    case FILE_AS:
        strcat(filename, ".as");
        break;
    case FILE_AM:
        strcat(filename, ".am");
        break;
    case FILE_ENT:
        strcat(filename, ".ent");
        break;
    case FILE_EXT:
        strcat(filename, ".ext");
        break;
    case FILE_OB:
        strcat(filename, ".ob");
        break;
    
    default:
        free(filename);
        return E_FILE_UNRECOGNIZED_FILE_TYPE;
    }

    (*output) = fopen(filename, "r");
    free(filename);
    return OK;
}

code save_file(FILE *file, const char *output_path, file_type format) 
{
    FILE *final_output;
    char buffer[MAX_LINE_LENGTH + 50];
    char *filename = malloc(sizeof(char) * (strlen(output_path) + 4));
    if (filename == NULL)
        return E_MEMORY_NEEDED;

    if (!file)
        return E_SYSTEM_UNUSABLE_TEMP_FILE;
    if (!output_path)
        return E_FILE_INVALID_PATH;
    
    strcpy(filename, output_path);
    switch (format)
    {
    case FILE_AS:
        strcat(filename, ".as");
        break;
    case FILE_AM:
        strcat(filename, ".am");
        break;
    case FILE_ENT:
        strcat(filename, ".ent");
        break;
    case FILE_EXT:
        strcat(filename, ".ext");
        break;
    case FILE_OB:
        strcat(filename, ".ob");
        break;
    
    default:
        free(filename);
        return E_FILE_UNRECOGNIZED_FILE_TYPE;
    }

    /* Open file */
    final_output = fopen(
        filename, (format == FILE_OB) 
            ? "wb" 
            : "w"
    );
    if (!final_output)
        return E_FILE_INVALID_PATH;

    /* starting from the start of the file */
    rewind(file);

    if (format == FILE_OB) /* write binary file */
    {
        /* ??? */
    }
    else /* write normal text files */
    {
        while (fgets(buffer, sizeof(buffer), file)) 
        {
            if (fputs(buffer, final_output) == EOF) 
            {
                fclose(final_output);
                free(filename);
                return E_WRITE_ERROR;
            }
        }
    }

    fclose(final_output);
    free(filename);
    return OK;
}