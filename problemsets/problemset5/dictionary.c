/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define HASHTABLESIZE 500

// Defines struct node
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* hashtable[HASHTABLESIZE];
int dictionarysize = 0;

int hash(const char* word)
{
    int sum = 0; 
    
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
            sum += word[i];
    }
    
    return sum % HASHTABLESIZE;  
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char string[LENGTH + 1];
    int length = strlen(word);
    
    for (int i = 0; i < length; i++)
        string[i] = tolower(word[i]);
    
    string[length] = '\0';
    int index = hash(string);
    
    if (hashtable[index] == NULL)
        return false;
        
    node* current = hashtable[index];
    
    while (current != NULL)
    {
        if (strcmp(string, current->word) == 0)
            return true;
        current = current->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    
    if (file == NULL)
    {
        printf("Can't open file.\n");
        return false;
    }
    
    while (feof(file) == 0)
    {
        dictionarysize++;
        node* new_node = malloc(sizeof(node));
        fscanf(file, "%s", new_node->word);
        int index = hash(new_node->word);
        
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
            new_node->next = NULL;
        }
        
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
    }
    
    fclose(file);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dictionarysize > 0)
        return dictionarysize - 1;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int index = 0;
    
    while (index < HASHTABLESIZE)
    {
        if (hashtable[index] == NULL)
            index++;
        else
        {
            while (hashtable[index] != NULL)
            {
                node* current = hashtable[index];
                hashtable[index] = current->next;
                free(current);
            }
            
            index++;
        }
    }
    
    return true;
}
