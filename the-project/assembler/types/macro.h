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

/* MACRO TRIE */
typedef struct macro_node_s *macro_node_ptr;
typedef struct macro_node_s
{
    macro_node_ptr children[NUM_OF_ALLOWED_CHARACTERS];
    macro *data;
} macro_node;

/*
    adds a macro to the macros tree.

    input:
        1. macro_node *head: the head of the tree.
        2. macro *node: the node to be added to the tree.
*/
void add_macro_to_tree(macro_node *head, macro *node);

/*
    gets a macro that coresnondes to the name given from the tree.

    input:
        1. macro_node head: the head of the tree.
        2. const char *name: the name of the macro to be found.
    output(macro *):
        a pointer to the macro from the tree. NULL if not found.
*/
macro *get_macro_for_name(macro_node head, const char *name);

/*
    checks if the name for the macro is allowed.

    input:
        1. const char *name: the name to be checked.
        2. const macro_node head: the head of the macros tree.
        3. size_t line: the line that the macro is on - used for error output.
    output(state):
        the state that the program is in after the function.
*/
state is_name_allowed(const char *name, const macro_node head, size_t line);

/*
    deletes a macro tree.

    input:
        1. macro_node *head: the head of the tree to be deleted.
*/
void delete_tree(macro_node *head);

/*
    deletes a macro tree except the head and resets the data in the head.

    input:
        1. macro_node *head: the head of the tree to be deleted.
*/
void zeroize_macro_tree(macro_node *head);

#endif