#ifndef MACRO_H
#define MACRO_H
#include <stdlib.h>

#include "../coms.h"

#define NUM_OF_ALLOWED_CHARACTERS 53 /* 26 small characters, 26 large characters and one underscore */
#define MACRO_DEF_START "macro"
#define MACRO_DEF_END "macroend"

/* MACRO TYPE */
typedef struct
{
    char *name;
    char *value;
} macro;

boolean is_name_allowed(const char *name);
boolean equals(macro a, macro b);

/* MACRO TRIE */
typedef struct macro_node *macro_node_ptr;
typedef struct
{
    macro_node_ptr children[NUM_OF_ALLOWED_CHARACTERS];
    macro data;
} macro_trie;

macro_trie init_macro_trie();
void add_macro_to_tree(macro_trie *head, macro node);
macro *get_macro_for_name(macro_trie head, const char *name);

#endif