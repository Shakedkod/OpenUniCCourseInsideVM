#ifndef COMMAND_H
#define COMMAND_H
#include <stdlib.h>

#include "../coms.h"

#define NUM_OF_COMMANDS 16

typedef struct
{
    char *name;
    int opcode;
    int funct;
    state (*parse)(void *output, size_t line);
} command;

command *get_command(const char *name);
boolean command_exists(const char *name);

#endif