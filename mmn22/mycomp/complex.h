#ifndef COMPLEX_H
#define COMPLEX_H

/* the complex data structure */
typedef struct {
    double real;
    double image;
} complex;

/* create and print */
/* 
    a functions that returns a complex number based from a real part and an imaginary part.

    input:
        double a: the real part of the complex number.
        double b: the imaginary part of the complex number.
    
    output(complex):
        the complex number.
*/
complex read_comp(double a, double b);

/*
    prints a complex number to stdout.

    input:
        complex value: the value to be printed.
*/
void print_comp(const complex value);

/* operations on complex numbers */
/*
    the function adds up to complex numbers.

    input:
        complex a: the first value to be added.
        complex b: the second value to be added.
    
    output(complex):
        the sum of the two complex numbers.
*/
complex add_comp(const complex a, const complex b);

/*
    the function removes one complex number from another => (a - b).

    input:
        complex a: the value to be removed from.
        complex b: the value to be remove.
    
    output(complex):
        the difference of the two complex numbers.
*/
complex sub_comp(const complex a, const complex b);

/*
    the function multiplies a complex number with a real number.

    input:
        complex image: the complex number to be multiplied.
        double real: the real number to be multiplied.

    output(complex):
        the multiplication of the numbers.
*/
complex mult_comp_real(const complex image, const double real);

/*
    the function multiplies a complex number with an imaginary number.

    input:
        complex comp: the complex number to be multiplied.
        double image: the imaginary number to be multiplied.

    output(complex):
        the multiplication of the numbers.
*/
complex mult_comp_img(const complex comp, const double image);

/*
    the function multiplies 2 complex numbers.

    input:
        complex a: the first number to be multiplied.
        complex b: the second number to be multiplied.

    output(complex):
        the multiplication of the numbers.
*/
complex mult_comp_comp(const complex a, const complex b);

/*
    the functions evaluates the absolute value of a complex value.

    input:
        complex value: the complex value.
    
    output(double):
        the absolute value of the complex number given.
*/
double abs_comp(const complex value);

#endif