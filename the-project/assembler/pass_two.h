#ifndef PASS_TWO_H
#define PASS_TWO_H

#include "coms.h"
#include "types/directive.h"
#include "types/symbol.h"
#include "types/external.h"
#include "types/entry.h"

state translate_directives(directive_node *directives, symbol_node *symbols, external_node *externals, entry_node *entries);
state create_files(directive_node *directives, external_node *externals, entry_node *entries, unsigned int ic, unsigned int dc, const char *file_name);

#endif