#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node *ptr;
typedef struct
{
    void *data;
    ptr next;
} node;

/* explain addNode*/
void addNode(node **head, void *(*createNewData)());

/* explain removeNode*/
void removeNode(node **head, void *(*getDeleteId)(), int removeKey, void (*deleteFunction)(void **));

/* explain printList*/
void printList(node *head, void (*printFunction)(void *));

/* explain deleteList*/
void deleteList(node **head);

#endif