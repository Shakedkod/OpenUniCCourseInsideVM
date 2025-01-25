#include <stdio.h>

#include "time.h"
#include "user_input.h"
 
int main (int argc, char *argv[])
{
    code status = OK;
    FILE *file;
    time a, b;
    unsigned int lines = 0, current_line = 0;
    int check = 0;

    status = read_file(argc, argv, &file, &lines);
    if (status != OK)
    {
        print_error(status, current_line);
        return 1;
    }

    while (current_line < lines)
    {
        status = get_times(file, &a, &b);
        if (status != OK)
            print_error(status, current_line);
        else
        {
            if (check_time(a) && check_time(b))
                print_difference(a, b, diff_time(a, b));
        }

        if (status == EXIT_EOF)
            return 1;

        current_line++;
    }

    close_file(file);
    return 0;
}