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
    int a_int = round(a), b_int = round(b);
    char op = '+';

    if (b < 0)
    {
        b = -b;
        b_int = -b_int;
        op = '-';
    }

    if ((fabs(a - a_int) < 1e-5) && fabs(b) == 1) /* a == int, b == 1*/
        printf("%d %c i\n", a_int, op);
    else if (fabs(b) == 1) /* a != int, b == 1*/
        printf("%.2lf %c i\n", a, op);
    else if ((fabs(a - a_int) < 1e-5) && (fabs(b - b_int) < 1e-5)) /* a && b == int*/
        printf("%d %c %di\n", a_int, op, b_int);
    else if (fabs(a - a_int) < 1e-5) /* a == int, b != int*/
        printf("%d %c (%.2lf)i\n", a_int, op, b);
    else if (fabs(b - b_int) < 1e-5) /* a != int, b == int*/
        printf("%.2lf %c %di\n", a, op, b_int);
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
