#include "complex.h"

int main()
{
    complex A, B, C, D, E, F;

    reset_number_to_zero(&A);
    reset_number_to_zero(&B);
    reset_number_to_zero(&C);
    reset_number_to_zero(&D);
    reset_number_to_zero(&E);
    reset_number_to_zero(&F);

    print_comp(A);
    read_comp(&A, 5.526, -53.12);
    print_comp(A);
}