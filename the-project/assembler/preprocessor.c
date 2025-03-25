#include <string.h>

#include "preprocessor.h"
#include "types/file.h"
#include "types/command.h"

state create_macro(FILE *file, macro *output, macro_node *tree, size_t current_line)
{
    char *part, *buffer, *pos, *temp, line_copy[MAX_LINE_LENGTH + 2];
    line_read current;
    size_t buffer_len = 0, buffer_size = 0, line_len = 0;
    state status = DEFAULT_STATE;
    status.line_num = current_line;
    output = malloc(sizeof(macro_node));

    if (output == NULL)
    {
        status.status = E_MEMORY_NEEDED;
        return status;
    }
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
        strcpy(status.data, part);
        return status;
    }

    status = is_name_allowed(part, *tree, current_line);
    if (status.status != OK)
        return status;
    
    strcpy(output->name, part);
    strcpy(status.data, output->name);
    
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
    strcpy(buffer, "");

    pos = buffer;

    while (!(current.status == READ_ERROR || current.status == READ_EOF) && (part == NULL || strcmp(part, MACRO_DEF_END) != 0))
    {
        strcpy(line_copy, current.line);
        part = strtok(current.line, WHITESPACES);
        if ((part != NULL) && strcmp(part, MACRO_DEF_END))
        {
            line_len = strlen(line_copy);
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
            strcat(pos, line_copy);
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
        memcpy(line_copy, current.line, sizeof(current.line));
        part = strtok(current.line, WHITESPACES);
        if (strcmp(part, MACRO_DEF_END) != 0)
        {
            status.status = E_MACRO_NOT_CLOSED;
            return status;
        }
    }
    
    part = strtok(NULL, WHITESPACES);
    if (part != NULL && part[0] != '\n' && part[0] != '\0')
    {
        status.status = E_MACRO_DEF_END_EXCESS;
        return status;
    }

    buffer_len = strlen(buffer);
    output->value = malloc(buffer_len);
    if (output->value == NULL)
    {
        free(buffer);
        status.status = E_MEMORY_NEEDED;
        return status;
    }
    buffer[strlen(buffer) - 1] = '\0'; /* replacing the last '\n' */
    strcpy(output->value, buffer);

    add_macro_to_tree(tree, output);
    free(buffer);
    return status;
}

state expand_macros(FILE *input, FILE **output, macro_node *output_macros, const char *file_output_name)
{
    FILE *temp_file = tmpfile();
    size_t lines = num_of_lines(input), i;
    line_read current;
    macro *current_macro = NULL;
    char *part, *dup_line, *symbol_name = NULL;
    state status = DEFAULT_STATE;
    boolean is_symbol = FALSE;

    if (!temp_file)
    {
        status.status = E_MEMORY_NEEDED;
        return status;
    }

    fseek(input, 0, SEEK_SET);
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
        dup_line = malloc(sizeof(current.line));
        if (dup_line == NULL)
        {
            fclose(temp_file);
            status.status = E_MEMORY_NEEDED;
            return status;
        }

        strcpy(dup_line, current.line);
        part = strtok(current.line, WHITESPACES);
        if (part != NULL && part[strlen(part) - 1] == ':')
        {
            is_symbol = TRUE;
            symbol_name = malloc((strlen(part) * sizeof(char)) + sizeof(char));
            if (symbol_name == NULL)
            {
                fclose(temp_file);
                status.status = E_MEMORY_NEEDED;
                return status;
            }

            strcpy(symbol_name, part);
            part = strtok(NULL, WHITESPACES);
        }

        if (part == NULL) /* the line is only WHITESPACES */
            fputs(dup_line, temp_file);
        else if ((current_macro = get_macro_for_name(*output_macros, part)) != NULL) /* found a usable macro */
        {
            if (is_symbol)
            {
                fputs(symbol_name, temp_file);
                fputs(" ", temp_file);
            }
            fputs(current_macro->value, temp_file);
        }
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
            fputs(dup_line, temp_file);
        
        /* moves the temp_file to the next line */
        fprintf(temp_file, "\n");
        free(dup_line);
        is_symbol = FALSE;

        if (symbol_name != NULL)
        {
            free(symbol_name);
            symbol_name = NULL;
        }
    }

    if (status.status == OK)
    {
        *output = temp_file;

        status = save_file(temp_file, file_output_name, FILE_AM);
        fclose(temp_file);
    }
    else
        fclose(temp_file);

    return status;
}