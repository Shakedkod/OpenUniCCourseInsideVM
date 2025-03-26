#ifndef ADDRESS_H
#define ADDRESS_H

typedef unsigned int address;

typedef struct _an *address_node_ptr;
typedef struct _an
{
	address_node_ptr next;
	address position;
} address_node;

/*
	this function creates an address node and puts it in a position in memory.

	output(address_node *):
		a pointer to the address node created.
*/
address_node *init_address_node();

/*
	this function frees the addresses list given to it.
	the head will be null after this function.

	input:
		1. address_node *head: the head of the list.
*/
void free_addresses_list(address_node *head);

#endif