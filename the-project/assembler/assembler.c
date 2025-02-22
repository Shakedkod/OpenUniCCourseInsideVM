#include <stdio.h>

#include "macro_workshop.h"
#include "types/file.h"

int main(int argc, char *argv[])
{
    int i = 0;
    FILE *as_file, *am_file;
    state status = DEFAULT_STATE;

    for (; i < argc; i++)
    {
        zerosize_state(&status);
        /* code */
    }
    return 0;
}