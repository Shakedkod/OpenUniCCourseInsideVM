#include <string.h>

#include "pass_one.h"
#include "types/address.h"

state create_data(directive_node *list, directive **first, data_type type, unsigned int *ic, unsigned int *dc, char original_line[MAX_LINE_LENGTH], size_t line);
state create_symbol(symbol_node *list, const char name[MAX_SYMBOL_NAME_LENGTH + 1], data *value, symbol_type type, address value_address, size_t line);
state create_extern(symbol_node *symbol_list, external_node *external_list, macro_node macros, unsigned int *ic, size_t line);
state create_instruction(char *first_part, directive_node *list, unsigned int *ic, size_t line);
state create_entry(entry_node *list, macro_node macros, size_t line);

state assemble_symbols(
    line_node* file, symbol_node **symbols, directive_node **directives, external_node **externals, entry_node **entries, macro_node macros, 
    unsigned int *fic, unsigned int *fdc
) {
    state status = DEFAULT_STATE, end_status = DEFAULT_STATE;
    boolean is_symbol = FALSE;
    unsigned int instruction_counter = INSTRUCTION_COUNTER_START, data_counter = DATA_COUNTER_START;

    line_node *current = file;
    symbol_node *symbol_ptr = *symbols;
    directive_node *directive_ptr = *directives;
    external_node *external_ptr = *externals;
    entry_node *entry_ptr = *entries;

    directive *current_directive;

    char line_duplicate[MAX_LINE_LENGTH + 2];
    char symbol_name[MAX_SYMBOL_NAME_LENGTH + 1];
    char *part;

    (*symbols) = init_symbol_node();
    (*directives) = init_directive_node();
    (*externals) = init_external_node();
    (*entries) = init_entry_node();

    if ((*symbols) == NULL || (*directives) == NULL || (*externals) == NULL || (*entries) == NULL)
    {
        status.status = E_MEMORY_NEEDED;
        print_status(status);
        end_status.status = status.status;
    }

    while (current != NULL)
    {
        strcpy(line_duplicate, current->line);

        part = strtok(line_duplicate, WHITESPACES);
        if (part != NULL)
        {
            /*! SYMBOL */
            if (part[strlen(part) - 1] == ':') /* symbol definiton */
            {
                part[strlen(part) - 1] = '\0';

                if ((status = check_symbol_name_validity(part, *symbols, macros, status.line_num)).status == OK)
                {
                    strcpy(symbol_name, part);
                    strcpy(status.data, symbol_name);
                    part = strtok(NULL, WHITESPACES);
                    is_symbol = TRUE;
                }
                else
                {
                    print_status(status);
                    end_status.status = status.status;
                }
            }
            else if (((part = strtok(NULL, WHITESPACES)) != NULL) && (part[0] == ':')) /* error at symbol definiton */
            {
                status.status = E_SYMBOL_SPACE_BEFORE_COLON;
                print_status(status);
                end_status.status = status.status;
            }
            else /* not a symbol */
            {
                strcpy(line_duplicate, current->line);
                part = strtok(line_duplicate, WHITESPACES);
            }

            /*! DOT INSTRUCTION */
            if (status.status == OK)
            {
                if (part == NULL || part[0] == '\0')
                {
                    if (is_symbol)
                    {
                        status.status = E_SYMBOL_MISSING_DEFINITON;
                        print_status(status);
                        end_status.status = status.status;
                    }
                }
                else if (part[0] == '.')
                {
                    if (strlen(part) > 1)
                    {
                        if (strcmp(part, DATA_DATA_DIRECTIVE_NO_SPACE) == 0) /* ".data" */
                        {
                            status = create_data(*directives, &current_directive, INTEGER_DATA_TYPE, &instruction_counter, &data_counter, current->line, status.line_num);
                            if (status.status == OK)
                            {
                                if (is_symbol)
                                {
                                    status = create_symbol(
                                        *symbols, symbol_name, &(current_directive->line.value), 
                                        DATA_SYMBOL_TYPE, current_directive->directive_address, status.line_num
                                    );

                                    if (status.status != OK)
                                    {
                                        print_status(status);
                                        end_status.status = status.status;
                                    }
                                }
                            }
                            else
                            {
                                print_status(status);
                                end_status.status = status.status;
                            }
                        }
                        else if (strcmp(part, DATA_STRING_DIRECTIVE_NO_SPACE) == 0) /* ".string" */
                        {
                            status = create_data(*directives, &current_directive, STRING_DATA_TYPE, &instruction_counter, &data_counter, current->line, status.line_num);
                            if (status.status == OK)
                            {
                                if (is_symbol)
                                {
                                    status = create_symbol(
                                        *symbols, symbol_name, &(current_directive->line.value), 
                                        DATA_SYMBOL_TYPE, current_directive->directive_address, status.line_num
                                    );

                                    if (status.status != OK)
                                    {
                                        print_status(status);
                                        end_status.status = status.status;
                                    }
                                }
                            }
                            else
                            {
                                print_status(status);
                                end_status.status = status.status;
                            }
                        }
                        else if (strcmp(part, DATA_ENTRY_DIRECTIVE_NO_SPACE) == 0)  /* ".entry" */
                            status = create_entry(*entries, macros, status.line_num);
                        else if (strcmp(part, DATA_EXTERN_DIRECTIVE_NO_SPACE) == 0) /* ".extern" */
                        {
                            if (is_symbol)
                            {
                                status.status = W_EXTERN_SYMBOL_DEF;
                                print_status(status);
                            }

                            status = create_extern(*symbols, *externals, macros, &instruction_counter, status.line_num);
                            if (status.status != OK)
                            {
                                print_status(status);
                                end_status.status = status.status;
                            }
                        }
                        else
                        {
                            status.status = E_DATA_UNKNOWN_TYPE;
                            print_status(status);
                            end_status.status = status.status;
                        }
                    }
                    else
                    {
                        part = strtok(NULL, WHITESPACES);

                        if (strcmp(part, DATA_DATA_DIRECTIVE) == 0) /* ". data" */
                        {
                            status = create_data(*directives, &current_directive, INTEGER_DATA_TYPE, &instruction_counter, &data_counter, current->line, status.line_num);
                            if (status.status == OK)
                            {
                                if (is_symbol)
                                {
                                    status = create_symbol(
                                        *symbols, symbol_name, &(current_directive->line.value), 
                                        DATA_SYMBOL_TYPE, current_directive->directive_address, status.line_num
                                    );

                                    if (status.status != OK)
                                    {
                                        print_status(status);
                                        end_status.status = status.status;
                                    }
                                }
                            }
                            else
                            {
                                print_status(status);
                                end_status.status = status.status;
                            }
                        }
                        else if (strcmp(part, DATA_STRING_DIRECTIVE) == 0) /* ". string" */
                        {
                            status = create_data(*directives, &current_directive, STRING_DATA_TYPE, &instruction_counter, &data_counter, current->line, status.line_num);
                            if (status.status == OK)
                            {
                                if (is_symbol)
                                {
                                    status = create_symbol(
                                        *symbols, symbol_name, &(current_directive->line.value), 
                                        DATA_SYMBOL_TYPE, current_directive->directive_address, status.line_num
                                    );

                                    if (status.status != OK)
                                    {
                                        print_status(status);
                                        end_status.status = status.status;
                                    }
                                }
                            }
                            else
                            {
                                print_status(status);
                                end_status.status = status.status;
                            }
                        }
                        else if (strcmp(part, DATA_ENTRY_DIRECTIVE) == 0) /* ". entry" */
                            status = create_entry(*entries, macros, status.line_num);
                        else if (strcmp(part, DATA_EXTERN_DIRECTIVE) == 0) /* ". extern" */
                        {
                            status = create_extern(*symbols, *externals, macros, &instruction_counter, status.line_num);
                            if (status.status != OK)
                            {
                                print_status(status);
                                end_status.status = status.status;
                            }
                        }
                        else
                        {
                            status.status = E_DATA_UNKNOWN_TYPE;
                            print_status(status);
                            end_status.status = status.status;
                        }
                    }
                }
                else /* INSTRUCTION */
                {
                    if (is_symbol)
                    {
                        status = create_symbol(*symbols, symbol_name, NULL, INSTRUCTION_SYMBOL_TYPE, instruction_counter, status.line_num);
                        if (status.status != OK)
                        {
                            print_status(status);
                            end_status.status = status.status;
                        }
                    }

                    if (status.status == OK)
                    {
                        status = create_instruction(part, *directives, &instruction_counter, status.line_num);
                        if (status.status != OK)
                        {
                            print_status(status);
                            end_status.status = status.status;
                        }
                    }
                }
            }
        }

        is_symbol = FALSE;
        current = current->next;
        status.line_num++;
        status.status = OK;
    }

    (*fic) = instruction_counter;
    (*fdc) = data_counter;

    /* removing the first node that is temporary */
    if ((*symbols)->next != NULL)
    {
        symbol_ptr = *symbols;
        (*symbols) = (*symbols)->next;
        free(symbol_ptr);
    }
    else
        *symbols = NULL;

    if ((*directives)->next != NULL)
    {
        directive_ptr = *directives;
        (*directives) = (*directives)->next;
        free(directive_ptr);
    }
    else
        *directives = NULL;

    if ((*externals)->next != NULL)
    {
        external_ptr = *externals;
        (*externals) = (*externals)->next;
        free(external_ptr);
    }
    else
        *externals = NULL;

    if ((*entries)->next != NULL)
    {
        entry_ptr = *entries;
        (*entries) = (*entries)->next;
        free(entry_ptr);
    }
    else
        *entries = NULL;

    return end_status;
}

state create_data(directive_node *list, directive **first, data_type type, unsigned int *ic, unsigned int *dc, char original_line[MAX_LINE_LENGTH], size_t line)
{
    /*
        creates a data directive from the inputted line.

        input:
            1. directive_node *list: the directives list to be updated.
            2. directive **first: the directive created. initial value doesn't matter.
            3. data_type type: the type of the data(string or int).
            4. unsigned int *ic: the current instruction count.
            5. unsigned int *dc: the current data count.
            6. char original_line[MAX_LINE_LENGTH]: the original line.
            7. size_t line: the line that the macro is on - used for error output.
        output(state):
            the state of the program after the function.
    */
    state status = DEFAULT_STATE;
    char *part, part_before[MAX_LINE_LENGTH];

    directive_node *before, *ptr = list;

    size_t int_start = 0, int_length = 0, i = 0;
    boolean was_in_number = FALSE, created_first = FALSE;

    size_t string_start, string_end;

    status.line_num = line;

    /* setting the data to the output directive */
    while (ptr->next != NULL)
        ptr = ptr->next;
    before = ptr;

    /* getting the data */
    part = strtok(NULL, WHITESPACES);
    if (part == NULL)
        status.status = E_DATA_MISSING;
    else if (type == INTEGER_DATA_TYPE)
    {
        while ((part != NULL) && (status.status == OK))
        {
            if (was_in_number)
                status.status = E_DATA_INTEGER_SPACE_IN_THE_MIDDLE;
            else
            {
                int_start = 0;
                int_length = 0;

                for (i = 0; i < strlen(part); i++)
                {
                    if (part[i] == ',')
                    {
                        ptr->next = init_directive_node();
                        before = ptr;
                        ptr = ptr->next;

                        ptr->value.type = DATA_DIRECTIVE_TYPE;
                        ptr->value.directive_address = *ic;
                        ptr->value.line.value.type = INTEGER_DATA_TYPE;
                        
                        status = check_valid_number(part + int_start, int_length, status.line_num);
                        if (status.status == OK)
                        {
                            if (sscanf(part + int_start, "%d", &(ptr->value.line.value.data.integer)) == 0)
                            {
                                status.status = E_DATA_INTEGER_NOT_FOUND;
                                free(ptr);
                                before->next = NULL;
                            }
                            else
                            {
                                if (ptr->value.line.value.data.integer <= MAX_INTEGER)
                                {
                                    if (!created_first)
                                    {
                                        (*first) = &(ptr->value);
                                        created_first = TRUE;
                                    }

                                    (*ic)++;
                                    (*dc)++;
                                }
                                else
                                {
                                    status.status = E_DATA_INTEGER_LARGER_THEN_MAX;
                                    free(ptr);
                                    before->next = NULL;
                                }
                            }
                        }
                        else
                        {
                            free(ptr);
                            before->next = NULL;
                        }

                        int_start = i + 1;
                        int_length = 0;
                        was_in_number = FALSE;
                    }
                    else
                    {
                        int_length++;
                        was_in_number = TRUE;
                    }
                }
            }

            strcpy(part_before, part);
            part = strtok(NULL, WHITESPACES);
        }

        if (int_length > 0)
        {
            ptr->next = init_directive_node();
            ptr = ptr->next;

            ptr->value.type = DATA_DIRECTIVE_TYPE;
            ptr->value.directive_address = *ic;
            ptr->value.line.value.type = INTEGER_DATA_TYPE;

            status = check_valid_number(part_before + int_start, int_length, status.line_num);
            if (status.status == OK)
            {
                if (sscanf(part_before + int_start, "%d", &(ptr->value.line.value.data.integer)) != 1)
                {
                    status.status = E_DATA_INTEGER_NOT_FOUND;
                    free(ptr);
                    before->next = NULL;
                }
                else
                {
                    if (ptr->value.line.value.data.integer <= MAX_INTEGER)
                    {
                        if (!created_first)
                        {
                            (*first) = &(ptr->value);
                            created_first = TRUE;
                        }

                        (*ic)++;
                        (*dc)++;
                    }
                    else
                    {
                        status.status = E_DATA_INTEGER_LARGER_THEN_MAX;
                        free(ptr);
                        before->next = NULL;
                    }
                }
            }
            else
            {
                free(ptr);
                before->next = NULL;
            }
        }
    }
    else if (type == STRING_DATA_TYPE)
    {
        if (part[0] != '"')
            status.status = E_DATA_STRING_NO_START_QUOTE;
        else
        {
            status = get_string_indexes(&string_start, &string_end, original_line, status.line_num);
            if (status.status == OK)
            {
                for (i = string_start; (i < (string_end + 1)) && (ptr != NULL); i++) /* each char has it's own node */
                {
                    ptr->next = init_directive_node();
                    ptr = ptr->next;

                    if (ptr != NULL)
                    {
                        ptr->value.type = DATA_DIRECTIVE_TYPE;
                        ptr->value.directive_address = *ic;
                        ptr->value.line.value.type = STRING_DATA_TYPE;

                        ptr->value.line.value.data.string = original_line[i];

                        if (!created_first)
                        {
                            (*first) = &(ptr->value);
                            created_first = TRUE;
                        }

                        (*ic)++;
                        (*dc)++;
                    }
                    else
                        status.status = E_MEMORY_NEEDED;
                }

                if (ptr != NULL) /* adding a '\0' at the end */
                {
                    ptr->next = init_directive_node();
                    ptr = ptr->next;

                    if (ptr != NULL)
                    {
                        ptr->value.type = DATA_DIRECTIVE_TYPE;
                        ptr->value.directive_address = *ic;
                        ptr->value.line.value.type = STRING_DATA_TYPE;

                        ptr->value.line.value.data.string = '\0';

                        if (!created_first)
                        {
                            (*first) = &(ptr->value);
                            created_first = TRUE;
                        }

                        (*ic)++;
                        (*dc)++;
                    }
                    else
                        status.status = E_MEMORY_NEEDED;

                }
            }
        }
    }
    else
        status.status = E_DATA_UNKNOWN_TYPE;

    return status;
}

state create_symbol(symbol_node *list, const char name[MAX_SYMBOL_NAME_LENGTH + 1], data *value, symbol_type type, address value_address, size_t line)
{
    /*
        creates a symbol from the input given.

        input:
            1. symbol_node *list: the list of symbols to be updated.
            2. const char name[MAX_SYMBOL_NAME_LENGTH + 1]: the name of the symbol to be created.
            3. data *value: a pointer to the value of the symbol.
            4. symbol_type type: the type of the symbol(data/instruction/extern).
            5. address value_address: the address of the symbol.
            6. size_t line: the line that the macro is on - used for error output.
        output(state):
            the state of the program after the function.
    */
    symbol_node *ptr = list;

    state status = DEFAULT_STATE;
    status.line_num = line;

    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = init_symbol_node();
    ptr = ptr->next;

    if (ptr != NULL)
    {
        strcpy(ptr->value.name, name);
        ptr->value.symbol_address = value_address;
        ptr->value.type = type;
        ptr->value.value = value;
    }
    else
        status.status = E_MEMORY_NEEDED;

    return status;
}

state create_extern(symbol_node *symbol_list, external_node *external_list, macro_node macros, unsigned int *ic, size_t line)
{
    /*
        creates an external from the input given.

        input:
            1. symbol_node *list: the list of symbols to be updated.
            2. external_node *external_list: the list of externals to be updated.
            3. macro_node macros: the macros tree.
            4. unsigned int *ic: the current instruction counter.
            5. size_t line: the line that the macro is on - used for error output.
        output(state):
            the state of the program after the function.
    */
    char *part, name[MAX_SYMBOL_NAME_LENGTH + 1];

    external_node *ptr = external_list;

    state status = DEFAULT_STATE;
    status.line_num = line;

    part = strtok(NULL, WHITESPACES);
    if (part != NULL)
    {
        if ((status = check_symbol_name_validity(part, symbol_list, macros, status.line_num)).status == OK)
        {
            strcpy(name, part);
            strcpy(status.data, name);
            part = strtok(NULL, WHITESPACES);

            if (part == NULL)
            {
                status = create_symbol(symbol_list, name, NULL, EXTERN_SYMBOL_TYPE, *ic, status.line_num);
                if (status.status == OK)
                {
                    while (ptr->next != NULL)
                        ptr = ptr->next;
                    ptr->next = init_external_node();
                    ptr = ptr->next;

                    if (ptr != NULL)
                        strcpy(ptr->value.name, name);
                    else
                        status.status = E_MEMORY_NEEDED;
                }
            }
            else
                status.status = E_EXTERN_EXCESS;
        }
    }
    else
        status.status = E_EXTERN_MISSING_SYMBOL;

    return status;
}

state create_entry(entry_node *list, macro_node macros, size_t line)
{
    /*
        creates an entry from the input given.

        input:
            1. entry_node *list: the list of entries to be updated.
            2. macro_node macros: the macros tree.
            3. size_t line: the line that the macro is on - used for error output.
        output(state):
            the state of the program after the function.
    */
    state status = DEFAULT_STATE;
    entry_node *ptr = list, *before;
    char *part;

    status.line_num = line;

    while (ptr->next != NULL)
        ptr = ptr->next;

    part = strtok(NULL, WHITESPACES);
    if (part == NULL)
        status.status = E_ENTRY_MISSING_SYMBOL;
    else if ((status = check_symbol_name_validity(part, NULL, macros, line)).status == OK)
    {
        ptr->next = init_entry_node();
        before = ptr;
        ptr = ptr->next;

        if (ptr != NULL)
        {
            strcpy(ptr->value.name, part);

            if (strtok(NULL, WHITESPACES) != NULL)
            {
                status.status = E_ENTRY_EXCESS;
                free(ptr);
                before->next = NULL;
            }
        }
        else
            status.status = E_MEMORY_NEEDED;
    }

    return status;
}

state create_instruction(char *first_part, directive_node *list, unsigned int *ic, size_t line)
{
    /*
        creates an instruction from the input given.

        input:
            1. char *first_part: the first part of the instruction.
            2. directive_node *list: the directives list to be updated.
            3. unsigned int *ic: the current instruction counter.
            4. size_t line: the line that the macro is on - used for error output.
        output(state):
            the state of the program after the function.
    */
    command *cmd;
    instruction instruction;

    directive_node *ptr = list;

    state status = DEFAULT_STATE;
    status.line_num = line;
    strcpy(status.data, first_part);
    
    while (ptr->next != NULL)
        ptr = ptr->next;

    /* command name */
    cmd = get_command(first_part);
    if (cmd != NULL)
    {
        status = (*(cmd->parse))(&instruction, line);
        if (status.status == OK)
        {
            ptr->next = init_directive_node();
            ptr = ptr->next;

            if (ptr != NULL)
            {
                ptr->value.directive_address = (*ic);
                ptr->value.type = INSTRUCTION_DIRECTIVE_TYPE;
                copy_instruction(&(ptr->value.line.inst), instruction);

                (*ic) += instruction.number_of_words;
            }
            else
                status.status = E_MEMORY_NEEDED;
        }
    }
    else
        status.status = E_INSTRUCTION_COMMAND_ABSENT;

    return status;
}