#include <stdlib.h>

#include "directive.h"

#define INSTRUCTION_START_DATA 3
#define INSTRUCTION_A_MOVE 2
#define INSTRUCTION_R_MOVE 1
#define INSTRUCTION_E_MOVE 0
#define INSTRUCTION_FIRST_WORD_A (1 << INSTRUCTION_A_MOVE)
#define INSTRUCTION_FIRST_WORD_R_E (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE)

void copy_instruction(instruction *dest, instruction input)
{
    dest->number_of_words = input.number_of_words;
    dest->cmd = input.cmd;
    dest->input = input.input;
    dest->input_type = input.input_type;
    dest->output = input.output;
    dest->output_type = input.output_type;
}

void copy_directive(directive *dest, directive input)
{
    dest->directive_address = input.directive_address;
    dest->type = input.type;

    /* instruction directive */
    if (dest->type == INSTRUCTION_DIRECTIVE_TYPE)
        copy_instruction(&(dest->line.inst), input.line.inst);
    else
        copy_data(&(dest->line.value), input.line.value);
}

int translate_arg_type(operand_address_type type)
{
    switch (type)
    {
    case IMMEDIATE_ADDRESS:
        return 0;

    case RELATIVE_ADDRESS:
        return 2;

    case STRAIGHT_REGISTER_ADDRESS:
        return 3;

    case STRAIGHT_ADDRESS:
    case EXTERN_STRAIGHT_ADDRESS:
    default:
        return 1;
    }
}

translated translate_directive(directive dr)
{
    command cmd;
    int input_type, output_type, input_register, output_register, value;
    translated output = {1, 0, 0, 0};

    /* data directive */
    if (dr.type == DATA_DIRECTIVE_TYPE)
    {
        output.num_of_words = 1;
        if (dr.line.value.type == STRING_DATA_TYPE)
            output.first = dr.line.value.data.string;
        else
            output.first = dr.line.value.data.integer;
    }

    /* instruction directive */
    if (dr.type == INSTRUCTION_DIRECTIVE_TYPE)
    {
        output.num_of_words = dr.line.inst.number_of_words;

        /* first command word */
        cmd = dr.line.inst.cmd;
        input_type = translate_arg_type(dr.line.inst.input_type);
        input_register = (dr.line.inst.input_type == STRAIGHT_REGISTER_ADDRESS) 
            ? dr.line.inst.input.data.integer 
            : 0;
        output_type = translate_arg_type(dr.line.inst.output_type);
        output_register = (dr.line.inst.output_type == STRAIGHT_REGISTER_ADDRESS)
            ? dr.line.inst.output.data.integer
            : 0;

        output.first = (cmd.opcode << 18) 
            | (input_type << 16) | (input_register << 13) 
            | (output_type << 11) | (output_register << 8) 
            | (cmd.funct << 3)
            | INSTRUCTION_FIRST_WORD_A | INSTRUCTION_FIRST_WORD_R_E;
        
        if (input_type != STRAIGHT_REGISTER_ADDRESS) /* the input word */
        {
            value = dr.line.inst.input.data.integer;

            switch (input_type)
            {
            case IMMEDIATE_ADDRESS:
            {
                output.second = (value << INSTRUCTION_START_DATA) 
                    | (1 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                break;
            }
            case STRAIGHT_ADDRESS:
            {
                output.second = (value << INSTRUCTION_START_DATA)
                    | (0 << INSTRUCTION_A_MOVE) | (1 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                break;
            }
            case EXTERN_STRAIGHT_ADDRESS:
            {
                output.second = (value << INSTRUCTION_START_DATA)
                    | (0 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (1 << INSTRUCTION_E_MOVE);
                break;
            }
            case RELATIVE_ADDRESS:
            {
                output.second = (value << INSTRUCTION_START_DATA)
                    | (1 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                break;
            }
            default:
                break;
            }
        }

        if (output_type != STRAIGHT_REGISTER_ADDRESS) /* the output word */
        {
            value = dr.line.inst.output.data.integer;

            if (output.num_of_words == 3) /* there was an input word */
            {
                switch (input_type)
                {
                case IMMEDIATE_ADDRESS:
                {
                    output.third = (value << INSTRUCTION_START_DATA)
                        | (1 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                    break;
                }
                case STRAIGHT_ADDRESS:
                {
                    output.third = (value << INSTRUCTION_START_DATA)
                        | (0 << INSTRUCTION_A_MOVE) | (1 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                    break;
                }
                case EXTERN_STRAIGHT_ADDRESS:
                {
                    output.third = (value << INSTRUCTION_START_DATA)
                        | (0 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (1 << INSTRUCTION_E_MOVE);
                    break;
                }
                case RELATIVE_ADDRESS:
                {
                    output.third = (value << INSTRUCTION_START_DATA)
                        | (1 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                    break;
                }
                default:
                    break;
                }
            }
            else /* there wasn't an input word */
            {
                switch (input_type)
                {
                case IMMEDIATE_ADDRESS:
                {
                    output.second = (value << INSTRUCTION_START_DATA)
                        | (1 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                    break;
                }
                case STRAIGHT_ADDRESS:
                {
                    output.second = (value << INSTRUCTION_START_DATA)
                        | (0 << INSTRUCTION_A_MOVE) | (1 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                    break;
                }
                case EXTERN_STRAIGHT_ADDRESS:
                {
                    output.second = (value << INSTRUCTION_START_DATA)
                        | (0 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (1 << INSTRUCTION_E_MOVE);
                    break;
                }
                case RELATIVE_ADDRESS:
                {
                    output.second = (value << INSTRUCTION_START_DATA)
                        | (1 << INSTRUCTION_A_MOVE) | (0 << INSTRUCTION_R_MOVE) | (0 << INSTRUCTION_E_MOVE);
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

    return output;
}

directive_node* init_directive_node()
{
    directive_node* output = malloc(sizeof(directive_node));
    if (output != NULL)
        output->next = NULL;

    return output;
}

void free_directives_list(directive_node* head)
{
    directive_node *current = head;
    directive_node *temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}

void DEBUG_print_directive(directive dr)
{
    printf("Address: %u, Type: ", dr.directive_address);

    switch (dr.type)
    {
    case DATA_DIRECTIVE_TYPE:
        printf("Data, ");
        break;
    case EXTERN_DIRECTIVE_TYPE:
        printf("Extern, ");
        break;
    case ENTRY_DIRECTIVE_TYPE:
        printf("Entry, ");
        break;
    case INSTRUCTION_DIRECTIVE_TYPE:
        printf("Instruction, %s", dr.line.inst.cmd.name);
        break;
    default:
        break;
    }
}

void DEBUG_print_directives_list(directive_node *head)
{
    if (head != NULL)
    {
        if (head->next != NULL)
        {
            DEBUG_print_directive(head->value);
            printf("\n");
            DEBUG_print_directives_list(head->next);
        }
        else
        {
            DEBUG_print_directive(head->value);
            printf("\n");
        }
    }
}