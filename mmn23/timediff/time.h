#ifndef TIME_H
#define TIME_H

typedef struct
{
    unsigned int day:5;
    unsigned int month:4;
    int year;
    unsigned int second:6;
    unsigned int minute:6;
    unsigned int hour:5;
} time;

/*
    calculates the difference of time in seconds between a and b.

    input:
        1. time a: the first time.
        2. time b: the second time.

    output(unsigned long):
        the difference in time.
*/
unsigned long diff_time(time a, time b);

/*
    prints the time given in an acceptable format to stdin.

    input:
        1. time t: the time to print.
*/
void print_time(time t);

/*
    checks if a date is possible.

    input:
        1. time t: the time to check.
    
    output(int):
        0 if the day is not possible.
        1 if the day is possible.
*/
int check_time(time t);

#endif