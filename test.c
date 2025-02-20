#include <stdio.h>

const double standard_rating = 10.0;
double rating;
int rate_the_ship(double, double, int, double);

int main()
{
    rate_the_ship(64.0, 45.3, 3, standard_rating);
    printf("%g\n", rating);
}

int rate_the_ship(double lwl, double sailarea, int nsails, double rating)
{
    rating *= (3.2/lwl) * sailarea * .025 * nsails;
    return 0;
}

/* MAGNIV */
void replace(int *i, int *j)
{
    (*i) ^= (*j);
    (*j) ^= (*i);
    (*i) ^= (*j); 
}