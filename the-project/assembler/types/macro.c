#include <string.h>

#include "macro.h"

boolean equals(macro a, macro b)
{
    return strcmp(a.name, b.name) && strcmp(a.value, b.value);
}