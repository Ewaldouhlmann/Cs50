// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 4096;

// Hash table
node *table[N];
int words_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    /*Getting the index in the hash table*/
    unsigned int hash_word = hash(word);

    node *p = table[hash_word];
    while (p != NULL)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    const unsigned int MULTIPLIER = 7;
    unsigned int hashValue = 0;
    int i = 0;
    /*Iterating each letter of the word, multiplying the current hashValue with multiplier, then
    adding the corresponding value to self word*/
    while (word[i] != '\0')
    {
        /*Checking if the character is not a letter, assign a value of 26 if isn't*/
        if (toupper(word[i]) == tolower(word[i]))
        {
            hashValue = hashValue * MULTIPLIER + 26;
        }
        else
        {
            /*Calculate its value based on its position in the alphabet*/
            hashValue = hashValue * MULTIPLIER + (toupper(word[i]) - 'A' + 1);
        }
        i++;
    }
    /*Returning the module to fit within the hash table size*/
    return hashValue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Error to open dictionary file");
        fclose(dict);
        return false;
    }

    // Reading words in the file
    char *buffer = malloc(46);
    if (buffer == NULL)
    {
        printf("Memory allocation failed");
        return false;
    }

    while (fscanf(dict, "%s", buffer) != EOF)
    {
        // Creating a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory allocation failed");
            fclose(dict);
            free(buffer);
            return false;
        }

        /*Copy the word into the node*/
        strcpy(n->word, buffer);

        /*Insert the node in the hash*/
        unsigned int hash_word = hash(n->word);
        /*Verifying if is the first node in current index*/
        if (table[hash_word] == NULL)
        {
            n->next = NULL;
            table[hash_word] = n;
        }
        else
        {
            n->next = table[hash_word];
            table[hash_word] = n;
        }
        words_counter++;
    }
    // close the dictionary file and free alocated memory
    fclose(dict);
    free(buffer);

    /*Dictionary loaded successfully*/
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    /*Returning the global counter*/
    return words_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    /*Walking through the root array, and for each idx freeing up memory*/
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p != NULL)
        {
            /*Creating a temporary variable to free the current node, and
            setting the current pointer to the next pointer*/
            node *temp = p;
            p = p->next;
            free(temp);
        }
        /*Setting all idx in the root array to null*/
        table[i] = NULL;
    }
    words_counter = 0;
    return true;
}
