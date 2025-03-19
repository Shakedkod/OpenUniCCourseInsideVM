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

size_t num_of_lines(FILE *file);
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

char *get_extention_for_type(file_type type);

state get_file(char *path, FILE **output, file_type type);
state save_file(FILE *file, const char *output_path, file_type format);

typedef struct _ln *line_node_ptr;
typedef struct _ln
{
    line_node_ptr next;
    char line[MAX_LINE_LENGTH + 2];
} line_node;

line_node* init_line_node();
void free_lines_list(line_node* head);
line_node* file_to_nodes(FILE* input, const char* input_name);

#endif