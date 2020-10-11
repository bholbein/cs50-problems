// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Additional Prototypes
node *createNode(char value[LENGTH + 1]);
node *insertNode(node *insert, node *hashtable_at_index);
void printList(node *head);
void freeMem(node *head);

// Number of buckets in hash table
// TODO: change to optimal value
const unsigned int N = 2000;

// Hash table
node *table[N];

// node counter
int node_counter = 0; 

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    long sum = 0;
    for (int i = 0, len = strlen(word); i <= len; i++)
    {
        sum = tolower(word[i]) + sum;
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // 1) Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Can't read from file %s", dictionary);
        return false;
    }
    // 2) Read strings from file one at a time
    char *word = malloc(LENGTH + 1);
    while (fscanf(file, "%s", word) != EOF)
    {
        node_counter++; 
        table[hash(word)] = insertNode(createNode(word), table[hash(word)]);
    }
    free(word);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return node_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i <= N; i++)
    {
        freeMem(table[i]);
    }
    return true;
}

node *createNode(char value[LENGTH + 1])
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    strcpy(n->word, value);
    n->next = NULL;
    //printf("node created \n");
    return n;
}

node *insertNode(node *insert, node *hashtable_at_index)
{
    if (hashtable_at_index == NULL)
    {
        hashtable_at_index = insert;
        //printf("New Node at Hashtable \n");
        return hashtable_at_index;
    }
    else 
    {
        insert->next = hashtable_at_index;
        //printf("New Node inserted \n");
        return insert;
    }
}

void freeMem(node *head)
{
    int nodes_deleted = 0;
    while (head != NULL)
    {
        node *tmp = head->next;
        free(head);
        head = tmp;
        nodes_deleted++;
    }
    // printf("Memory freed for %i nodes!", nodes_deleted);
}

void printList(node *head)
{
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%s ", tmp->word);
    }
    printf("\n");
}