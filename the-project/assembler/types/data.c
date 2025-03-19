#include <string.h>
#include <ctype.h>

#include "data.h"

void copy_data(data *dest, data input)
{
	dest->type = input.type;
	
	if (dest->type == STRING_DATA_TYPE || dest->type == SYMBOL_DATA_TYPE)
		dest->data.string = input.data.string;
	if (dest->type == INTEGER_DATA_TYPE)
		dest->data.integer = input.data.integer;
}

state check_valid_number(const char str[MAX_LINE_LENGTH], size_t length, size_t line)
{
	state status = DEFAULT_STATE;
	size_t i = 0;

	status.line_num = line;

	if (str[0] == '+' || str[0] == '-')
		i = 1;

	while (i < length && status.status == OK)
	{
		if (!isdigit(str[i]))
		{
			if (str[i] == '+' || str[i] == '-')
			{
				status.status = E_DATA_INTEGER_PLUS_MINUS_IN_THE_MIDDLE;
			}
			else
				status.status = E_DATA_INTEGER_NOT_DIGIT;
		}

		i++;
	}

	return status;
}

state get_string_indexes(size_t *string_start, size_t *string_end, char line[MAX_LINE_LENGTH], size_t line_num)
{
	state status = DEFAULT_STATE;
	size_t i = 0;
	boolean is_in_string = FALSE, was_in_string = FALSE;

	status.line_num = line_num;

	for (; (i < strlen(line)) && (status.status == OK); i++)
	{
		if (line[i] == '"')
		{
			if (is_in_string)
			{
				(*string_end) = i - 1;
				was_in_string = TRUE;
				is_in_string = FALSE;
			}
			else
			{
				if (was_in_string)
					status.status = E_DATA_STRING_EXTRA_STRING;
				else
				{
					(*string_start) = i + 1;
					is_in_string = TRUE;
				}
			}
		}
	}

	if (is_in_string)
		status.status = E_DATA_STRING_NOT_CLOSED;

	return status;
}