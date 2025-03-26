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

state check_symbol_name_validity(const char *name, symbol_node *head, macro_node macro_head, size_t line);

symbol_node *init_symbol_node();
void free_symbols_list(symbol_node *head);
symbol *get_symbol_in_list(symbol_node *head, const char name[MAX_SYMBOL_NAME_LENGTH + 1]);
boolean is_symbol_in_list(symbol_node* head, const char name[MAX_SYMBOL_NAME_LENGTH + 1]);

#endif