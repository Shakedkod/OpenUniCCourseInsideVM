#include <string.h>

#include "macro_workshop.h"
#include "types/file.h"
#include "types/command.h"

state create_macro(FILE *file, macro *output, macro_node *tree, int current_line)
{
    char *part, *buffer, *pos, *temp;
    line_read current;
    size_t buffer_len = 0, buffer_size = 0, line_len = 0;
    state status = {OK, "", current_line};

    /* name */
    part = strtok(NULL, WHITESPACES);
    if (part == NULL)
    {
        status.status = E_MACRO_UNNAMED;
        return status;
    }
    if (command_exists(part))
    {
        status.status = E_MACRO_COMMAND_NAME;
        status.data = part;
        return status;
    }
    if ((status = is_name_allowed(part, *tree, current_line)).status != OK)
        return status;
    output->name = part;
    status.data = output->name;
    
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        status.status = E_MACRO_DEF_EXCESS;
        return status;
    }
    
    /* value */
    status.line_num++;
    current = read_line(file);
    buffer_size = MAX_LINE_LENGTH * sizeof(char);
    buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
        status.status = E_MEMORY_NEEDED;
        return status;
    }

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
                    status.status = E_MEMORY_NEEDED;
                    return status;
                }
                buffer = temp;
                pos = buffer + strlen(buffer);
            }

            /* updates buffer with new line */
            strcat(pos, current.line);
            strcat(pos, "\n");
            pos = buffer + strlen(buffer);

            current = read_line(file);
            status.line_num++;
        }
    }
    if (current.status == READ_ERROR)
    {
        free(buffer);
        status.status = E_READ_ERROR;
        return status;
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
                    status.status = E_MEMORY_NEEDED;
                    return status;
                }
                buffer = temp;
                pos = buffer + strlen(buffer);
            }

            /* updates buffer with new line */
            strcat(pos, current.line);
            strcat(pos, "\n");
            pos = buffer + strlen(buffer);

            current = read_line(file);
            status.line_num++;
        }
    }

    buffer_len = strlen(buffer);
    output->value = malloc(buffer_len + 1);
    if (output->value == NULL)
    {
        free(buffer);
        status.status = E_MEMORY_NEEDED;
        return status;
    }
    strcpy(output->value, buffer);

    add_macro_to_tree(tree, *output);
    free(buffer);
    return status;
}

state expand_macros(FILE *input, FILE **output, macro_node *output_macros)
{
    FILE *temp_file = tmpfile();
    int lines = num_of_lines(input), i;
    line_read current;
    macro *current_macro = NULL;
    char *part;
    state status = {OK, "", 0};

    if (!temp_file)
    {
        status.status = E_MEMORY_NEEDED;
        return status;
    }

    for (i = 0; i < lines; i++)
    {
        status.line_num = i;
        current = read_line(input);
        if (current.status == READ_ERROR)
        {
            fclose(temp_file);
            status.status = E_READ_ERROR;
            return status;
        }
        
        /* check the first part of the line*/
        part = strtok(current.line, WHITESPACES);
        if (!part) /* the line is only WHITESPACES */
            fputs(current.line, temp_file);
        else if ((current_macro = get_macro_for_name(*output_macros, part)) != NULL) /* found a usable macro */
            fputs(current_macro->value, temp_file);
        else if (strcmp(part, MACRO_DEF_START) == 0) /* found a macro definition */
        {
            if ((status = create_macro(input, current_macro, output_macros, i)).status != OK)
            {
                fclose(temp_file);
                return status;
            }
            i = status.line_num; /* forwarding i past the macro */
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

    if (status.status == OK)
        *output = temp_file;
    else
        fclose(temp_file);
    return status;
}