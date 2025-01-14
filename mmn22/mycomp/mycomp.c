#include <stdio.h>

#include "user_interface.h"
#include "complex.h"
#include "coms.h"

int main()
{
    complex A = {}, B = {}, C = {}, D = {}, E = {}, F = {};
    code status = OK;
    boolean eof = FALSE, empty = FALSE;

    /* for easier send to the execute_line() function with keeping their individuality by their name in the struct*/
    vars variables = { &A, &B, &C, &D, &E, &F };

    while (TRUE)
    {
        /* instruction */
        if (!empty)
            printf("The program is ready for your next command: ");
        empty = FALSE;

        /* execution & errors */
        status = execute_line(variables, &eof);
        print_error(status);

        /* exit & empty status */
        if (status == EXIT_STOP)
            return 0;
        if (eof)
        {
            printf("EOF is not a proper way to end the program. use the 'stop' command.\n");
            return 1;
        }
        if (status == EMPTY)
            empty = TRUE;
    }

    return 0;
}