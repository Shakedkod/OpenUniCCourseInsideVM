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
    /* TODO */
} command;

command *get_command(const char *name);
boolean command_exists(const char *name);

char *write_command(command cmd /*TODO: OPERATORS*/);

#endif