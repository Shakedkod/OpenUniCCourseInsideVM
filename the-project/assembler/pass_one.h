#ifndef PASS_ONE_H
#define PASS_ONE_H

#include "coms.h"

#include "types/file.h"
#include "types/macro.h"
#include "types/entry.h"
#include "types/symbol.h"
#include "types/external.h"
#include "types/directive.h"

/*
	converts the lines to directives, symbols, externals and entires.

	input:
		1. line_node *file: the lines to be converted.
		2. symbol_node **symbols: the symbols list to be created. initial value doesn't matter.
		3. directive_node **directives: the directives list to be created. initial value doesn't matter.
		4. external_node **externals: the externals list to be created. initial value doesn't matter.
		5. entry_node **entries: the entries list to be created. initial value doesn't matter.
		6. macro_node macro_tree: the macro tree from the preprocessor.
		7. unsigned int *fic: the final instruction count. initial value doesn't matter.
		8. unsigned int *fdc: the final data count. initial value doesn't matter.
	output(state):
		the state of the program after the function.
*/
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