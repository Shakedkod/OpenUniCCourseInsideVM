#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command.h"
#include "symbol.h"

boolean is_symbol_in_list(symbol_node *head, const char name[MAX_SYMBOL_NAME_LENGTH + 1]);

state check_symbol_name_validity(const char *name, symbol_node *head, macro_node macro_head, size_t line)
{
	size_t i = 1;
	state status = DEFAULT_STATE;
	status.line_num = line;
	strcpy(status.data, name);

	if (strlen(name) > MAX_SYMBOL_NAME_LENGTH)
		status.status = E_SYMBOL_NAME_ILLEGAL_LENGTH;

	if (status.status == OK)
	{
		if (isalpha(name[0]))
		{
			for (; (i < strlen(name)) && (status.status == OK); i++)
			{
				if (!isalpha(name[i]) && !isdigit(name[i]))
					status.status = E_SYMBOL_NAME_ILLEGAL_CHARACTER;
			}
		}
		else
			status.status = E_SYMBOL_NAME_START_ILLEGAL;
	}

	if (status.status == OK)
	{
		if (command_exists(name))
			status.status = E_SYMBOL_COMMAND_NAME;
		else if (is_symbol_in_list(head, name))
			status.status = E_SYMBOL_ALREADY_EXISTS;
		else if (get_macro_for_name(macro_head, name) != NULL)
			status.status = E_SYMBOL_MACRO_DEFINED;
	}

	return status;
}

symbol_node *init_symbol_node()
{
	symbol_node *output = malloc(sizeof(symbol_node));
	if (output != NULL)
	{
		output->next = NULL;
		output->value.value = NULL;
	}

	return output;
}

void free_symbols_list(symbol_node *head)
{
	symbol_node *current = head;
	symbol_node *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

symbol *get_symbol_in_list(symbol_node *head, const char name[MAX_SYMBOL_NAME_LENGTH + 1])
{
	if (head == NULL)
		return NULL;
	if (strcmp(head->value.name, name) == 0)
		return &(head->value);

	return get_symbol_in_list(head->next, name);
}

boolean is_symbol_in_list(symbol_node *head, const char name[MAX_SYMBOL_NAME_LENGTH + 1])
{
	return (get_symbol_in_list(head, name) != NULL);
}