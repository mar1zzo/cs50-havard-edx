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

// Number of buckets in hash table
const unsigned int N = 26; //limiting the array to the number of letters of the alphabet

// initializing only positive numbers for the hash
unsigned int hash_numbers;

// hash initiated word counter
unsigned int count_words;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // obtem o valor do array de palavras do texto
    hash_numbers = hash(word);

    // acesse a lista vinculada no índice hash_value na tabela hash
    node *pointer = table[hash_numbers];

    // percorre a tabela
    while (pointer != NULL)
    {
        // Se a palavra estiver no dicionario, retorna verdadeiro
        if (strcasecmp(word, pointer->word) == 0)
        {
            return true;
        }

        // Senao passa para o proximo ponteiro
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // https://stackoverflow.com/questions/7666509/hash-function-for-string/7666577#7666577
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    //
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *file = fopen(dictionary, "r");

    // if the file is empty, returns false
    if (file == NULL)
    {
        return false;
    }

    // creates an array to store the dictionary words
    char word[LENGTH + 1];

    // scans the file and arranges the words in a list
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory
        node *n = malloc(sizeof(node));

        // validates if it is empty, return false
        if (n == NULL)
        {
            return false;
        }

        // Put the word in the memory node
        strcpy(n->word, word);

        // get the hash value
        hash_numbers = hash(word);

        // points to the obtained hash value
        n->next = table[hash_numbers];

        // points to the new position
        table[hash_numbers] = n;

        // increments 1 in the word counter
        count_words++;
    }

    // Close file
    fclose(file);

    // Dictionnary onload, return true
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If the number of words is greater than zero it returns the quantity, otherwise it returns zero
    if (count_words > 0)
    {
        return count_words;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // allocate a new pointer to traverse the entire hash table and free memory
        node *pointer = table[i];

        // traverses the array
        while (pointer)
        {
            // allocate the pointer in a temporary array so as not to lose its origin
            node *temp = pointer;
            pointer = pointer->next;

            // Free temp
            free(temp);
        }

        // If you do not hear more words in the text or cursor is null, return true
        if (i == N - 1 && pointer == NULL)
        {
            return true;
        }
    }
    return false;
}