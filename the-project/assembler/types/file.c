#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "file.h"

size_t num_of_lines(FILE *file)
{
    /* counts the number of lines in a file */
    int ch;
    size_t lines = 1;
    
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
    size_t len;
    line_read result;
    result.status = READ_ERROR;

    if (fgets(result.line, sizeof(result.line), file) != NULL)
    {
        /* Check if we found newline */
        len = strlen(result.line);
        if (len >= MAX_LINE_LENGTH + 1)
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
    size_t i;
    
    if (str == NULL || str[0] == '\0')
        return TRUE;

    for (i = 0; i < strlen(str); i++)
        if (!isspace(str[i]))
            return FALSE;

    return TRUE;
}

state get_file(char *path, FILE **output, file_type type)
{
    state status = DEFAULT_STATE;
    char *filename = malloc(sizeof(char) * (strlen(path) + 4));

    strcpy(status.data, path);
    if (filename == NULL)
    {
        status.status = E_MEMORY_NEEDED;
        return status;
    }
    
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
        status.status = E_FILE_UNRECOGNIZED_FILE_TYPE;
        return status;
    }

    (*output) = fopen(filename, "r");
    if ((*output) == NULL)
        status.status = E_FILE_INVALID_PATH;

    free(filename);
    return status;
}

state save_file(FILE *file, const char *output_path, file_type format) 
{
    state status = DEFAULT_STATE;
    FILE *final_output;
    char buffer[MAX_LINE_LENGTH + 50];
    char *filename = malloc(sizeof(char) * (strlen(output_path) + 5));

    strcpy(status.data, output_path);
    if (filename == NULL)
    {
        status.status = E_MEMORY_NEEDED;
        return status;
    }

    if (!file)
    {
        status.status = E_SYSTEM_UNUSABLE_TEMP_FILE;
        return status;
    }
    if (!output_path)
    {
        status.status = E_FILE_INVALID_PATH;
        return status;
    }
    
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
        status.status = E_FILE_UNRECOGNIZED_FILE_TYPE;
        return status;
    }

    /* Open file */
    final_output = fopen(filename, "w");
    if (!final_output)
    {
        status.status = E_FILE_INVALID_PATH;
        return status;
    }

    /* starting from the start of the file */
    rewind(file);

    while (fgets(buffer, sizeof(buffer), file)) 
    {
        if (fputs(buffer, final_output) == EOF) 
        {
            fclose(final_output);
            free(filename);
            status.status = E_WRITE_ERROR;
            return status;
        }
    }

    fclose(final_output);
    free(filename);
    return status;
}

void free_lines_list(line_node* head)
{
    if (head != NULL)
    {
        free_lines_list(head->next);
        free(head);
    }
}

line_node* init_line_node()
{
    line_node *output = malloc(sizeof(line_node));
    if (output != NULL)
    {
        output->next = NULL;
        output->line[0] = '\0';
    }
    
    return output;
}

line_node* file_to_nodes(FILE* input, const char *input_name)
{
    line_read current;
    size_t i = 0, length = num_of_lines(input);
    line_node output = {NULL, "\0"};
    line_node *ptr = &output;
    char *part, copy[MAX_LINE_LENGTH + 1];
    state status = DEFAULT_STATE;
    strcpy(status.data, input_name);

    for (; (i < length) && (ptr != NULL); i++)
    {
        current = read_line(input);

        if (current.status == READ_TOO_LONG)
        {
            status.line_num = i;
            status.status = W_LINE_TOO_LONG;
            print_status(status);
            current.line[MAX_LINE_LENGTH] = '\0';
        }

        if (current.status != READ_ERROR)
        {
            ptr->next = init_line_node();
            ptr = ptr->next;

            if (ptr != NULL)
            {
                strcpy(copy, current.line);
                part = strtok(copy, WHITESPACES);

                if (part == NULL || part[0] != ';')
                    strcpy(ptr->line, current.line);
                else
                    ptr->line[0] = '\0';
            }
        }
        else
        {
            ptr->next = NULL;
            ptr = ptr->next;
        }
    }

    if (ptr == NULL)
    {
        free_lines_list(output.next);
        output.next = NULL;
    }
    return output.next;
}