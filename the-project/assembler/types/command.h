#ifndef COMMAND_H
#define COMMAND_H
#include <stdlib.h>

#include "../coms.h"

typedef struct
{
    char *name;
    int opcode;
    int funct;
    /* TODO */
} command;

command commands_list[16] = {
    {"add", 2, 1},
    {"bne", 9, 2},
    {"clr", 5, 1},
    {"cmp", 1, 0},
    {"dec", 5, 4},
    {"inc", 5, 3},
    {"jmp", 9, 1},
    {"jsr", 9, 3},
    {"lea", 4, 0},
    {"mov", 0, 0},
    {"not", 5, 2},
    {"prn", 13, 0},
    {"red", 12, 0},
    {"rts", 14, 0},
    {"stop", 15, 0},
    {"sub", 2, 2}
};

typedef struct command_node *command_ptr;
typedef struct
{
    command_ptr children[NUMBER_OF_ALPHABETIC_LETTERS];
    command *value;
} command_node;

command_node get_commands();

command *get_command(const char *name);
boolean command_exists(const char *name);

#endif