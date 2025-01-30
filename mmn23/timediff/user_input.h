#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <stdio.h>

#include "coms.h"
#include "time.h"

/*
    reads a file and returns data about it.

    input:
        1. int argc: the number of arguments given by the user.
        2. char *argv[]: the vector of arguments given by the user.
        3. FILE **output: the pointer to a file so that we can update it.
        4. int *num_of_lines: the number of lines of the file, this will be updated with the correct data.
    
    output(code):
        the status of the reading.
*/
code read_file(int argc, char *argv[], FILE **output, int *num_of_lines);

/*
    closes an open file.

    input:
        1. FILE *file: the file to be closed.
*/
void close_file(FILE *file);

/*
    gets two times from the file.

    input:
        1. FILE *file: the file to be read from.
        2. time *a: the first time to be updated with new data.
        2. time *b: the second time to be updated with new data.
    
    output(code):
        the status of the line read.
*/
code get_times(FILE *file, time *a, time *b);

/*
    prints the difference and the times in an acceptable format.

    input:
        1. time a: the first time.
        2. time b: the second time.
        3. unsigned long diff: the difference between them in seconds.
*/
void print_difference(time a, time b, unsigned long diff);

#endif