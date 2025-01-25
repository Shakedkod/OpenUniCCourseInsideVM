#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <stdio.h>

#include "coms.h"
#include "time.h"

code read_file(int argc, char *argv[], FILE **output, int *num_of_lines);
void close_file(FILE *file);
code get_times(FILE *file, time *a, time *b);
void print_difference(time a, time b, unsigned long diff);

#endif