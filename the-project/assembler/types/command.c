#include <string.h>
#include <ctype.h>

#include "command.h"
#include "directive.h"
#include "file.h"

state parse_add(void *output, size_t line);
state parse_bne(void *output, size_t line);
state parse_clr(void *output, size_t line);
state parse_cmp(void *output, size_t line);
state parse_dec(void *output, size_t line);
state parse_inc(void *output, size_t line);
state parse_jmp(void *output, size_t line);
state parse_jsr(void *output, size_t line);
state parse_lea(void *output, size_t line);
state parse_mov(void *output, size_t line);
state parse_not(void *output, size_t line);
state parse_prn(void *output, size_t line);
state parse_red(void *output, size_t line);
state parse_rts(void *output, size_t line);
state parse_stop(void *output, size_t line);
state parse_sub(void *output, size_t line);

command commands[NUM_OF_COMMANDS] = {
    /*   name opcode funct function   */
        {"add",   2,   1, parse_add },
        {"bne",   9,   2, parse_bne },
        {"clr",   5,   1, parse_clr },
        {"cmp",   1,   0, parse_cmp },
        {"dec",   5,   4, parse_dec },
        {"inc",   5,   3, parse_inc },
        {"jmp",   9,   1, parse_jmp },
        {"jsr",   9,   3, parse_jsr },
        {"lea",   4,   0, parse_lea },
        {"mov",   0,   0, parse_mov },
        {"not",   5,   2, parse_not },
        {"prn",   13,  0, parse_prn },
        {"red",   12,  0, parse_red },
        {"rts",   14,  0, parse_rts },
        {"stop",  15,  0, parse_stop},
        {"sub",   2,   2, parse_sub }
};

command *get_command(const char *name)
{
    int mid, left = 0, right = NUM_OF_COMMANDS - 1;
    char name_letter = name[0];
    int comp_result;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (commands[mid].name[0] < name_letter)
            left = mid + 1;
        else if (commands[mid].name[0] > name_letter)
            right = mid - 1;
        else
        {
            comp_result = strcmp(commands[mid].name, name);

            if (comp_result == 0) /* Found exact match */
                return &(commands[mid]); 
            else if (comp_result < 0) /* Command name is less than target */
                left = mid + 1;  
            else /* Command name is greater than target */
                right = mid - 1; 
        }
    }

    return NULL; /* Not found */
}

boolean command_exists(const char *name)
{
    return (get_command(name) != NULL);
}

/* command helpers */
state parse_number(char *first_part, char **output, int *num, boolean first, size_t line)
{
    state status = DEFAULT_STATE;

    size_t i = 0;
    char *part, *before;

    status.line_num = line;
    part = first_part + 1; /* removing the # */

    if (strlen(first_part) == 1)
        part = strtok(NULL, WHITESPACES);

    while (status.status == OK && i < strlen(part) && part[i] != ',')
        i++;

    if (first)
    {
        if (part[i] == ',')
        {
            status = check_valid_number(part, i, status.line_num);
            if (status.status == OK)
            {
                if (sscanf(part, "%d", num) != 0)
                {
                    if (strlen(part) == (i + 1))
                    {
                        part = strtok(NULL, WHITESPACES);
                        if (part == NULL)
                            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
                        else
                            (*output) = part;
                    }
                    else
                        (*output) = part + (i + 1);
                }
                else
                    status.status = E_DATA_INTEGER_NOT_FOUND;
            }
        }
        else
        {
            before = part;
            part = strtok(NULL, WHITESPACES);
            if (part != NULL && part[0] == ',')
            {
                if (sscanf(before, "%d", num) != 0)
                {
                    if (strlen(part) == 1)
                    {
                        part = strtok(NULL, WHITESPACES);
                        if (part == NULL)
                            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
                        else
                            (*output) = part;
                    }
                    else
                        (*output) = part + 1;
                }
                else
                    status.status = E_DATA_INTEGER_NOT_FOUND;
            }
            else
                status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
        }
    }
    else
    {
        if (part[i] == ',')
            status.status = E_INSTRUCTION_EXCESS;
        else
        {
            before = part;
            part = strtok(NULL, WHITESPACES);

            if (part != NULL)
                status.status = E_INSTRUCTION_EXCESS;
            else
            {
                status = check_valid_number(before, i, status.line_num);
                if (status.status == OK)
                {
                    if (sscanf(before, "%d", num) == 0)
                        status.status = E_DATA_INTEGER_NOT_FOUND;
                }
            }
        }
    }

    return status;
}

state parse_register(char *input, char **output, instruction *dr_ptr, boolean first, size_t line)
{
    state status = DEFAULT_STATE;
    status.line_num = line;

    if (first)
    {
        if (strlen(input) < 2)
            status.status = E_INSTRUCTION_MISSING_PARAM;
        else if (!isdigit(input[1]) || (input[1] < '0' || input[2] > '7'))
            status.status = E_INSTRUCTION_REGISTER_ILLEGAL;
        else
        {
            if (strlen(input) > 2)
            {
                if (input[2] != ',')
                    status.status = E_INSTRUCTION_REGISTER_ILLEGAL;
                else
                {
                    dr_ptr->input_type = STRAIGHT_REGISTER_ADDRESS;
                    dr_ptr->input.type = INTEGER_DATA_TYPE;
                    if (sscanf(input, "r%d", &(dr_ptr->input.data.integer)) == 0)
                        status.status = E_DATA_INTEGER_NOT_FOUND;
                    else
                    {
                        if (strlen(input) == 3)
                            (*output) = strtok(NULL, WHITESPACES);
                        else
                            (*output) = input + 3; /* to go over the comma */
                    }
                }
            }
            else
            {
                dr_ptr->input_type = STRAIGHT_REGISTER_ADDRESS;
                dr_ptr->input.type = INTEGER_DATA_TYPE;
                if (sscanf(input, "r%d", &(dr_ptr->input.data.integer)) == 0)
                    status.status = E_DATA_INTEGER_NOT_FOUND;
                else
                {
                    input = strtok(NULL, WHITESPACES);
                    
                    if (input == NULL)
                        status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
                    else if (input[0] != ',')
                        status.status = E_INSTRUCTION_REGISTER_ILLEGAL;
                    else
                    {
                        if (strlen(input) == 1)
                            (*output) = strtok(NULL, WHITESPACES);
                        else
                            (*output) = input + 1; /* to go over the comma */
                    }
                }
            }
        }
    }
    else
    {
        if (strlen(input) < 2)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
        else if (!isdigit(input[1]) || (input[1] < '0' || input[2] > '7'))
            status.status = E_INSTRUCTION_REGISTER_ILLEGAL;
        else
        {
            if (strlen(input) > 2)
                status.status = E_INSTRUCTION_EXCESS;
            else
            {
                dr_ptr->output_type = STRAIGHT_REGISTER_ADDRESS;
                dr_ptr->output.type = INTEGER_DATA_TYPE;
                if (sscanf(input, "r%d", &(dr_ptr->output.data.integer)) == 0)
                    status.status = E_DATA_INTEGER_NOT_FOUND;
                else
                {
                    if ((input = strtok(NULL, WHITESPACES)) != NULL)
                        status.status = E_INSTRUCTION_EXCESS;
                    else
                        (*output) = NULL;
                }
            }
        }
    }

    return status;
}

state check_symbol_name_validity_for_parse(const char *name, size_t line)
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
    }

    return status;
}

state parse_symbol(char *input, char **output, char symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], boolean first, size_t line)
{
    int i = 0;
    char *before;
    
    state status = DEFAULT_STATE;
    status.line_num = line;

    if (first)
    {
        while (i < strlen(input) && input[i] != ',')
            i++;

        if (i == strlen(input))
        {
            before = input;
            input = strtok(NULL, WHITESPACES);

            if (input == NULL || input[0] != ',')
                status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
            else
            {
                if ((status = check_symbol_name_validity_for_parse(before, status.line_num)).status == OK)
                    strcpy(symbol_name, before);
                (*output) = input + 1;
            }
        }
        else
        {
            input[i] = '\0';
            if ((status = check_symbol_name_validity_for_parse(input, status.line_num)).status == OK)
                strcpy(symbol_name, input);
            input[i] = ',';
            (*output) = input + (i + 1);
        }
    }
    else
    {
        while (i < strlen(input) && input[i] != ',')
            i++;

        if (i == strlen(input))
        {
            if ((status = check_symbol_name_validity_for_parse(input, status.line_num)).status == OK)
                strcpy(symbol_name, input);

            input = strtok(NULL, WHITESPACES);
            if (input != NULL)
                status.status = E_INSTRUCTION_EXCESS;
        }
        else
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

/* COMMANDS */
state parse_add(void *output, size_t line)
{
    /* possible inputs: 0,1,3 */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr; 

    int num;

    status.line_num = line;
    strcpy(status.data, "add");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[0];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, TRUE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->input_type = IMMEDIATE_ADDRESS;
                dr_ptr->input.type = INTEGER_DATA_TYPE;
                dr_ptr->input.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, TRUE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, TRUE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->input_type = STRAIGHT_ADDRESS;
                    dr_ptr->input.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->input.data.symbol, symbol_name);
                }
            }
        }
    }
    else
        status.status = E_INSTRUCTION_MISSING_PARAM;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        strcpy(status.data, "add");

        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_bne(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,2 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1];
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "bne");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[1];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
        {
            status = parse_symbol(part + 1, &part, symbol_name, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = RELATIVE_ADDRESS;
                dr_ptr->output.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->output.data.symbol, symbol_name);
            }
        }
        else /* 1 - STRAIGHT_ADDRESS */
        {
            status = parse_symbol(part, &part, symbol_name, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = STRAIGHT_ADDRESS;
                dr_ptr->output.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->output.data.symbol, symbol_name);
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_clr(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "clr");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[2];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_cmp(void *output, size_t line)
{
    /* possible inputs: 0,1,3 */
    /* possible outputs: 0,1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    int num;

    status.line_num = line;
    strcpy(status.data, "cmp");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[3];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, TRUE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->input_type = IMMEDIATE_ADDRESS;
                dr_ptr->input.type = INTEGER_DATA_TYPE;
                dr_ptr->input.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, TRUE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, TRUE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->input_type = STRAIGHT_ADDRESS;
                    dr_ptr->input.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->input.data.symbol, symbol_name);
                }
            }
        }
    }
    else
        status.status = E_INSTRUCTION_MISSING_PARAM;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        strcpy(status.data, "cmp");

        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = IMMEDIATE_ADDRESS;
                dr_ptr->output.type = INTEGER_DATA_TYPE;
                dr_ptr->output.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED; 
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_dec(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "dec");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[4];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_inc(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "inc");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[5];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED; 
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_jmp(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,2 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1];
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "jmp");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[6];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
        {
            status = parse_symbol(part + 1, &part, symbol_name, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = RELATIVE_ADDRESS;
                dr_ptr->output.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->output.data.symbol, symbol_name);
            }
        }
        else /* 1 - STRAIGHT_ADDRESS */
        {
            status = parse_symbol(part, &part, symbol_name, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = STRAIGHT_ADDRESS;
                dr_ptr->output.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->output.data.symbol, symbol_name);
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_jsr(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,2 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1];
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "jsr");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[7];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
        {
            status = parse_symbol(part + 1, &part, symbol_name, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = RELATIVE_ADDRESS;
                dr_ptr->output.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->output.data.symbol, symbol_name);
            }
        }
        else /* 1 - STRAIGHT_ADDRESS */
        {
            status = parse_symbol(part, &part, symbol_name, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = STRAIGHT_ADDRESS;
                dr_ptr->output.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->output.data.symbol, symbol_name);
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_lea(void *output, size_t line)
{
    /* possible inputs: 1 */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "lea");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[8];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_INPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED;
        else /* 1 - STRAIGHT_ADDRESS */
        {
            status = parse_symbol(part, &part, symbol_name, TRUE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->input_type = STRAIGHT_ADDRESS;
                dr_ptr->input.type = SYMBOL_DATA_TYPE;
                strcpy(dr_ptr->input.data.symbol, symbol_name);
            }
        }
    }
    else
        status.status = E_INSTRUCTION_MISSING_PARAM;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        strcpy(status.data, "lea");

        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_mov(void *output, size_t line)
{
    /* possible inputs: 0,1,3 */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    int num;

    status.line_num = line;
    strcpy(status.data, "mov");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[9];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, TRUE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->input_type = IMMEDIATE_ADDRESS;
                dr_ptr->input.type = INTEGER_DATA_TYPE;
                dr_ptr->input.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, TRUE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, TRUE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->input_type = STRAIGHT_ADDRESS;
                    dr_ptr->input.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->input.data.symbol, symbol_name);
                }
            }
        }
    }
    else
        status.status = E_INSTRUCTION_MISSING_PARAM;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        strcpy(status.data, "mov");

        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_not(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "not");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[10];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_prn(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 0,1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    int num;

    status.line_num = line;
    strcpy(status.data, "prn");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[11];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = IMMEDIATE_ADDRESS;
                dr_ptr->output.type = INTEGER_DATA_TYPE;
                dr_ptr->output.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_red(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: 0,1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    int num;

    status.line_num = line;
    strcpy(status.data, "red");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[12];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, FALSE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->output_type = IMMEDIATE_ADDRESS;
                dr_ptr->output.type = INTEGER_DATA_TYPE;
                dr_ptr->output.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}

state parse_rts(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: none */
    state status = DEFAULT_STATE;

    char *part;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "rts");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[13];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;
    dr_ptr->output_type = NO_OPERAND;

    if (part != NULL)
        status.status = E_INSTRUCTION_EXCESS;
    return status;
}

state parse_stop(void *output, size_t line)
{
    /* possible inputs: none */
    /* possible outputs: none */
    state status = DEFAULT_STATE;

    char *part;
    instruction *dr_ptr;

    status.line_num = line;
    strcpy(status.data, "stop");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[14];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    dr_ptr->input_type = NO_OPERAND;
    dr_ptr->output_type = NO_OPERAND;

    if (part != NULL)
        status.status = E_INSTRUCTION_EXCESS;
    return status;
}

state parse_sub(void *output, size_t line)
{
    /* possible inputs: 0,1,3 */
    /* possible outputs: 1,3 */
    state status = DEFAULT_STATE;

    char *part, symbol_name[MAX_SYMBOL_NAME_LENGTH + 1], *before;
    instruction *dr_ptr;

    int num;

    status.line_num = line;
    strcpy(status.data, "sub");

    dr_ptr = (instruction *)output;
    dr_ptr->cmd = commands[15];
    dr_ptr->number_of_words = 1;

    /* INPUT */
    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
        {
            status = parse_number(part, &part, &num, TRUE, status.line_num);
            if (status.status == OK)
            {
                (dr_ptr->number_of_words)++;
                dr_ptr->input_type = IMMEDIATE_ADDRESS;
                dr_ptr->input.type = INTEGER_DATA_TYPE;
                dr_ptr->input.data.integer = num;
            }
        }
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, TRUE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, TRUE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->input_type = STRAIGHT_ADDRESS;
                    dr_ptr->input.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->input.data.symbol, symbol_name);
                }
            }
        }
    }
    else
        status.status = E_INSTRUCTION_MISSING_PARAM;

    /* OUTPUT */
    if (status.status == OK && (part == NULL || part[0] == '\0'))
    {
        part = strtok(NULL, WHITESPACES);
        if (part == NULL)
            status.status = E_INSTRUCTION_MISSING_SECOND_PARAMETER;
    }

    if (status.status == OK)
    {
        strcpy(status.data, "sub");

        if (part[0] == '#') /* 0 - IMMEDIATE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED;
        else if (part[0] == '&') /* 2 - RELATIVE_ADDRESS */
            status.status = E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED;
        else /* 3 - STRAIGHT_REGISTER_ADDRESS */
        {
            before = part;
            status = parse_register(part, &part, dr_ptr, FALSE, status.line_num);
            if (status.status != OK && status.status != E_INSTRUCTION_EXCESS) /* 1 - STRAIGHT_ADDRESS */
            {
                status = parse_symbol(before, &part, symbol_name, FALSE, status.line_num);
                if (status.status == OK)
                {
                    (dr_ptr->number_of_words)++;
                    dr_ptr->output_type = STRAIGHT_ADDRESS;
                    dr_ptr->output.type = SYMBOL_DATA_TYPE;
                    strcpy(dr_ptr->output.data.symbol, symbol_name);
                }
            }
        }

        if ((part = strtok(NULL, WHITESPACES)) != NULL)
            status.status = E_INSTRUCTION_EXCESS;
    }

    return status;
}