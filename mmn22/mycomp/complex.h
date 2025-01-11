#ifndef COMPLEX_H
#define COMPLEX_H

/* the complex data structure */
typedef struct {
    double real;
    double image;
} complex;

/* create and print */
complex read_comp(double a, double b);
void print_comp(const complex value);

/* operations on complex numbers */
complex add_comp(const complex a, const complex b);
complex sub_comp(const complex a, const complex b);
complex mult_comp_real(const complex image, const double real);
complex mult_comp_img(const complex comp, const double image);
complex mult_comp_comp(const complex a, const complex b);
double abs_comp(const complex value);

#endif