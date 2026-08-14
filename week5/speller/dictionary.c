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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 475254;

// Hash table
node *table[N];

// Number of words in the dictionary
unsigned int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int bucket = hash(word);
    node *n = table[bucket];
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        else
        {
            n = n->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int length = strlen(word);
    if (length == 1)
    {
        return toupper(word[0]) - 'A';
    }
    else if (length == 2)
    {
        return 26 + ((toupper(word[0]) - 'A') * 26) + toupper(word[1]) - 'A';
    }
    else if (length == 3)
    {
        return 702 + ((toupper(word[0]) - 'A') * 676) + ((toupper(word[1]) - 'A') * 26) + toupper(word[2]) - 'A';
    }
    else
    {
        return 18278 + ((toupper(word[0]) - 'A') * 17576) + ((toupper(word[1]) - 'A') * 676) + ((toupper(word[2]) - 'A') * 26) + toupper(word[3]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    unsigned int bucket = 0;
    char words[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("The dictionary couldn't be opened\n");
        return false;
    }
    while (fscanf(file, "%s", words) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Failed to allocate memory\n");
            fclose(file);
            return false;
        }
        strcpy(n->word, words);
        bucket = hash(words);
        n->next = table[bucket];
        table[bucket] = n;
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current;
    for (unsigned int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            current = table[i];
            table[i] = table[i]->next;
            free(current);
        }
    }
    return true;
}
