#include <string.h>

#include "macro_workshop.h"
#include "types/file.h"

code create_macro(FILE *file, macro *output, macro_trie *tree)
{
    char data[80], *part;
    line_read current;

    /* name */
    part = strtok(NULL, WHITESPACES);
    if (part == NULL)
        return E_MACRO_UNNAMED;
    if (command_exists(part))
        return E_MACRO_COMMAND_NAME;
    if (!is_name_allowed(part))
        return E_MACRO_ILLEGAL_NAME;
    output->name = part;
    
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
        return E_MACRO_DEF_EXCESS;
    
    /* value */
    current = read_line(file);
    while (current.status != READ_ERROR && !strcmp(part, MACRO_DEF_END))
    {
        part = strtok(current.line, WHITESPACES);
        if ((part == NULL) || !strcmp(part, MACRO_DEF_END))
        {
            /* TODO, REALLOC THE STRING EACH TIME AND WORK ON IT. */
        }
    }
    if (current.status == READ_ERROR)
        return E_READ_ERROR;

    output->value = data;
    add_macro_to_tree(tree, *output);
}

code expand_macros(FILE *input, FILE **output, macro_trie *output_macros)
{
    FILE *temp_file = tmpfile();
    int lines = num_of_lines(input), i;
    line_read current;
    macro *current_macro = NULL;
    char *part;
    code status = OK;

    for (i = 0; i < lines; i++)
    {
        current = read_line(input);
        if (current.status == READ_ERROR)
            return E_READ_ERROR;
        
        /* check the first part of the line*/
        part = strtok(current.line, WHITESPACES);
        if (!part) /* the line is only WHITESPACES */
            fprintf(temp_file, current.line);
        else if ((current_macro = get_macro_for_name(*output_macros, part)) != NULL) /* found a usable macro */
            fprintf(temp_file, current_macro->value);
        else if (strcmp(part, MACRO_DEF_START)) /* found a macro definition */
        {
            if ((status = create_macro(input, current_macro, output_macros)) != OK) /* TODO */
        }
        else /* not a macro */
            fprintf(temp_file, current.line);
        
        /* moves the temp_file to the next line */
        fprintf(temp_file, "\n");
    }
    
    return status;
}