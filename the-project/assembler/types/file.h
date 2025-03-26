#ifndef FILE_H
#define FILE_H
#include <stdio.h>

#include "../coms.h"

#define WHITESPACES " \t"

/* LINES */
typedef enum 
{
    READ_ERROR = -1,
    READ_EOF, /* line ends at EOF */
    READ_NEWLINE,
    READ_TOO_LONG
} read_status;

typedef struct
{
    char line[MAX_LINE_LENGTH + 2];
    read_status status;
} line_read;

/*
    the function gets the number of lines in the file given.

    input:
        1. FILE *file: the file to be counted.
    output(size_t):
        the number of lines.
*/
size_t num_of_lines(FILE *file);

/*
    the function reads the next line from the file given.

    input:
        1. FILE *file: the file to be read from.
    output(line_read):
        the line read packaged in a wrapper.
*/
line_read read_line(FILE *file);

/*
    checks if a string is just whitespaces == spaces or tabs.

    input:
        char *str: the string to be checked.
    output(boolean):
        TRUE if all whitespaces. FALSE if not.
*/
boolean is_all_whitespaces(const char *str);

/* FILES */
typedef enum {
    FILE_AS, /* assembly source code */
    FILE_AM, /* unpacked macro file */
    FILE_ENT, /* entries file */
    FILE_EXT, /* externals file */
    FILE_OB /* output machine code file (object file) */
} file_type;

/*
    gets a file from a path given.

    input:
        1. char *path: the path of the file.
        2. FILE **output: the file to be outputted. initial value doesn't matter.
        3. file_type type: the type of the file to be found.
    output(state):
        the state of the program after the function.
*/
state get_file(char *path, FILE **output, file_type type);

/*
    saves a file in the path given.

    input:
        1. FILE *file: the file to be saved.
        2. const char *output_path: the path of the file.
        3. file_type format: the format of the file.
    output(state):
        the state of the program after the function.
*/
state save_file(FILE *file, const char *output_path, file_type format);

typedef struct _ln *line_node_ptr;
typedef struct _ln
{
    line_node_ptr next;
    char line[MAX_LINE_LENGTH + 2];
} line_node;

/*
    this function creates a line node and puts it in a position in memory.

	output(line_node *):
		a pointer to the line node created.
*/
line_node *init_line_node();

/*
    this function frees the lines list given to it.
	the head will be null after this function.

	input:
		1. line_node *head: the head of the list.
*/
void free_lines_list(line_node *head);

/*
    converts a file to line nodes.

    input:
        1. FILE* input: the file to be converted.
        2. const char* input_name: the file name for error reasons.
    output(line_node *):
        the head of the nodes list.
*/
line_node *file_to_nodes(FILE* input, const char* input_name);

#endif