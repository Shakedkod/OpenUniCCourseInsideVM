#include "list.h"

int main()
{
    node *head = NULL;

    addNode(&head, 5);
    addNode(&head, 7);
    addNode(&head, 10);
    
    printList(head);
    removeNode(&head, 7);
    printList(head);

    removeNode(&head, 5);
    printList(head);

    deleteList(&head);
    printList(head);

    return 0;
}