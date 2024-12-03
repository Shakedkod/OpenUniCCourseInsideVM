#include "list.h"

void addNode(node **head, int newKey)
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

        (*head)->key = newKey;
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
    temp->key = newKey;
    temp->next = NULL;
}

void removeNode(node **head, int removeKey)
{
    node *temp1 = *head;
    node *temp2;

    if (temp1 == NULL)
        return;
    temp2 = (node *)((*head)->next);

    if (temp1->key == removeKey)
    {
        *head = (node *)((*head)->next);
        free(temp1);
        return;
    }
    
    while (temp2 != NULL && temp2->key != removeKey)
    {
        temp1 = temp2;
        temp2 = (node *)temp2->next;
    }
    
    if (temp2 != NULL)
    {
        temp1->next = (ptr)temp2->next;
        free(temp2);
    }
    else
        printf("There is no node with the value to delete.\n");
}

void printList(node *head)
{
    node *temp = head;

    if (head == NULL)
        printf("The list is empty.\n");

    while (temp != NULL)
    {
        printf("%d", temp->key);

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