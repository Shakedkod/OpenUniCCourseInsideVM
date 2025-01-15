#include <stdio.h>

#include "coms.h"

void print_error(code error)
{
    switch (error)
    {
    case TOO_LONG:
        printf("Max line length is %d characters.\n", MAX_LINE_LENGTH);
        break;
    case ILLEGAL_COMMA:
        printf("Illegal comma.\n");
        break;
    case MISSING_COMMA:
        printf("Missing comma.\n");
        break;
    case EXTRA_COMMA:
        printf("Multiple consecutive commas.\n");
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
    case IP_LETTERS_IN_NUMBER:
        printf("Invalid parameter - letters in a number.\n");
        break;
    case IP_NOT_A_NUMBER:
        printf("Invalid parameter - not a number.\n");
        break;
    case IP_MULTIPLE_DOTS:
        printf("Invalid parameter - multiple dots in a number.\n");
        break;
    
    default:
        break;
    }
}