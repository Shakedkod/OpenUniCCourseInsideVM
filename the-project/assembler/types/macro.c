#include <string.h>
#include <ctype.h>

#include "macro.h"

macro *get_macro_for_name(macro_node head, const char *name);

state is_name_allowed(const char *name, const macro_node head, int line)
{
    int i = 0, check;
    state status = {OK, "", line};

    if (isdigit(name[0]))
    {
        status.status = E_MACRO_NAME_STARTS_WITH_DIGIT;
        return status;
    }
    
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
                    {
                        status.status = E_MACRO_NAME_ILLEGAL_CHARACTER;
                        status.data = name[i];
                    }
            }
        }
    }

    if (get_macro_for_name(head, name) != NULL)
    {
        status.status = E_MACRO_ALREADY_DEFINED;
        status.data = name;
        return status;
    }
    
    return status;
}

boolean equals(macro a, macro b)
{
    return strcmp(a.name, b.name) && strcmp(a.value, b.value);
}

macro_node *init_macro_node()
{
    int i;

    macro_node *result = malloc(sizeof(macro_node));
    result->data = NULL;

    for (i = 0; i < NUM_OF_ALLOWED_CHARACTERS; i++)
    {
        result->children[i] = NULL;
    }

    return result;
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
        head->data = malloc(sizeof(macro));
        head->data->name = node.name;
        head->data->value = node.value;
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
    current->data = malloc(sizeof(macro));
    current->data->name = node.name;
    current->data->value = node.value;
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

void delete_tree(macro_node *head)
{
    int i;

    if (head == NULL)
        return;
    
    /* Free all children first */
    for (i = 0; i < NUM_OF_ALLOWED_CHARACTERS; i++)
    {
        if (head->children[i] != NULL)
        {
            delete_tree(head->children[i]);
            head->children[i] = NULL;
        }
    }
    
    /* Free the macro data if it exists */
    if (head->data != NULL)
    {
        free(head->data->name);
        free(head->data->value);
        free(head->data);
        head->data = NULL;
    }
    
    /* Free the node itself */
    free(head);
}

void zeroize_macro_tree(macro_node *head)
{
    int i;

    /* Free children */
    for (i = 0; i < NUM_OF_ALLOWED_CHARACTERS; i++)
    {
        delete_tree(head->children[i]);
        head->children[i] = NULL;
    }

    /* Free the macro */
    if (head->data != NULL)
    {
        free(head->data->name);
        free(head->data->value);
        free(head->data);
        head->data = NULL;
    }
}
