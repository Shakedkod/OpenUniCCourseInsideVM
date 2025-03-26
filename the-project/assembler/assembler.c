#include <stdio.h>

#include "coms.h"

#include "types/file.h"
#include "types/macro.h"
#include "types/entry.h"
#include "types/symbol.h"
#include "types/external.h"
#include "types/directive.h"

#include "preprocessor.h"
#include "pass_one.h"
#include "pass_two.h"

int main(int argc, char *argv[])
{
    /* an assembler. */
    int i = 1;
    unsigned int final_instruction_counter = 0, final_data_counter = 0;

    state status = DEFAULT_STATE;

    FILE *as_file, *am_file;
    line_node *file = init_line_node();

    macro_node macros = DEFAULT_MACRO_NODE;
    symbol_node *symbols = NULL;
    directive_node *directives = NULL;
    external_node *externals = NULL;
    entry_node *entries = NULL;

    if (file == NULL)
    {
        status.status = E_MEMORY_NEEDED;
        print_status(status);
        i = argc;
    }


    if (argc == 1)
    {
        status.status = E_FILE_NO_FILE_ENTERED;
        print_status(status);
    }

    for (; i < argc; i++)
    {
        /* reset parameters */
        zeroize_state(&status);
        zeroize_macro_tree(&macros);
        free_symbols_list(symbols);
        free_directives_list(directives);
        free_entries_list(entries);
        free_lines_list(file);
        file = NULL;

        printf("file %s:\n", argv[i]);
        printf("-----------------\n");

        /* PREPROCESSOR */
        status = get_file(argv[i], &as_file, FILE_AS);
        if (status.status == OK)
        {
            status = expand_macros(as_file, &am_file, &macros, argv[i]);
            if (status.status == OK)
            {
                /* ASSEMBLER PASS 1 */
                status = get_file(argv[i], &am_file, FILE_AM);
                if (status.status == OK)
                {
                    file = file_to_nodes(am_file, argv[i]);
                    if (file != NULL)
                    {
                        status = assemble_symbols(file, &symbols, &directives, &externals, &entries, macros, &final_instruction_counter, &final_data_counter);
                        if (status.status == OK)
                        {
                            /* ASSEMBLER PASS 2 */
                            status = translate_directives(directives, symbols, externals, entries);
                            if (status.status == OK)
                            {
                                /* creating files */
                                status = create_files(directives, externals, entries, final_instruction_counter, final_data_counter, argv[i]);
                                if (status.status == OK)
                                    printf("Output files created without errors.\n");
                            }
                        }
                    }
                    else
                    {
                        status.status = E_MEMORY_NEEDED;
                        print_status(status);
                    }
                }
                else
                    print_status(status);
            }
            else
                print_status(status);
        }
        else
            print_status(status);
    }

    zeroize_macro_tree(&macros);
    free_lines_list(file);
    free_symbols_list(symbols);
    free_directives_list(directives);
    free_entries_list(entries);

    return (status.status == OK) ? 0 : 1;
}