#include <string.h>

#include "command.h"

command commands[NUM_OF_COMMANDS] = {
    /*   name opcode funct   */
        {"add",   2,   1},
        {"bne",   9,   2},
        {"clr",   5,   1},
        {"cmp",   1,   0},
        {"dec",   5,   4},
        {"inc",   5,   3},
        {"jmp",   9,   1},
        {"jsr",   9,   3},
        {"lea",   4,   0},
        {"mov",   0,   0},
        {"not",   5,   2},
        {"prn",   13,  0},
        {"red",   12,  0},
        {"rts",   14,  0},
        {"stop",  15,  0},
        {"sub",   2,   2}
};

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
