// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1430;
long word_count = -1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *check = malloc(sizeof(node));
    if (check == NULL)
    {
        printf("Could not allocate memory\n");
        return false;
    }
    
    int x = hash(word);
    
    free(check);
    
    check = table[x];
    
    while (check != NULL)
    {
        if (strcasecmp(check->word, word) == 0)
        {
            return true;
        }
        else
        {
            check = check->next;
        }
    }
    
    free(check);
    
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // I am choosing to use djb2 hash function
    // 5381 is chosen in this hash function as it is a prime number and prime
    // numbers are very good for distribution in hash tables
    unsigned long hash = 5381;
    unsigned int x;
    
    // Every time while loops back *word moves 1 array to the right thereby changing the value of x
    while ((x = *word++))
    {
        // You can use isupper to check ints as it looks at integer value
        if (isupper(x))
        {
            x = x + 32;
        }
        
        // << is bit shifting, e.g. << 0 = 0001 = 1. << 1 = 0010 = 2. << 5 = 100000 = 32.
        // It essentially tells the programme where to place the 1 in a binary sequence.
        hash = ((hash << 5) + hash) + x;
    }
    
    return hash % (N - 1);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }
    
    while (true)
    {
        node *n = calloc(1, sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate memory\n");
            return false;
        }
        
        if (feof(dict))
        {
            free(n);
            
            fclose(dict);
            
            return true;
        }
        
        word_count++;
    
        fscanf(dict, "%s", n->word);
        
        int x = hash(n->word);
        
        if (table[x] != NULL)
        {
            n->next = table[x];
            
            table[x] = n;
        }
        else
        {
            table[x] = n;
        }
    }
    
    // TODO
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current = calloc(1, sizeof(node));
    if (current == NULL)
    {
        printf("Could not allocate memory\n");
        return false;
    }
    
    free(current);
    
    node *temp = calloc(1, sizeof(node));
    if (temp == NULL)
    {
        printf("Could not allocate memory\n");
        return false;
    }
    
    free(temp);
    
    for (unsigned long x = 0; x < N; x++)
    {
        current = table[x];
        
        while (current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(current);
    
    // TODO
    return true;
}
