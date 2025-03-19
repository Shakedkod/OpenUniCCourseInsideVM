#ifndef ADDRESS_H
#define ADDRESS_H

typedef unsigned int address;

typedef struct _an *address_node_ptr;
typedef struct _an
{
	address_node_ptr next;
	address position;
} address_node;

address_node *init_address_node();
void free_addresses_list(address_node *head);
void copy_addresses_list(address_node *dest, address_node *input);

#endif