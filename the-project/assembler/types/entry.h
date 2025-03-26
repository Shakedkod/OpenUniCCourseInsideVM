#ifndef ENTRY_H
#define ENTRY_H

#include "../coms.h"
#include "address.h"

typedef struct
{
	address appearance;
	char name[MAX_SYMBOL_NAME_LENGTH + 1];
} entry;

typedef struct _enn *entry_node_ptr;
typedef struct _enn
{
	entry_node_ptr next;
	entry value;
} entry_node;

/*
	this function creates an entry node and puts it in a position in memory.

	output(entry_node *):
		a pointer to the entry node created.
*/
entry_node *init_entry_node();

/*
	this function frees the entries list given to it.
	the head will be null after this function.

	input:
		1. entry_node *head: the head of the list.
*/
void free_entries_list(entry_node *head);

#endif