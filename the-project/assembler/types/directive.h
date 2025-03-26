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

/*
    the function copies an instruction to another one without them being connected in any way.

    input:
        1. instruction *dest: the instruction to be copied to.
        2. instruction input: the instruction to be copied.
*/
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

typedef struct
{
    char num_of_words;
    int first;
    int second;
    int third;
} translated;

/*
    the function translate a directive into a maximum of 3 words, each consisting of 24 bits.
    each word is stored in an int.

    input:
        1. directive dr: the directive to be translated.
    output(translated):
        the translated words inside a package with the number of words included.
*/
translated translate_directive(directive dr);

typedef struct _dn* directive_node_ptr;
typedef struct _dn
{
    directive_node_ptr next;
    directive value;
} directive_node;


/*
	this function creates a directive node and puts it in a position in memory.

	output(directive_node *):
		a pointer to the directive node created.
*/
directive_node* init_directive_node();

/*
    this function frees the directives list given to it.
	the head will be null after this function.

	input:
		1. directive_node *head: the head of the list.
*/
void free_directives_list(directive_node* head);

#endif