#include <stdio.h>

#include "macro_workshop.h"
#include "types/file.h"

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *as_file, *am_file;
    state status;

    for (; i < argc; i++)
    {
        status = get_new_state();
        /* code */
    }
    return 0;
}