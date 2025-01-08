#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "complex.h"

struct
{
    char *name;
    void (*func)(void);
} commands[] = {
    {"read_comp", read_comp},
};

#endif