#include <stdio.h>

#include "coms.h"

void print_error(code status, int line)
{
    switch (status)
    {
    case MISSING_ARGUMENT:
        printf("Missing command line argument.\nCorrect use: timediff <filepath>.\n");
        break;
    case TOO_MANY_ARGUMENTS:
        printf("Too many command line arguments.\nCorrect use: timediff <filepath>.\n");
        break;
    case MISSING_FILE:
        printf("The file you entered doesn't exist.\n");
        break;
    case UNREADABLE_FILE:
        printf("The file you provided isn't readble.\n");
        break;
    case LINE_TOO_LONG:
        printf("Line %d is too long. please enter a max of 1000 characters per line.\n", (line + 1));
        break;
    case MISSING_NUMBER:
        printf("In line %d there is a missing number. there should be 12 numbers per line separated by whitespaces.\n", (line + 1));
        break;
    case TOO_MANY_NUMBERS:
        printf("In line %d there are too many numbers. there should be 12 numbers per line separated by whitespaces.\n", (line + 1));
        break;
    case INCORRECT_MONTH:
        printf("There are 12 months in a year. Also, a month can't be negative.\n");
        break;
    case INCORRECT_HOUR:
        printf("There are 24 hours in a day. Also, there are no negative hours.\n");
        break;
    case INCORRECT_DAY:
        printf("There are at most 31 days at a month. Also, time doesn't go backwards, so there is no (-) day :)\n");
        break;
    case INCORRECT_MINUTE:
        printf("There are 60 minutes in an hour. Also, there is no negative minute.\n");
        break;
    case INCORRECT_SECOND:
        printf("There are 60 seconds in an minute. Also, there is no negative second.\n");
        break;
    case EXIT_EOF:
        printf("Unexpected EOF.\n");
        break;
    case EMPTY_FILE:
        printf("The file you provided is empty.\n");
        break;
    
    default:
        break;
    }
}