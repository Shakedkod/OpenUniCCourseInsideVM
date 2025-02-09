#ifndef MACRO_WORKSHOP_H
#define MACRO_WORKSHOP_H
#include <stdio.h>

#include "coms.h"
#include "types/macro.h"

code find_macros(FILE *input, macro_trie *empty);
code expand_macros(FILE *input, FILE **output, const macro_trie macros);

#endif