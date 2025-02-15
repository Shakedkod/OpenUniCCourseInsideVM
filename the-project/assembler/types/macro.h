#ifndef MACRO_H
#define MACRO_H
#include <stdlib.h>

#include "../coms.h"

/* for the definition in the next line: 26 small characters, 26 large characters and one underscore */
#define NUM_OF_ALLOWED_CHARACTERS ((2 * NUMBER_OF_ALPHABETIC_LETTERS) + NUMBER_OF_ALLOWED_NUMBERS + 1) 
#define MACRO_DEF_START "macro"
#define MACRO_DEF_END "macroend"

/* MACRO TYPE */
typedef struct
{
    char *name;
    char *value;
} macro;

code is_name_allowed(const char *name);
boolean equals(macro a, macro b);

/* MACRO TRIE */
typedef struct macro_node *macro_node_ptr;
typedef struct
{
    macro_node_ptr children[NUM_OF_ALLOWED_CHARACTERS];
    macro *data;
} macro_node;

macro_node init_macro_node();
void add_macro_to_tree(macro_node *head, macro node);
macro *get_macro_for_name(macro_node head, const char *name);

#endif