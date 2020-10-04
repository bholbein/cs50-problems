// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Additional Prototypes
node *createNode(char value[LENGTH + 1]);
node *inserNode(char value[LENGTH + 1], node *head);

// Number of buckets in hash table
// TODO: change to optimal value
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return word[0] - 97;
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
    }
    // 2) Read strings from file one at a time
    char *word = malloc(128);
    while (fscanf(file, "%s", word) != EOF)
    {
        // sanity check printf
        printf("%s \n", word);
        // 3) Create a new node for each word
        createNode(word);
        // 4) Insert node into hash table at the location, applying hash the hash function
        inserNode(word, table[hash(word)]);
    }
    fclose(file);
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
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
    return n;
}

node *inserNode(char value[LENGTH + 1], node *head)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    strcpy(n->word, value);
    n->next = head;
    return head = n;
}