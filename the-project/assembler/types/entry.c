#include <stdlib.h>

#include "entry.h"

entry_node *init_entry_node()
{
	entry_node *output = malloc(sizeof(entry_node));
	
	if (output != NULL)
		output->next = NULL;
	return output;
}

void free_entries_list(entry_node *head)
{
	entry_node *current = head;
	entry_node *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}