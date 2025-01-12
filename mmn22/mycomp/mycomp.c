#include <string.h>

int strcmp_for_commands(const char *a, const char *b)
{
    /*
    returns:
        0 - strings are not equal
        1 - strings are equal
        2 - start of string a is equal to string b
        3 - string are equal but a has a comma at the end
    */

    int len_a = strlen(a), len_b = strlen(b), i = 0;

    if (len_a < len_b)
        return 0;

    if (len_a == len_b)
    {
        for (; i < len_a; i++)
        {
            if (a[i] != b[i])
                return 0;
        }
        return 1;
    }
    
    for (; i < len_b; i++)
    {
        if (a[i] != b[i])
            return 0;
    }

    if (a[len_b] == ',')
        return 3;
    return 2;
}

int main()
{
    /*
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
    */

    const char *a = " ";
    char b[1024];
    strcpy(b, a);
    
    char *tok = strtok(b, " \t");
    while(tok != NULL)
    {
        int return_code = strcmp_for_commands(tok, "read_comp");
        printf("%s ", tok);
        if (return_code == 1)
            printf("command: read_comp\n");
        else if (return_code == 2 || !return_code)
            printf("function name not found\n");
        else
            printf("comma error\n");
        

        tok = strtok(0, " \t");
    }

    return 0;
}