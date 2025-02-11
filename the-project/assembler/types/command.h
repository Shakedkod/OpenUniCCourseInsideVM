#ifndef COMMAND_H
#define COMMAND_H
#include "../coms.h"

#define ALLOWED_COMMAND_LETTERS 26

typedef struct command_trie *command_ptr;
typedef struct
{
    command_ptr children[ALLOWED_COMMAND_LETTERS];
    void *data; /* REPLACE WITH REAL DATA */
} command_trie;

boolean command_exists(const char *name);

#endif