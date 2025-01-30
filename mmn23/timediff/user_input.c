#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "user_input.h" 

#define LINE_MAX_LENGTH 1000
#define MAX_NUMBER_LENGTH 50
#define NUMBERS_PER_LINE 12
#define WHITESPACES " \t"

typedef enum 
{
    SECOND,
    MINUTE,
    HOUR,
    DAY,
    MONTH,
    YEAR
} time_field;

boolean is_all_whitespaces(const char *str)
{
    /* checks if a string is just whitespaces */
    int i;
    
    if (str == NULL || str[0] == '\0')
        return TRUE;

    for (i = 0; i < strlen(str); i++)
        if (!isspace(str[i]))
            return FALSE;

    return TRUE;
}

int count_lines(FILE *file) 
{
    /* counts the number of lines in a file */
    int ch, lines = 1;

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
        return 0;
    fseek(file, 0, SEEK_SET);
    
    while ((ch = fgetc(file)) != EOF)
        if (ch == '\n')
            lines++;

    fseek(file, 0, SEEK_SET);
    return lines;
}

code read_file(int argc, char *argv[], FILE **output, int *num_of_lines)
{
    FILE *file;

    if (argc < 2)
        return MISSING_ARGUMENT;
    if (argc > 2)
        return TOO_MANY_ARGUMENTS;
    
    file = fopen(argv[1], "r");
    if (file == NULL)
        return MISSING_FILE;
    
    *(num_of_lines) = count_lines(file);
    if (*(num_of_lines) == 0)
        return EMPTY_FILE;

    *(output) = file;
    return OK;
}

code check_time_validity(int time, const time_field type)
{
    /* checks if a time is valid */
    switch (type)
    {
    case MONTH:
        return ((time <= 12) && (time >= 1)) 
            ? OK 
            : INCORRECT_MONTH;
    case DAY:
        return ((time <= 31) && (time >= 1))
            ? OK
            : INCORRECT_DAY;
    case HOUR:
        return ((time < 24) && (time >= 0))
            ? OK 
            : INCORRECT_HOUR;
    case MINUTE:
        return ((time < 60) && (time >= 0))
            ? OK
            : INCORRECT_MINUTE;
    case SECOND:
        return ((time < 60) && (time >= 0))
            ? OK
            : INCORRECT_SECOND;
    default:
        return TOO_MANY_NUMBERS;
    }
}

code get_times(FILE *file, time *a, time *b)
{
    int length = 0, index = 0, num_of_outupted_args, current;
    char line[LINE_MAX_LENGTH];
    char *part;
    if (fgets(line, LINE_MAX_LENGTH, file) == NULL)
        return EXIT_EOF;
    
    length = strlen(line);
    if (length == LINE_MAX_LENGTH)
        return LINE_TOO_LONG;
    if (line[length - 1] == '\n')
        line[length - 1] == '\0';

    part = strtok(line, WHITESPACES);
    while (index < NUMBERS_PER_LINE)
    {
        if (part == NULL)
            return MISSING_NUMBER;
        
        num_of_outupted_args = sscanf(part, "%d", &current);
        if (num_of_outupted_args != 1)
            return MISSING_NUMBER;
        
        switch (index)
        {
        case 0:
            a->year = current;
            break;
        case 1:
            if (check_time_validity(current, MONTH) != OK)
                return check_time_validity(current, MONTH);
            a->month = current;
            break;
        case 2:
            if (check_time_validity(current, DAY) != OK)
                return check_time_validity(current, DAY);
            a->day = current;
            break;
        case 3:
            if (check_time_validity(current, HOUR) != OK)
                return check_time_validity(current, HOUR);
            a->hour = current;
            break;
        case 4:
            if (check_time_validity(current, MINUTE) != OK)
                return check_time_validity(current, MINUTE);
            a->minute = current;
            break;
        case 5:
            if (check_time_validity(current, SECOND) != OK)
                return check_time_validity(current, SECOND);
            a->second = current;
            break;
        case 6:
            b->year = current;
            break;
        case 7:
            if (check_time_validity(current, MONTH) != OK)
                return check_time_validity(current, MONTH);
            b->month = current;
            break;
        case 8:
            if (check_time_validity(current, DAY) != OK)
                return check_time_validity(current, DAY);
            b->day = current;
            break;
        case 9:
            if (check_time_validity(current, HOUR) != OK)
                return check_time_validity(current, HOUR);
            b->hour = current;
            break;
        case 10:
            if (check_time_validity(current, MINUTE) != OK)
                return check_time_validity(current, MINUTE);
            b->minute = current;
            break;
        case 11:
            if (check_time_validity(current, SECOND) != OK)
                return check_time_validity(current, SECOND);
            b->second = current;
            break;
        default:
            return TOO_MANY_NUMBERS;
        }

        part = strtok(NULL, WHITESPACES);
        index++;
    }

    if (part != NULL && !is_all_whitespaces(part))
        return TOO_MANY_NUMBERS;
    return OK;
}

void print_difference(time a, time b, unsigned long diff)
{
    printf("The first time is ");
    print_time(a);
    printf(".\n");

    printf("The second time is ");
    print_time(b);
    printf(".\n");

    if (diff == ULONG_MAX)
        printf("The difference between the times is too big for the program to comprehend. we know it's more then %lu seconds.\n", ULONG_MAX);
    else
        printf("The difference between them is %lu seconds.\n", diff);
}

void close_file(FILE *file)
{
    fclose(file);
}