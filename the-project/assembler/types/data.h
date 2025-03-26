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

/*
	the function checks if the N letters of the string given to it is a valid number.

	input:
		1. const char str[MAX_LINE_LENGTH]: the string with the number in it.
		2. size_t length: the length of the number(N).
		3. size_t line: the line that the number is on - used for error output.
    output(state):
        the state of the program at the end of the function.
*/
state check_valid_number(const char str[MAX_LINE_LENGTH], size_t length, size_t line);

/*
	the functions finds the start and end index of a string in the line given and checks there is only one string in the line.
	the start of the string is the char after the quotation mark.
	the end of the string is the char before the second quotation mark.

	input:
		1. size_t *string_start: the start of the string. initial value doesn't matter.
		2. size_t *string_end: the end of the string. initial value doesn't matter.
		3. char line[MAX_LINE_LENGTH]: the line that the string is on.
		4. size_t line_num: the line that the string is on - used for error output.
    output(state):
        the state of the program at the end of the function.
*/
state get_string_indexes(size_t *string_start, size_t *string_end, char line[MAX_LINE_LENGTH], size_t line_num);

#endif