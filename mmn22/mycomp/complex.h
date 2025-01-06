#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct 
{
    double a;
    double b;
} complex;

void reset_number_to_zero(complex *value);
void read_comp(complex *value, double a, double b);
void print_comp(complex value);

#endif