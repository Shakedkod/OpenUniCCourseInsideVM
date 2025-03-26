#include <stdlib.h>

#include "address.h"

address_node *init_address_node()
{
	address_node *output = malloc(sizeof(address_node));
	if (output != NULL)
		output->next = NULL;

	return output;
}

void free_addresses_list(address_node *head)
{
	address_node *current = head;
	address_node *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}