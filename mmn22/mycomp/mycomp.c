#include <string.h>

#include "user_interface.h"
#include "complex.h"
#include "coms.h"

int main()
{
    complex A = {}, B = {}, C = {}, D = {}, E = {}, F = {};
    code status = OK;
    char current_line[1024];

    while (1)
    {
        status = execute_line(current_line);
        printf("status: %s\n", code_to_str(status));
        if (status == EXIT_STOP)
            return 0;
        if (status == EXIT_EXCESS_AND_EOF)
        {
            printf("EXCESS ERROR\n");
            status = EXIT_EOF;
        }
        if (status == EXIT_EOF)
        {
            printf("EOF IS NOT EXCEPTED\n");
            return 1;
        }
    }

    return 0;
}