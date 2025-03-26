#ifndef SYMBOL_H
#define SYMBOL_H

#include "../coms.h"
#include "address.h"
#include "macro.h"
#include "data.h"

typedef enum
{
	UNKNOWN_SYMBOL_TYPE,
	DATA_SYMBOL_TYPE,
	EXTERN_SYMBOL_TYPE,
	INSTRUCTION_SYMBOL_TYPE
} symbol_type;

typedef struct
{
	address symbol_address;
	char name[MAX_SYMBOL_NAME_LENGTH + 1];
	symbol_type type;
	data *value;
} symbol;

typedef struct _sn *symbol_node_ptr;
typedef struct _sn
{
	symbol_node_ptr next;
	symbol value;
} symbol_node;

/*
	checks if the symbol name given is valid and can be used.

	input:
		1. const char *name: the name to be checked.
		2. symbol_node *head: the head of the symbols list.
		3. macro_node macro_head: the head of the macros tree.
		4. size_t line: the line that the macro is on - used for error output.
    output(state):
        the state that the program is in after the function.
*/
state check_symbol_name_validity(const char *name, symbol_node *head, macro_node macro_head, size_t line);

/*
	this function creates a symbol node and puts it in a position in memory.

	output(symbol_node *):
		a pointer to the symbol node created.
*/
symbol_node *init_symbol_node();

/*
	this function frees the symbols list given to it.
	the head will be null after this function.

	input:
		1. symbol_node *head: the head of the list.
*/
void free_symbols_list(symbol_node *head);

/*
	finds the symbol in the list by name.

	input:
		1. symbol_node *head: the head of the list.
		2. const char name[MAX_SYMBOL_NAME_LENGTH + 1]: the name to be checked.
	output(symbol *):
		a pointer to the symbol in the list. NULL if not found.
*/
symbol *get_symbol_in_list(symbol_node *head, const char name[MAX_SYMBOL_NAME_LENGTH + 1]);

#endif