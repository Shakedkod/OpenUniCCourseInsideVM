#include <string.h>

#include "user_interface.h"
#include "complex.h"
#include "coms.h"

int main()
{
    complex A = {}, B = {}, C = {}, D = {}, E = {}, F = {};
    code status = OK;
    boolean eof = FALSE;

    /* for easier send to the execute_line() function with keeping their individuality by their name in the struct*/
    vars variables = { &A, &B, &C, &D, &E, &F };

    while (TRUE)
    {
        status = execute_line(variables, &eof);
        printf("status: %s\n", code_to_str(status));
        if (status == EXIT_STOP)
            return 0;
        if (eof)
        {
            printf("EOF IS NOT EXCEPTED\n");
            return 1;
        }
    }

    return 0;
}