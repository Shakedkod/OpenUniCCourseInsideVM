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

void copy_addresses_list(address_node *dest, address_node *input)
{
	address_node *ptr = input, *result_ptr = dest;

	dest = init_address_node();
	while (ptr != NULL)
	{
		result_ptr->next = malloc(sizeof(address_node));
		if (result_ptr->next != NULL)
		{
			result_ptr = result_ptr->next;
			result_ptr->position = ptr->position;
		}

		ptr = ptr->next;
	}

	dest = dest->next;
}
