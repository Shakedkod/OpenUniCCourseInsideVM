#include <stdio.h>

#include "coms.h"

char *code_to_str(code value)
{
    switch (value)
    {
    case OK:
        return "OK";
    case CONTINUE:
        return "CONTINUE";
    case EMPTY:
        return "EMPTY";
    case ILLEGAL_COMMA:
        return "ILLEGAL_COMMA";
    case UNDEFINED_COMMAND:
        return "UNDEFINED_COMMAND";
    case READING_ERROR:
        return "READING_ERROR";
    case EXCESS:
        return "EXCESS";
    case MISSING_VAR:
        return "MISSING_VAR";
    case UNDEFINED_VAR:
        return "UNDEFINED_VAR";
    case EXIT_STOP:
        return "EXIT_STOP";
    default:
        return "ERROR READING CODE";
    }
}

void print_error(code error)
{
    switch (error)
    {
    case ILLEGAL_COMMA:
        printf("Illegal comma.\n");
        break;
    case UNDEFINED_COMMAND:
        printf("Undefined command name.\n");
        break;
    case EXCESS:
        printf("Extraneous text after end of command.\n");
        break;
    case MISSING_VAR:
        printf("Missing parameter.\n");
        break;
    case UNDEFINED_VAR:
        printf("Undefined complex variable.\n");
        break;
    
    default:
        break;
    }
}