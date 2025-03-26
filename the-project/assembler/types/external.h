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

external_node *init_external_node();
void free_externals_list(external_node *head);
external *get_external_in_list(external_node *head, char name[MAX_SYMBOL_NAME_LENGTH + 1]);

#endif