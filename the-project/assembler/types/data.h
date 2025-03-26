#ifndef DATA_H
#define DATA_H

#include <stdio.h>

#include "../coms.h"

#define DATA_DATA_DIRECTIVE "data"
#define DATA_DATA_DIRECTIVE_NO_SPACE ".data"
#define DATA_STRING_DIRECTIVE "string"
#define DATA_STRING_DIRECTIVE_NO_SPACE ".string"
#define DATA_EXTERN_DIRECTIVE "extern"
#define DATA_EXTERN_DIRECTIVE_NO_SPACE ".extern"
#define DATA_ENTRY_DIRECTIVE "entry"
#define DATA_ENTRY_DIRECTIVE_NO_SPACE ".entry"

#define DATA_DATA_SEPARATOR ','
#define DATA_STRING_CAP '"'

#define MAX_INTEGER 1048575

typedef enum
{
	UNKNOWN_DATA_TYPE,
	STRING_DATA_TYPE,
	INTEGER_DATA_TYPE,
	SYMBOL_DATA_TYPE
} data_type;

typedef struct
{
	data_type type;
	union
	{
		char symbol[MAX_SYMBOL_NAME_LENGTH + 1];
		char string;
		int integer;
	} data;
} data;

state check_valid_number(const char str[MAX_LINE_LENGTH], size_t length, size_t line);
state get_string_indexes(size_t *string_start, size_t *string_end, char line[MAX_LINE_LENGTH], size_t line_num);

#endif