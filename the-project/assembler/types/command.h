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

/*
    the function finds a command with the name given.

    input:
        1. const char *name: the name of the command to find.
    output(command *):
        a pointer to the command in question. NULL if there is no such command.
*/
command *get_command(const char *name);

/*
    checks if a command exists in the assembler.

    input:
        1. const char *name: the name of the command.
    output(boolean):
        TRUE if it does, else FALSE 
*/
boolean command_exists(const char *name);

#endif