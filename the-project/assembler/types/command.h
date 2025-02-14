#ifndef COMMAND_H
#define COMMAND_H
#include "../coms.h"

typedef struct command_node *command_ptr;
typedef struct
{
    command_ptr children[NUMBER_OF_ALPHABETIC_LETTERS];
    void *data; /* REPLACE WITH REAL DATA */
} command_node;

boolean command_exists(const char *name);

#endif