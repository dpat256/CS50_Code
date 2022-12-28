// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// unsigned int preprocess(void) 
// {
//     FILE *dict = fopen()
// }
// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *ptr = table[hash(word)];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr -> word) == 0)
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
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        fclose(dict);
        return false;
    }
    else
    {
        char word [LENGTH + 1];
        while(fgets(word, LENGTH, dict))
        {
            word [strlen(word) - 1] = '\0';
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            int index = hash(word);
            strcpy(n -> word, word);
            n -> next = NULL;

            n -> next = table[index];
            table[index] = n;
        }
        fclose(dict);
        return true;    
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO: CHECK WHY DICT is 1 greater in size after load.
    // char *list[50000];
    unsigned int sum = 0;
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            sum++;
            ptr = ptr -> next;
        }
    }
    return sum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr -> next;
            free(ptr);
            ptr = tmp;
        }
    }
    return true;
}
