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

entry_node *init_entry_node();
void free_entries_list(entry_node *head);

#endif