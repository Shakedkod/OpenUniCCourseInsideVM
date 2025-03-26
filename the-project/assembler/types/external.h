#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "address.h"
#include "../coms.h"

typedef struct
{
	char name[MAX_SYMBOL_NAME_LENGTH + 1];
	address_node *locations;
} external;

typedef struct _exn *external_node_ptr;
typedef struct _exn
{
	external_node_ptr next;
	external value;
} external_node;

/*
	this function creates an external node and puts it in a position in memory.

	output(external_node *):
		a pointer to the external node created.
*/
external_node *init_external_node();

/*
	this function frees the externals list given to it.
	the head will be null after this function.

	input:
		1. external_node *head: the head of the list.
*/
void free_externals_list(external_node *head);

/*
	the function gets an external by name in the list given.

	input:
		1. external_node *head: the head of the list to be checked.
		2. char name[MAX_SYMBOL_NAME_LENGTH + 1]: the name of the symbol to be found.
	output(external *):
		a pointer to the external node found in the list. NULL if not found.
*/
external *get_external_in_list(external_node *head, char name[MAX_SYMBOL_NAME_LENGTH + 1]);

#endif