#include <string.h>

#include "command.h"

command_node *get_new_node()
{
    command_node result = {{NULL}, NULL};
    return &result;
}

command_node get_commands()
{
    int i, j, name_len;
    char *name;
    command *current;
    command_node result = {{NULL}, NULL};
    command_node *ptr;
    
    for (i = 0; i < GET_ARRAY_LENGTH(commands_list); i++)
    {
        current = &(commands_list[i]);
        name = current->name;
        name_len = strlen(name);
        ptr = &result;

        for (j = 0; j < name_len; j++)
        {
            if (ptr->children[GET_LETTER_INDEX(name[i])] == NULL)
                ptr->children[GET_LETTER_INDEX(name[i])] = get_new_node();
            
            ptr = ptr->children[GET_LETTER_INDEX(name[i])];
        }
        
        ptr->value = current;
    }
    

    return result;
}

command *get_command(const char *name)
{
    int i, len = strlen(name);
    command_node head = get_commands();
    command_node *ptr = &head;

    for (i = 0; i < len; i++)
    {
        if (ptr->children[GET_LETTER_INDEX(name[i])] == NULL)
            return NULL;
        
        ptr = ptr->children[GET_LETTER_INDEX(name[i])];
    }

    return ptr->value;
}

boolean command_exists(const char *name)
{
    return (get_command(name) != NULL);
}
