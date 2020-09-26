/** 
 * Implement a singly linked list in C 
*/

#include <stdio.h>
#include <stdlib.h>

// type definition & function prototypes

typedef struct node
{
    int number;
    struct node *next;
} node;

node *createList(int value);
node *insertNode(int value, node *head);
int deleteList(node *head); // don't forget to free memory
int findValue(int value, node *head);
void printList(node *head);

// implementation

int main(void)
{
    node *list = createList(5);
    list = insertNode(1, list);
    list = insertNode(3, list);
    printList(list);
}

node *createList(int value)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->number = value;
    n->next = NULL;
    return n;
}

node *insertNode(int value, node *head)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->number = value;
    n->next = head;
    return head = n;
}

void printList(node *head)
{
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i ", tmp->number);
    }
}