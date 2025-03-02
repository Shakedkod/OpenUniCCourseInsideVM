#include <stdio.h>

#include "coms.h"
#include "macro_workshop.h"
#include "types/file.h"
#include "types/macro.h"

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *as_file, *am_file;
    state status = DEFAULT_STATE;
    macro_node macros = DEFAULT_MACRO_NODE;

    for (; i < argc; i++)
    {
        /* reset parameters */
        zeroize_state(&status);
        zeroize_macro_tree(&macros);

        /* open file */
        status.status = get_file(argv[i], &as_file, FILE_AS);
        if (status.status == OK)
        {
            status = expand_macros(as_file, &am_file, &macros);
            if (status.status == OK)
            {
                
            }
            else
                print_error(status.status, 0, argv[i]);
        }
        else
            print_error(status.status, 0, argv[i]);
    }

    zeroize_macro_tree(&macros); /* we don't need to free the head, because it's not dynamically allocated. */
    return 0;
}