#ifndef MACRO_WORKSHOP_H
#define MACRO_WORKSHOP_H
#include <stdio.h>

#include "coms.h"
#include "types/macro.h"

state expand_macros(FILE *input, FILE **output, macro_node *output_macros, const char* file_output_name);

#endif