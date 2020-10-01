// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
// TODO: change to optimal value
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // First letter, First two letters, Math using all the letters
    // Research online on existing hash function
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // 1) Open dictionary file
    // Use fopen
    // Check if return value is NULL

    // 2) Read strings from file one at a time
    // fscanf(file, "%s", word)
    // fscanf will return EOF once it reaches end of file

    // 3) Create a new node for each word
    // Use malloc
    // Remember to check if return value is NULL
    // Copy word into node using strcpy (String Copy)

    // 4) Hash word to obtain hash value (implement better hash function later)
    // Use the hash function
    // Function takes a string and returns an index

    // 5) Insert node into hash table at the location
    // Recall that hash table is an array of linked lists
    // Be sure to set pointers in the correct order
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
