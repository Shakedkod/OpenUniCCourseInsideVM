#ifndef MACRO_WORKSHOP_H
#define MACRO_WORKSHOP_H
#include <stdio.h>

#include "coms.h"
#include "types/macro.h"

/*
    expands the macros to full code to be saved in an output file.

    input:
        1. FILE *input: the input file to be read from.
        2. FILE **output: the output file to be updated. initial value doesn't matter.
        3. macro_node *output_macros: the outupted macros tree to be updated.
        4. const char* file_output_name: the output file name.
    output(state):
        the state of the program at the end of the function.
*/
state expand_macros(FILE *input, FILE **output, macro_node *output_macros, const char* file_output_name);

#endif