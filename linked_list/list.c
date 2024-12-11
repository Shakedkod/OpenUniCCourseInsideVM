#include "list.h"

void addNode(node **head, void *(*createNewData)())
{
    node *temp = *head;

    if ((*head) == NULL)
    {
        *head = (node *)malloc(sizeof(node));
        if ((*head) == NULL)
        {
            perror("there is not enough space.");
            exit(1);
        }

        (*head)->data = createNewData();
        (*head)->next = NULL;

        return;
    }

    while (temp->next != NULL)
        temp = (node *)temp->next;

    temp->next = (ptr)malloc(sizeof(node));
    if (temp->next == NULL)
    {
        perror("there is not enough space.");
        exit(1);
    }

    temp = (node *)temp->next;
    temp->data = createNewData();
    temp->next = NULL;
}

void removeNode(node **head, void *(*getDeleteKey)(), int removeKey, void (*deleteFunction)(void **))
{
    node *temp1 = *head;
    node *temp2;

    if (temp1 == NULL)
        return;
    temp2 = (node *)((*head)->next);

    if (getDeleteKey(temp1) == removeKey)
    {
        *head = (node *)((*head)->next);
        deleteFunction(&(temp1->data));
        free(temp1);
        return;
    }
    
    while (temp2 != NULL && getDeleteKey(temp2) != removeKey)
    {
        temp1 = temp2;
        temp2 = (node *)temp2->next;
    }
    
    if (temp2 != NULL)
    {
        temp1->next = (ptr)temp2->next;
        deleteFunction(&(temp2->data));
        free(temp2);
    }
    else
        printf("There is no node with the value to delete.\n");
}

void printList(node *head, void (*printFunction)(void *))
{
    node *temp = head;

    if (head == NULL)
        printf("The list is empty.\n");

    while (temp != NULL)
    {
        printFunction(temp);

        if (temp->next != NULL)
            printf(" -> ");

        temp = (node *)temp->next;
    }
    printf("\n");
}

void deleteList(node **head)
{
    node *temp = *head;
    node *first = *head;
    while (temp != NULL)
    {
        temp = (node *)first->next;
        free(first);
        first = temp;
    }
    *head = NULL;
}