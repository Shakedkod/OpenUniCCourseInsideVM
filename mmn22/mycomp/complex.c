#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "complex.h"

complex read_comp(double a, double b)
{
    complex result = {a, b};
    return result;
}

void print_comp(const complex value)
{
    double a = value.real, b = value.image;
    int aInt = (int)a, bInt = (int)b;
    char op = '+';

    if (b < 0)
    {
        b = -b;
        op = '-';
    }

    if (a == aInt && b == bInt) /* a && b == int*/
        printf("%d %c %di\n", aInt, op, bInt);
    else if (a == aInt) /* a == int, b != int*/
        printf("%d %c (%.2lf)i\n", aInt, op, b);
    else if (b == bInt) /* a != int, b == int*/
        printf("%.2lf %c %di\n", a, op, bInt);
    else /* a && b != int*/
        printf("%.2lf %c (%.2lf)i\n", a, op, b);
}

complex add_comp(const complex a, const complex b)
{
    complex result = {
        a.real + b.real, 
        a.image + b.image
    };
    return result;
}

complex sub_comp(const complex a, const complex b)
{
    complex result = {
        a.real - b.real,
        a.image - b.image
    };
    return result;
}

complex mult_comp_real(const complex comp, const double real)
{
    complex result = {
        comp.real * real,
        comp.image * real,
    };
    return result;
}

complex mult_comp_img(const complex comp, const double image)
{
    complex result = {
        -(image * comp.image),
        image * comp.real
    };
    return result;
}

complex mult_comp_comp(const complex a, const complex b)
{
    complex result = {
        (a.real * b.real) - (a.image * b.image),
        (a.real * b.image) + (a.image * b.real)
    };
    return result;
}

double abs_comp(const complex value)
{
    return sqrt(
        pow(value.real, 2) + pow(value.image, 2)
    );
}
