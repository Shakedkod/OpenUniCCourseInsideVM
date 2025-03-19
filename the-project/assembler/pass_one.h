#ifndef PASS_ONE_H
#define PASS_ONE_H

#include "coms.h"

#include "types/file.h"
#include "types/macro.h"
#include "types/entry.h"
#include "types/symbol.h"
#include "types/external.h"
#include "types/directive.h"

state assemble_symbols(
	line_node *file, 
	symbol_node **symbols, 
	directive_node **directives, 
	external_node **externals,
	entry_node **entries,
	macro_node macro_tree, 
	unsigned int *fic, 
	unsigned int *fdc
);

#endif