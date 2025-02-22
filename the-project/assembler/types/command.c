#include <string.h>

#include "command.h"

command *get_command(const char *name)
{
    int mid, left = 0, right = NUM_OF_COMMANDS - 1;
    char command_letter, name_letter = name[0];
    
    while (left <= right)
    {
        mid = (left + right) / 2;

        command_letter = commands[mid].name[0];
        if (command_letter == name_letter)
        {
            if (commands[mid].name[1] == name[1])
                return &(commands[mid]);
        }
        else if (command_letter < name_letter)
            right = mid - 1;
        else
            left = mid + 1;
    }
    
    return NULL;
}

boolean command_exists(const char *name)
{
    return (get_command(name) != NULL);
}
