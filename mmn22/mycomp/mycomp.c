#include "complex.h"

int main()
{
    complex A = {}, B = {}, C = {}, D = {}, E = {}, F = {};

    print_comp(A);
    A = read_comp(5.526, -53.12);
    print_comp(A);

    char first[100];
    char second[100];
    scanf("%s", first);
    scanf("%s", second);
    printf("%s ", first);
    printf("%s", second);

    int stop = 0;

    while (!stop)
    {
        stop = do_command();
    }
    return 0;
}