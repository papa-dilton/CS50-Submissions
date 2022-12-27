// Implements a dictionary's functionality
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <strings.h>

#include "dictionary.h"

#define IOBUS_SIZE 50000

typedef uint8_t BYTE;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

typedef struct IObuffer
{
    char *data;
    struct IObuffer *next;
}
IObuffer;

// Number of buckets in hash table, must be power of 26
const unsigned int N = 456976;
// Must be equal to log base 26 of N
const unsigned int TABLE_DEPTH = 4;

// Hash table
node *table[N];



// Returns true if word is in dictionary, else false

bool check(const char *word)
{
    // Get word location on hash table
    node *scanning = table[hash(word)];
    char *lower_word = malloc(sizeof(BYTE) * (LENGTH + 1));
    strcpy(lower_word, word);
    for (int i = 0; i < LENGTH; i++)
    {
        if (lower_word[i] == '\0')
        {
            break;
        }
        lower_word[i] = tolower(lower_word[i]);
    }
    while (scanning != NULL)
    {
        // If data found
        if (strcmp(scanning->word, lower_word) == 0)
        {
            free(lower_word);
            return true;
        }
        scanning = scanning->next;
    }
    free(lower_word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash word into table index
    int index = 0;
    int letter = 0;
    for (int i = TABLE_DEPTH; i > 0; i--)
    {
        if (word[letter] == '\0' || word[letter] == '\'')
        {
            break;
        }
        int debug = pow(26, i - 1);
        index += (toupper(word[letter]) - 65) * pow(26, i - 1);
        letter++;
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *dicptr = fopen(dictionary, "r");
    if (dicptr == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }


    // Retrieve dictionary from disk into memory

    IObuffer *buffer = NULL;

    bool keep_reading = true;
    while (keep_reading)
    {
        //make room for data
        char *IObus = malloc(sizeof(char) * (IOBUS_SIZE + 1));
        if (IObus == NULL)
        {
            printf("Could not create IObus\nExiting with code 1...");
            return false;
        }

        // Read data from disk 50 IOBUS_SIZE at a time
        const unsigned long read_size = fread(IObus, sizeof(char), IOBUS_SIZE, dicptr);

        // Mark end of data
        IObus[read_size] = '\0';

        // Store data in linked list, in order
        IObuffer *tmp = malloc(sizeof(IObuffer));
        tmp->data = IObus;
        tmp->next = NULL;

        // Find end of list and have it point here
        IObuffer *finder = (buffer != NULL) ? buffer->next : NULL;
        while (finder != NULL)
        {
            if (finder->next == NULL)
            {
                break;
            }
            finder = finder->next;
        }
        if (buffer == NULL)
        {
            buffer = tmp;
        }
        else if (buffer->next == NULL)
        {
            buffer->next = tmp;
        }
        else
        {
            finder->next = tmp;
        }

        // Stop reading if end of file reached
        if (read_size < IOBUS_SIZE)
        {
            keep_reading = false;
        }

    }
    fclose(dicptr);

    // Read linked list dictionary files

    int playhead = 0;
    char *word_buffer = malloc(sizeof(char) * (LENGTH + 1));
    if (word_buffer == NULL)
    {
        printf("Could not create word_buffer\nExiting with code 1...");
        while (buffer != NULL)
        {
            IObuffer *bufferPtr = buffer->next;
            free(buffer->data);
            free(buffer);
            buffer = bufferPtr;
        }
        return false;
    }
    int wordlen = 0;

    //Initialize table[] to have null pointers
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    // Loop through all data in buffer
    while (buffer->data[playhead] != '\0' || buffer->next != NULL)
    {
        // Get current char of data
        const char cur_char = buffer->data[playhead];

        // At end of file
        if (cur_char == '\0')
        {
            IObuffer *bufferPtr = buffer->next;
            free(buffer->data);
            free(buffer);
            buffer = bufferPtr;
            if (buffer == NULL)
            {
                break;
            }
            playhead = 0;
        }
        // At \n
        else if (cur_char == '\n')
        {
            word_buffer[wordlen] = '\0';
            int table_index = hash(word_buffer);
            node *tmp = malloc(sizeof(node));
            tmp->next = (table[table_index] != NULL) ? table[table_index] : NULL;
            for (int i = 0; i <= wordlen; i++)
            {
                tmp->word[i] = word_buffer[i];
            }
            table[table_index] = tmp;
            if (word_buffer == NULL)
            {
                printf("Could not create word_buffer\nExiting with code 1...");
                return false;
            }
            wordlen = 0;
            playhead++;

        }
        // At normal char
        else
        {
            word_buffer[wordlen] = cur_char;
            wordlen++;
            playhead++;
        }
    }
    // Free memory
    free(word_buffer);
    while (buffer != NULL)
    {
        IObuffer *bufferPtr = buffer->next;
        free(buffer->data);
        free(buffer);
        buffer = bufferPtr;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = 0;
    node *ptr = NULL;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            size++;
            ptr = ptr->next;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
