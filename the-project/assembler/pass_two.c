#include <string.h>
#include <stdio.h>

#include "pass_two.h"
#include "types/file.h"

state add_entry(entry_node *list, directive value, symbol_node *symbols);
int get_number_of_words_before_output(directive dr);

state translate_directives(directive_node *directives, symbol_node *symbols, external_node *externals, entry_node *entries)
{
	state status = DEFAULT_STATE, end_status = DEFAULT_STATE;

	address_node *ad_n_ptr;
	symbol *temp_symb;
	external *temp_extrn;
	directive_node *ptr = directives;
	entry_node *entry_ptr = entries;

	/* updating entries */
	while (entry_ptr != NULL)
	{
		temp_symb = get_symbol_in_list(symbols, entry_ptr->value.name);
		if (temp_symb != NULL)
			entry_ptr->value.appearance = temp_symb->symbol_address;
		else
		{
			strcpy(status.data, entry_ptr->value.name);
			status.status = E_SYMBOL_NOT_FOUND;
			print_status(status);
			end_status.status = status.status;
		}

		entry_ptr = entry_ptr->next;
	}

	/* updating directives */
	status.status = OK;
	while (ptr != NULL)
	{
		if (ptr->value.type != DATA_DIRECTIVE_TYPE && ptr->value.type != EXTERN_DIRECTIVE_TYPE) /* .data/.string/.extern -> skip */
		{
			/* input operand */
			if (ptr->value.line.inst.input_type == STRAIGHT_ADDRESS) /* normal symbol */
			{
				temp_symb = get_symbol_in_list(symbols, ptr->value.line.inst.input.data.symbol);
				if (temp_symb != NULL)
				{
					if (temp_symb->type == EXTERN_SYMBOL_TYPE) /* external symbol */
					{
						temp_extrn = get_external_in_list(externals, temp_symb->name);
						ad_n_ptr = temp_extrn->locations;

						if (ad_n_ptr == NULL)
						{
							ad_n_ptr = init_address_node();
							temp_extrn->locations = ad_n_ptr;
						}
						else
						{
							while (ad_n_ptr->next != NULL)
								ad_n_ptr = ad_n_ptr->next;
							ad_n_ptr->next = init_address_node();
							ad_n_ptr = ad_n_ptr->next;
						}

						if (ad_n_ptr != NULL)
							ad_n_ptr->position = ptr->value.directive_address + 1; /* +1 because it's in the second word */
						else
						{
							status.status = E_MEMORY_NEEDED;
							print_status(status);
							end_status.status = status.status;
						}

						ptr->value.line.inst.input_type = EXTERN_STRAIGHT_ADDRESS;
					}
					else /* in file symbol */
					{
						ptr->value.line.inst.input.type = INTEGER_DATA_TYPE;
						ptr->value.line.inst.input.data.integer = temp_symb->symbol_address;
					}
				}
				else
				{
					strcpy(status.data, ptr->value.line.inst.input.data.symbol);
					status.status = E_SYMBOL_NOT_FOUND;
					print_status(status);
					end_status.status = status.status;
				}
			}
			else if (ptr->value.line.inst.input_type == RELATIVE_ADDRESS) /* weird symbol */
			{
				temp_symb = get_symbol_in_list(symbols, ptr->value.line.inst.input.data.symbol);
				if (temp_symb != NULL)
				{
					if (temp_symb->type == EXTERN_SYMBOL_TYPE) /* external symbol */
					{
						strcpy(status.data, ptr->value.line.inst.input.data.symbol);
						status.status = E_RELATIVE_SYMBOL_EXTERN;
						print_status(status);
						end_status.status = status.status;
					}
					else /* in file symbol */
					{
						ptr->value.line.inst.input.type = INTEGER_DATA_TYPE;
						ptr->value.line.inst.input.data.integer = (temp_symb->symbol_address - ptr->value.directive_address);
					}
				}
				else
				{
					strcpy(status.data, ptr->value.line.inst.input.data.symbol);
					status.status = E_SYMBOL_NOT_FOUND;
					print_status(status);
					end_status.status = status.status;
				}
			}

			if (status.status == OK)
			{
				/* output operand */
				if (ptr->value.line.inst.output_type == STRAIGHT_ADDRESS) /* normal symbol */
				{
					temp_symb = get_symbol_in_list(symbols, ptr->value.line.inst.output.data.symbol);
					if (temp_symb != NULL)
					{
						if (temp_symb->type == EXTERN_SYMBOL_TYPE) /* external symbol */
						{
							temp_extrn = get_external_in_list(externals, temp_symb->name);
							ad_n_ptr = temp_extrn->locations;

							if (ad_n_ptr == NULL)
							{
								ad_n_ptr = init_address_node();
								temp_extrn->locations = ad_n_ptr;
							}
							else
							{
								while (ad_n_ptr->next != NULL)
									ad_n_ptr = ad_n_ptr->next;
								ad_n_ptr->next = init_address_node();
								ad_n_ptr = ad_n_ptr->next;
							}

							if (ad_n_ptr != NULL)
								ad_n_ptr->position = ptr->value.directive_address + get_number_of_words_before_output(ptr->value);
							else
							{
								status.status = E_MEMORY_NEEDED;
								print_status(status);
								end_status.status = status.status;
							}

							ptr->value.line.inst.output_type = EXTERN_STRAIGHT_ADDRESS;
						}
						else
						{
							ptr->value.line.inst.output.type = INTEGER_DATA_TYPE;
							ptr->value.line.inst.output.data.integer = temp_symb->symbol_address;
						}
					}
					else
					{
						strcpy(status.data, ptr->value.line.inst.output.data.symbol);
						status.status = E_SYMBOL_NOT_FOUND;
						print_status(status);
						end_status.status = status.status;
					}
				}
				else if (ptr->value.line.inst.output_type == RELATIVE_ADDRESS) /* weird symbol */
				{
					temp_symb = get_symbol_in_list(symbols, ptr->value.line.inst.output.data.symbol);
					if (temp_symb == NULL)
					{
						strcpy(status.data, ptr->value.line.inst.output.data.symbol);
						status.status = E_SYMBOL_NOT_FOUND;
						print_status(status);
						end_status.status = status.status;
					}
					else if (temp_symb->type == EXTERN_SYMBOL_TYPE) /* external symbol */
					{
						strcpy(status.data, ptr->value.line.inst.output.data.symbol);
						status.status = E_RELATIVE_SYMBOL_EXTERN;
						print_status(status);
						end_status.status = status.status;
					}
					else /* in file symbol */
					{
						ptr->value.line.inst.output.type = INTEGER_DATA_TYPE;
						ptr->value.line.inst.output.data.integer = (temp_symb->symbol_address - ptr->value.directive_address);
					}
				}
			}
		}

		ptr = ptr->next;
		status.status = OK;
	}

	return end_status;
}

state create_files(directive_node *directives, external_node *externals, entry_node *entries, unsigned int ic, unsigned int dc, const char *file_name)
{
	state status = DEFAULT_STATE;

	directive_node *current_dr = directives;
	external_node *current_ext = externals;
	entry_node *current_ent = entries;
	address_node *current_address;
	translated int_dr;

	FILE *tempfile;

	/* creating the entries file */
	if (entries != NULL)
	{
		tempfile = tmpfile();
		while (current_ent != NULL)
		{
			fprintf(tempfile, "%s %07u\n", current_ent->value.name, current_ent->value.appearance);

			current_ent = current_ent->next;
		}

		/* create the file */
		status = save_file(tempfile, file_name, FILE_ENT);
		if (status.status != OK)
			print_status(status);
		fclose(tempfile);
	}

	/* creating the externals file */
	if (status.status == OK && externals != NULL)
	{
		tempfile = tmpfile();
		while (current_ext != NULL)
		{
			current_address = current_ext->value.locations;
			while (current_address != NULL)
			{
				fprintf(tempfile, "%s %07u\n", current_ext->value.name, current_address->position);

				current_address = current_address->next;
			}

			current_ext = current_ext->next;
		}

		status = save_file(tempfile, file_name, FILE_EXT);
		if (status.status != OK)
			print_status(status);
		fclose(tempfile);
	}

	/* creating the objects file */
	if (status.status == OK && directives != NULL)
	{
		tempfile = tmpfile();
		fprintf(tempfile, "%7d %-6d\n", (ic - INSTRUCTION_COUNTER_START - dc), dc);

		while (current_dr != NULL)
		{
			int_dr = translate_directive(current_dr->value);

			/* first word */
			fprintf(tempfile, "%07u %06x\n", current_dr->value.directive_address, (int_dr.first & 0xFFFFFF));

			/* second word */
			if (int_dr.num_of_words > 1)
				fprintf(tempfile, "%07u %06x\n", current_dr->value.directive_address + 1, (int_dr.second & 0xFFFFFF));

			/* third word */
			if (int_dr.num_of_words > 2)
				fprintf(tempfile, "%07u %06x\n", current_dr->value.directive_address + 2, (int_dr.third & 0xFFFFFF));

			current_dr = current_dr->next;
		}

		status = save_file(tempfile, file_name, FILE_OB);
		if (status.status != OK)
			print_status(status);
		fclose(tempfile);
	}

	return status;
}

/* translate_directives helper methods */
state add_entry(entry_node *list, directive value, symbol_node *symbols)
{
	state status = DEFAULT_STATE;
	symbol *symb;
	entry_node *ptr = list, *before;

	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = init_entry_node();
	before = ptr;
	ptr = ptr->next;

	if (ptr != NULL)
	{
		symb = get_symbol_in_list(symbols, value.line.value.data.symbol);
		if (symb != NULL)
		{
			ptr->value.appearance = symb->symbol_address;
			strcpy(ptr->value.name, symb->name);
		}
		else
			status.status = E_ENTRY_SYMBOL_NOT_FOUND;

		if (status.status != OK)
		{
			free(ptr);
			before->next = NULL;
		}
	}
	else
		status.status = E_MEMORY_NEEDED;

	return status;
}

int get_number_of_words_before_output(directive dr)
{
	int output = 1;

	switch (dr.line.inst.input_type)
	{
	case IMMEDIATE_ADDRESS:
	case STRAIGHT_ADDRESS:
	case EXTERN_STRAIGHT_ADDRESS:
	case RELATIVE_ADDRESS:
		output++;
		break;
	case STRAIGHT_REGISTER_ADDRESS:
	case NO_OPERAND:
		break;
	}

	return output;
}