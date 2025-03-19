#ifndef MACRO_H
#define MACRO_H
#include <stdlib.h>

#include "../coms.h"

/* for the definition in the next line: 26 small characters, 26 large characters and one underscore */
#define NUM_OF_ALLOWED_CHARACTERS ((2 * NUMBER_OF_ALPHABETIC_LETTERS) + NUMBER_OF_ALLOWED_NUMBERS + 1) 
#define MACRO_DEF_START "mcro"
#define MACRO_DEF_END "mcroend"
#define DEFAULT_MACRO_NODE {{NULL}, NULL}

/* MACRO TYPE */
typedef struct
{
    char name[MAX_LINE_LENGTH - 4]; /* MAX_LINE_LENGTH + 1 - 5(length of 'mcro ') */
    char *value;
} macro;

boolean equals(macro a, macro b);

/* MACRO TRIE */
typedef struct macro_node_s *macro_node_ptr;
typedef struct macro_node_s
{
    macro_node_ptr children[NUM_OF_ALLOWED_CHARACTERS];
    macro *data;
} macro_node;

void add_macro_to_tree(macro_node *head, macro *node);
macro *get_macro_for_name(macro_node head, const char *name);
state is_name_allowed(const char *name, const macro_node head, size_t line);
macro *get_macro_for_name(macro_node head, const char *name);
void delete_tree(macro_node *head);
void zeroize_macro_tree(macro_node *head);

#endif