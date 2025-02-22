#include <string.h>
#include <ctype.h>

#include "macro.h"

macro *get_macro_for_name(macro_node head, const char *name);

code is_name_allowed(const char *name, const macro_node head)
{
    int i = 0, check;
    if (isdigit(name[0]))
        return E_MACRO_NAME_STARTS_WITH_DIGIT;
    
    for (i = 0; i < strlen(name); i++)
    {
        check = name[i] - '0';
        if (check > 9 || check < 0)
        {
            check = name[i] - 'A';
            if (check < 0 || check > (NUMBER_OF_ALPHABETIC_LETTERS - 1))
            {
                check = name[i] - 'a';
                if (check < 0 || check > (NUMBER_OF_ALPHABETIC_LETTERS - 1))
                    if (name[i] != '_')
                        return E_MACRO_NAME_ILLEGAL_CHARACTER;
            }
        }
    }

    if (get_macro_for_name(head, name) != NULL)
        return E_MACRO_ALREADY_DEFINED;
    
    return OK;
}

boolean equals(macro a, macro b)
{
    return strcmp(a.name, b.name) && strcmp(a.value, b.value);
}

macro_node *init_macro_node()
{
    macro_node result = {{NULL}, NULL};
    return &result;
}

int get_index_of_char_in_child_array(char c)
{
    if (c == '_')
        return NUM_OF_ALLOWED_CHARACTERS - 1;
    if (toupper(c) == c)
        return NUMBER_OF_ALPHABETIC_LETTERS + (c - 'A');
    if (isdigit(c))
        return (2 * NUMBER_OF_ALPHABETIC_LETTERS) + (c - '0');
    return c - 'a';
}

void add_macro_to_tree(macro_node *head, macro node)
{
    int i, letter = 0, length = strlen(node.name);
    macro_node *current;

    if (length == 0)
    {
        head->data = &node;
        return;
    }

    /* fining a place for the macro */
    current = head;
    for (i = 0; i < length; i++)
    {
        letter = get_index_of_char_in_child_array((node.name)[i]);

        if (current->children[letter] == NULL)
            current->children[letter] = init_macro_node();
        current = current->children[letter];
    }

    /* putting the macro inside the tree */
    current->data = &node;
}

macro *get_macro_for_name(macro_node head, const char *name)
{
    int i = 0, len = strlen(name);
    macro_node *current = &head;

    for (; i < len; i++)
    {
        if (current == NULL)
            return NULL;
        
        current = current->children[get_index_of_char_in_child_array(name[i])];
    }

    return current->data;
}
