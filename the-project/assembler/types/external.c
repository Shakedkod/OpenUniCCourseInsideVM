#include <stdlib.h>
#include <string.h>

#include "external.h"

external_node* init_external_node()
{
	external_node* output = malloc(sizeof(external_node));
	if (output != NULL)
	{
		output->next = NULL;
		output->value.locations = NULL;
	}

	return output;
}

void free_externals_list(external_node* head)
{
	external_node *current = head;
	external_node *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free_addresses_list(temp->value.locations);
		free(temp);
	}
}

external *get_external_in_list(external_node *head, char name[MAX_SYMBOL_NAME_LENGTH + 1])
{
	external *output = NULL;
	external_node *ptr = head;

	while (ptr != NULL && output == NULL)
	{
		if (strcmp(ptr->value.name, name) == 0)
			output = &(ptr->value);
		ptr = ptr->next;
	}

	return output;
}
