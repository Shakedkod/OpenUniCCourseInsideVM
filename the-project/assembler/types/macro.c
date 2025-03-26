#include <string.h>
#include <ctype.h>

#include "macro.h"

macro *get_macro_for_name(macro_node head, const char *name);

state is_name_allowed(const char *name, const macro_node head, size_t line)
{
    size_t i = 0;
    int check;
    state status = {OK, "", 0};
    status.line_num = line;

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
                        status.data[0] = name[i]; status.data[1] = '\0';
                        return status;
                    }
            }
        }
    }

    if (get_macro_for_name(head, name) != NULL)
    {
        status.status = E_MACRO_ALREADY_DEFINED;
        strcpy(status.data, name);
        return status;
    }
    
    return status;
}

macro_node *init_macro_node()
{
    /*
        this function creates an macro node and puts it in a position in memory.

	    output(macro_node *):
            a pointer to the macro node created.
    */
    int i;

    macro_node *result = malloc(sizeof(macro_node));
    if (result != NULL)
    {
        result->data = NULL;

        for (i = 0; i < NUM_OF_ALLOWED_CHARACTERS; i++)
        {
            result->children[i] = NULL;
        }
    }
    return result;
}

int get_index_of_char_in_child_array(char c)
{
    /*
        gets the index of a char in the array

        input:
            1. char c: the char.
        output(int):
            the index.
    */
    if (c == '_')
        return NUM_OF_ALLOWED_CHARACTERS - 1;
    if (toupper(c) == c)
        return NUMBER_OF_ALPHABETIC_LETTERS + (c - 'A');
    if (isdigit(c))
        return (2 * NUMBER_OF_ALPHABETIC_LETTERS) + (c - '0');
    return c - 'a';
}

void add_macro_to_tree(macro_node *head, macro *node)
{
    int i, letter = 0;
    size_t length = strlen(node->name);
    macro_node *current;

    if (length == 0)
    {
        head->data = node;
        return;
    }

    /* fining a place for the macro */
    current = head;
    for (i = 0; i < length; i++)
    {
        letter = get_index_of_char_in_child_array((node->name)[i]);

        if (current->children[letter] == NULL)
            current->children[letter] = init_macro_node();
        current = current->children[letter];
    }

    /* putting the macro inside the tree */
    current->data = node;
}

macro *get_macro_for_name(macro_node head, const char *name)
{
    int i = 0;
    size_t len = strlen(name);
    macro_node *current = &head;

    for (; i < len; i++)
    {
        if (current == NULL)
        {
            return NULL;
        }

        current = current->children[get_index_of_char_in_child_array(name[i])];
    }

    if (current == NULL || current->data == NULL)
        return NULL;
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
        free(head->data->value);
        free(head->data);
        head->data = NULL;
    }
}
