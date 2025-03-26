#include <stdio.h>

#include "coms.h"

#define DEFAULT_STATE_DATA '\0'
#define DEFAULT_STATE_LINE_NUM 1
#define DEFAULT_STATE_STATUS OK

void zeroize_state(state *status)
{
    status->data[0] = DEFAULT_STATE_DATA;
    status->line_num = DEFAULT_STATE_LINE_NUM;
    status->status = DEFAULT_STATE_STATUS;
}

typedef enum 
{
    PATTERN_D,
    PATTERN_S,
    PATTERN_D_S,
    PATTERN_S_D,
    PATTERN_NONE
} format_pattern;

struct code_to_message
{
    code status;
    const char *msg;
    format_pattern pattern;
} messages[] = {
    /* Unknown error in the form of the OK status */
    {OK, "Unknown error."},

    /* WARNING */
        /* reader */
    {W_LINE_TOO_LONG, "Line %d is too long.", PATTERN_D},
        /* directive */
            /* extern */
    {W_EXTERN_SYMBOL_DEF, "Extern instruction defineds a symbol, so putting it in a symbol is meaningless. This happens at line %d", PATTERN_D},

    /* ERROR */
        /* macro */
    {E_MACRO_UNNAMED, "The macro defined in line %d needs a name.", PATTERN_D},
    {E_MACRO_EXCESS, "In line %d at the call of macro '%s', there is excess characters after the name.", PATTERN_D_S},
    {E_MACRO_COMMAND_NAME, "In line %d the macro name '%s' is a command name, and thus not allowed.", PATTERN_D_S},
    {E_MACRO_DEF_EXCESS, "In line %d at the definiton of macro '%s', there is excess characters after the name.", PATTERN_D_S},
    {E_MACRO_DEF_END_EXCESS, "In line %d at the definiton of macro '%s', there is excess characters after mcroend.", PATTERN_D_S},
    {E_MACRO_ALREADY_DEFINED, "The macro %s, defined in line %d, is already defined.", PATTERN_S_D},
    {E_MACRO_NOT_CLOSED, "The macro at the end of the file wasn't closed before EOF. please add a line with 'mcroend' at the end of it.", PATTERN_NONE},
            /* macro name */
    {E_MACRO_NAME_STARTS_WITH_DIGIT, "The macro defined in line %d, has an illegal name - Macros can't start with a digit.", PATTERN_D},
    {E_MACRO_NAME_ILLEGAL_CHARACTER, "The macro defined in line %d, has an illegal name - Illegal character '%s'.", PATTERN_D_S},
    
        /* symbol */
    {E_SYMBOL_SPACE_BEFORE_COLON, "The label defined in line %d, has a whitespace before the colon(':'). That is not allowed.", PATTERN_D},
    {E_SYMBOL_ALREADY_EXISTS, "The symbol '%s', defined in line %d, has already been defined.", PATTERN_S_D},
    {E_SYMBOL_MACRO_DEFINED, "The symbol '%s', defined in line %d, has the same name as a macro, witch is not allowed.", PATTERN_S_D},
    {E_SYMBOL_COMMAND_NAME, "The symbol '%s', defined in line %d, has the same name as an assembly command, witch is not allowed.", PATTERN_S_D},
    {E_SYMBOL_MISSING_DEFINITON, "In line %d, there is a symbol defined by the name '%s', but no value or instruction is set to it.", PATTERN_D_S},
    {E_SYMBOL_NOT_FOUND, "The symbol '%s' does not exists.", PATTERN_S},
            /* symbol name */
    {E_SYMBOL_NAME_START_ILLEGAL, "The first letter within the name of the symbol '%s', defined in line %d, is not allowed.", PATTERN_S_D},
    {E_SYMBOL_NAME_ILLEGAL_CHARACTER, "One of the caracters in the name of the symbol '%s', defined in line %d, is illegal. Allowed characters are:\n\t1. Small and large English letters.\n\t2. Numbers from 0 to 9.", PATTERN_S_D},
    {E_SYMBOL_NAME_ILLEGAL_LENGTH, "A symbol name length is allowed to be 31 or less. In line %d, the symbol '%s' has a name longer then allowed.", PATTERN_D_S},
    
        /* directive */
            /* data */
    {E_DATA_MISSING, "After a .data/.string/.extern/.entry definition, there should be some data. in line %d, this data is missing.", PATTERN_D},
    {E_DATA_UNKNOWN_TYPE, "Data can be an integer or a string. In line %d, there seems to be neither.", PATTERN_D},
                /* integer */
    {E_DATA_INTEGER_PLUS_MINUS_IN_THE_MIDDLE, "An integer data type consist of an optional +/- and digits after it. In line %d, there is +/- in the middle of the number.", PATTERN_D},
    {E_DATA_INTEGER_NOT_DIGIT, "An integer data type consist of an optional +/- and digits after it. In line %d, a character that isn't a digit snuck into the number.", PATTERN_D},
    {E_DATA_INTEGER_SPACE_IN_THE_MIDDLE, "An integer data type consist of an array of numbers consisting of an optional +/- and digits after it. In line %d, there is a space in the middle of a number, witch is not allowed.", PATTERN_D},
    {E_DATA_INTEGER_NOT_FOUND, "An integer data type consist of an array of numbers consisting of an optional +/- and digits after it. In line %d, an integer wan't found.", PATTERN_D},
    {E_DATA_INTEGER_LARGER_THEN_MAX, "The integer you provided in line %d, is larger then allowed.", PATTERN_D},
                /* string */
    {E_DATA_STRING_EXTRA_STRING, "After a .string there should be only one string encased in quotation marks(\"). In line %d there seems to be an extra string.", PATTERN_D},
    {E_DATA_STRING_NOT_CLOSED, "After a .string there should be only one string encased in quotation marks(\"). In line %d there seems to be an unclosed string.", PATTERN_D},
    {E_DATA_STRING_NO_START_QUOTE, "After a .string there should be only one string encased in quotation marks(\"). In line %d the first quotation mark is missing.", PATTERN_D},
            /* extern */
    {E_EXTERN_MISSING_SYMBOL, "After a .extern instruction, there should be a symbol name that appears in another file to be used in this file. In line %d the name is missing.", PATTERN_D},
    {E_EXTERN_EXCESS, "After a .extern instruction, there should be a symbol name and nothing else. In line %d, at extern '%s', there is excess characters.", PATTERN_D_S},
            /* entry */
    {E_ENTRY_MISSING_SYMBOL, "After a .entry instruction, there should be a symbol name that appears in another file to be used in this file. In line %d the name is missing.", PATTERN_D},
    {E_ENTRY_EXCESS, "After a .entry instruction, there should be a symbol name and nothing else. In line %d, there is excess characters.", PATTERN_D},
    {E_ENTRY_SYMBOL_NOT_FOUND, "An entry was created for a symbol that doen't exists.", PATTERN_NONE},
            /* instruction */
    {E_INSTRUCTION_MISSING_PARAM, "There is a parameter missing at the instruction in line %d.", PATTERN_D},
    {E_INSTRUCTION_MISSING_SECOND_PARAMETER, "After the first parameter in an instruction line there should come a ',' and after it a second parameter. In line %d, it's missing.", PATTERN_D},
    {E_INSTRUCTION_INPUT_RELATIVE_NOT_ALLOWED, "The command '%s' does not accept a relative address in its input variable. In line %d it happens.", PATTERN_S_D},
    {E_INSTRUCTION_OUTPUT_RELATIVE_NOT_ALLOWED, "The command '%s' does not accept a relative address in its output variable. In line %d it happens.", PATTERN_S_D},
    {E_INSTRUCTION_INPUT_IMMEDIATE_NOT_ALLOWED, "The command '%s' does not accept an immediate address in its input variable. In line %d it happens.", PATTERN_S_D},
    {E_INSTRUCTION_OUTPUT_IMMEDIATE_NOT_ALLOWED, "The command '%s' does not accept an immediate address in its output variable. In line %d it happens.", PATTERN_S_D},
    {E_INSTRUCTION_INPUT_STRAIGHT_REGISTER_NOT_ALLOWED, "The command '%s' does not accept a straight register address in its input variable. In line %d it happens.", PATTERN_S_D},
    {E_INSTRUCTION_OUTPUT_STRAIGHT_REGISTER_NOT_ALLOWED, "The command '%s' does not accept a straight register address in its output variable. In line %d it happens.", PATTERN_S_D},
    {E_INSTRUCTION_EXCESS, "After a command there should be maximum of 2 vars, and in line %d there are more. each var except from the first starts with a comma.", PATTERN_D},
    {E_RELATIVE_SYMBOL_EXTERN, "The symbol '%s' is an external symbol, and thus can't be used as relative.", PATTERN_S},
                /* command */
    {E_INSTRUCTION_COMMAND_ABSENT, "The command entered in line %d is '%s', but this command dosen't exists.", PATTERN_D_S},
                /* register */
    {E_INSTRUCTION_REGISTER_ILLEGAL, "To define a register, we use 'r<number>'. this number could be 0 to 7. In line %d, the register wasn't defined correctly.", PATTERN_D},

        /* memory */
    {E_MEMORY_NEEDED, "There isn't enough memory to assemble the program you entered. reached memory capacity at line %d.", PATTERN_D},

        /* file */
    {E_FILE_INVALID_PATH, "The file path you provided(%s) is invalid: the path doesn't exists, or the file doesn't exist.", PATTERN_S},
    {E_FILE_UNRECOGNIZED_FILE_TYPE, "Unrecognized file type. the only allowed file type is *.as, enter it without the '.as'.", PATTERN_NONE},
    {E_FILE_NO_FILE_ENTERED, "You need to enter an assembly file to be assembled.\nCorrect use:\n\tassembler <file path without extention> ...", PATTERN_NONE},
    
        /* reader */
    {E_READ_ERROR, "There was a reading error at line %d.", PATTERN_D},
    {E_WRITE_ERROR, "There was a writing error at file %s.", PATTERN_S},

        /* system */
    {E_SYSTEM_UNUSABLE_TEMP_FILE, "There us an error with the temp file of %s. maybe the system is unable to read it.", PATTERN_S},
};

void print_status(state status)
{
    int i = (status.status < GET_ARRAY_LENGTH(messages)) && (status.status >= 0)
        ? status.status
        : 0;
    
    switch (messages[i].pattern)
    {
    case PATTERN_D:
        printf(messages[i].msg, status.line_num);
        break;
    case PATTERN_S:
        printf(messages[i].msg, status.data);
        break;
    case PATTERN_D_S:
        printf(messages[i].msg, status.line_num, status.data);
        break;
    case PATTERN_S_D:
        printf(messages[i].msg, status.data, status.line_num);
        break;

    default:
        printf("%s", messages[i].msg);
    }

    printf("\n");
}