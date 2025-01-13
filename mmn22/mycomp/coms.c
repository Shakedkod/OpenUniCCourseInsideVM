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
    case EXIT_EXCESS_AND_EOF:
        return "EXITS_EXCESS_AND_EOF";
    case EXIT_STOP:
        return "EXIT_STOP";
    case EXIT_EOF:
        return "EXIT_EOF";
    default:
        return "ERROR READING CODE";
    }
}