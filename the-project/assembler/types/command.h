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

command *get_command(const char *name);
boolean command_exists(const char *name);

char *write_command(command cmd /*TODO: OPERATORS*/);

#endif