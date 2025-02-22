#include <string.h>

#include "macro_workshop.h"
#include "types/file.h"
#include "types/command.h"

code create_macro(FILE *file, macro *output, macro_node *tree)
{
    char *part, *buffer, *pos, *temp;
    line_read current;
    size_t buffer_len = 0, buffer_size = 0, line_len = 0;
    code status = OK;

    /* name */
    part = strtok(NULL, WHITESPACES);
    if (part == NULL)
        return E_MACRO_UNNAMED;
    if (command_exists(part))
        return E_MACRO_COMMAND_NAME;
    if ((status = is_name_allowed(part, *tree)) != OK)
        return status;
    output->name = part;
    
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
        return E_MACRO_DEF_EXCESS;
    
    /* value */
    current = read_line(file);
    buffer_size = MAX_LINE_LENGTH * sizeof(char);
    buffer = malloc(buffer_size);
    if (buffer == NULL)
        return E_MEMORY_NEEDED;

    pos = buffer;
    *pos = '\0';

    while (!(current.status == READ_ERROR || current.status == READ_EOF) && !strcmp(part, MACRO_DEF_END))
    {
        part = strtok(current.line, WHITESPACES);
        if ((part != NULL) && !strcmp(part, MACRO_DEF_END))
        {
            line_len = strlen(current.line);
            buffer_len += line_len;

            /* checks if we need to resize the buffer */
            if (buffer_size < buffer_len + 1)
            {
                buffer_size += MAX_LINE_LENGTH;
                temp = realloc(buffer, buffer_size);
                if (temp == NULL)
                {
                    free(buffer);
                    return E_MEMORY_NEEDED;
                }
                buffer = temp;
                pos = buffer + strlen(buffer);
            }

            /* updates buffer with new line */
            strcat(pos, current.line);
            strcat(pos, "\n");
            pos = buffer + strlen(buffer);

            current = read_line(file);
        }
    }
    if (current.status == READ_ERROR)
    {
        free(buffer);
        return E_READ_ERROR;
    }
    if (current.status == READ_EOF)
    {
        part = strtok(current.line, WHITESPACES);
        if ((part != NULL) && !strcmp(part, MACRO_DEF_END))
        {
            line_len = strlen(current.line);
            buffer_len += line_len;

            /* checks if we need to resize the buffer */
            if (buffer_size < buffer_len + 1)
            {
                buffer_size += MAX_LINE_LENGTH;
                temp = realloc(buffer, buffer_size);
                if (temp == NULL)
                {
                    free(buffer);
                    return E_MEMORY_NEEDED;
                }
                buffer = temp;
                pos = buffer + strlen(buffer);
            }

            /* updates buffer with new line */
            strcat(pos, current.line);
            strcat(pos, "\n");
            pos = buffer + strlen(buffer);

            current = read_line(file);
        }
    }

    buffer_len = strlen(buffer);
    output->value = malloc(buffer_len + 1);
    if (output->value == NULL)
    {
        free(buffer);
        return E_MEMORY_NEEDED;
    }
    strcpy(output->value, buffer);

    add_macro_to_tree(tree, *output);
    free(buffer);
    return OK;
}

code expand_macros(FILE *input, FILE **output, macro_node *output_macros)
{
    FILE *temp_file = tmpfile();
    int lines = num_of_lines(input), i;
    line_read current;
    macro *current_macro = NULL;
    char *part;
    code status = OK;

    if (!temp_file)
        return E_MEMORY_NEEDED;

    for (i = 0; i < lines; i++)
    {
        current = read_line(input);
        if (current.status == READ_ERROR)
        {
            fclose(temp_file);
            return E_READ_ERROR;
        }
        
        /* check the first part of the line*/
        part = strtok(current.line, WHITESPACES);
        if (!part) /* the line is only WHITESPACES */
            fputs(current.line, temp_file);
        else if ((current_macro = get_macro_for_name(*output_macros, part)) != NULL) /* found a usable macro */
            fputs(current_macro->value, temp_file);
        else if (strcmp(part, MACRO_DEF_START) == 0) /* found a macro definition */
        {
            if ((status = create_macro(input, current_macro, output_macros)) != OK)
            {
                fclose(temp_file);
                return status;
            }
            /* 
                removes the last newline char so that when I add one at the end of this repetition of the while loop, 
                there won't be an extra empty line
            */
            fseek(temp_file, -1, SEEK_CUR);
        }
        else /* not a macro */
            fputs(current.line, temp_file);
        
        /* moves the temp_file to the next line */
        fprintf(temp_file, "\n");
    }

    if (status == OK)
        *output = temp_file;
    else
        fclose(temp_file);
    return status;
}