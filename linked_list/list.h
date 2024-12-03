#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node *ptr;
typedef struct
{
    int key;
    ptr next;
} node;

/* explain addNode*/
void addNode(node **head, int newKey);

/* explain removeNode*/
void removeNode(node **head, int removeKey);

/* explain printList*/
void printList(node *head);

/* explain deleteList*/
void deleteList(node **head);

#endif