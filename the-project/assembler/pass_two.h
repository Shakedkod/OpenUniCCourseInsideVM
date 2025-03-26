#ifndef PASS_TWO_H
#define PASS_TWO_H

#include "coms.h"
#include "types/directive.h"
#include "types/symbol.h"
#include "types/external.h"
#include "types/entry.h"

/*
    translates the directives to simpler directives - removes every symbol and replaces it with it's address or relative address.

    input:
        1. directive_node *directives: the directives list to be updated.
        2. symbol_node *symbols: the symbols list.
        3. external_node *externals: the externals list.
        4. entry_node *entries: the entries list to be updated.
    output(state):
        the state of the program at the end of the function.
*/
state translate_directives(directive_node *directives, symbol_node *symbols, external_node *externals, entry_node *entries);

/*
    creates the output files from the directives, externals and entries.

    input:
        1. directive_node *directives: the directives list.
        2. external_node *externals: the externals list.
        3. entry_node *entries: the entries list.
        4. unsigned int ic: the instruction count.
        5. unsigned int dc: the data count.
        6. const char *file_name: the file name for the output files.
    output:
        the state of the program at the end of the function.
*/
state create_files(directive_node *directives, external_node *externals, entry_node *entries, unsigned int ic, unsigned int dc, const char *file_name);

#endif