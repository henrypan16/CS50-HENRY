// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
void freeWord(node *word);
// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *ptr = table[hash(word)];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr -> next;  
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fp = fopen(dictionary, "r");;
    
    int index = 0;

    //Allocate memory for first elements hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = calloc(1, sizeof(node));
    }

    node *ptr = table[index];

    if (fp == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    while (fgets(buffer, LENGTH + 2, fp) != NULL)
    {
        //If hash number changes, move ptr to the next element of array
        if (index != hash(buffer))
        {
            index = hash(buffer);
            ptr = table[index];
        }
        //Else, create a new node for new word
        else
        {
            ptr->next = calloc(1, sizeof(node));
            ptr = ptr->next;
        }
        strtok(buffer, "\n");      
        strcpy(ptr->word, buffer);
        count++;        
    }

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count > 0)
    {
        return count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        freeWord(table[i]);
    }

    return true;
}

//Recursion function to free all node of hash table
void freeWord(node *word)
{
    if (word == NULL)
    {
        return;
    }

    freeWord(word->next);
    free(word);
}