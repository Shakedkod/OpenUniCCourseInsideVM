#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include "symbol.h"
#include "address.h"
#include "command.h"

typedef enum
{
    DATA_DIRECTIVE_TYPE,
    EXTERN_DIRECTIVE_TYPE,
    ENTRY_DIRECTIVE_TYPE,
    INSTRUCTION_DIRECTIVE_TYPE
} directive_type;

typedef enum
{
    IMMEDIATE_ADDRESS,
    STRAIGHT_ADDRESS,
    EXTERN_STRAIGHT_ADDRESS,
    RELATIVE_ADDRESS,
    STRAIGHT_REGISTER_ADDRESS,
    NO_OPERAND
} operand_address_type;

typedef struct
{
    unsigned int number_of_words;
    command cmd;
    operand_address_type input_type;
    data input;
    operand_address_type output_type;
    data output;
} instruction;

void copy_instruction(instruction *dest, instruction input);

typedef struct
{
    address directive_address;
    directive_type type;
    union
    {
        instruction inst;
        data value;
    } line;
	
} directive;

void copy_directive(directive *dest, directive input);

typedef struct
{
    char num_of_words;
    int first;
    int second;
    int third;
} translated;

translated translate_directive(directive dr);

typedef struct _dn* directive_node_ptr;
typedef struct _dn
{
    directive_node_ptr next;
    directive value;
} directive_node;

directive_node* init_directive_node();
void free_directives_list(directive_node* head);

#endif