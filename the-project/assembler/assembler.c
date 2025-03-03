#include <stdio.h>

#include "coms.h"
#include "preprocessor.h"
#include "types/file.h"
#include "types/macro.h"

int main(int argc, char *argv[])
{
    int i = 1;
    FILE *as_file, *am_file;
    state status = DEFAULT_STATE;
    macro_node macros = DEFAULT_MACRO_NODE;

    if (argc == 1)
        print_error(E_FILE_NO_FILE_ENTERED, 0, "");

    for (; i < argc; i++)
    {
        /* reset parameters */
        zeroize_state(&status);
        zeroize_macro_tree(&macros);

        /* PREPROCESSOR */
        status.status = get_file(argv[i], &as_file, FILE_AS);
        if (status.status == OK)
        {
            status = expand_macros(as_file, &am_file, &macros);
            if (status.status == OK)
            {
                
                status.status = save_file(am_file, argv[i], FILE_AM);
                if (status.status == OK)
                {
                    /* ASSEMBLER PASS 1 */
                }
                else
                    print_error(status.status, 0, argv[i]);
            }
            else
                PRINT_ERROR(status);
        }
        else
            print_error(status.status, 0, argv[i]);
    }

    zeroize_macro_tree(&macros); /* we don't need to free the head, because it's not dynamically allocated. */
    return 0;
}