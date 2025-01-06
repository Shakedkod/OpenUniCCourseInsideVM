#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "complex.h"

void reset_number_to_zero(complex *value)
{
    if (value == NULL)
        return;
    
    value->a = 0;
    value->b = 0;
}

void read_comp(complex *value, double a, double b)
{
    if (value == NULL)
        return;
    
    value->a = a;
    value->b = b;
}

void print_comp(complex value)
{
    double a = value.a, b = value.b;
    char op = '+';

    if (b < 0)
    {
        b = -b;
        op = '-';
    }

    if (a == floor(a) && b == floor(b)) /* a && b == int*/
        printf("%d %c %di\n", (int)a, op, (int)b);
    else if (a == floor(a)) /* a == int, b != int*/
        printf("%d %c (%g)i\n", (int)a, op, b);
    else if (b == floor(b)) /* a != int, b == int*/
        printf("%g %c %di\n", a, op, (int)b);
    else /* a && b != int*/
        printf("%g %c (%g)i\n", a, op, b);
}