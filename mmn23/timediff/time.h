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

unsigned long diff_time(time a, time b);
void print_time(time t);
int check_time(time t);

#endif