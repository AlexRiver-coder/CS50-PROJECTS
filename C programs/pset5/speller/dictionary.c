// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"
#include <strings.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Represents the number of words stored in the table
int wordcounter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Just added because could not change the unload function input for course sake
int unload_helper(node *tble);

// Number of buckets in hash table
const unsigned int N = 2400;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
// Get the hash value for the word in the text
    int checker = hash(word);
    
// Pointer to travel through the table
    node *traveler = table[checker];
    
// Return false if there is no word in the actual table
    if (traveler == NULL)
    {
        return false;
    }
    
// While loop to loop through the list if more than one word ended in the same table
    while (traveler -> next != NULL)
    {
        if (strcasecmp(traveler -> word, word) == 0)
        {
            return true;
        }
        
        else
        {
            traveler = traveler -> next;
        }
        
    }
    
// Checks if the actual table does not contain the word we are checking     
    if (strcasecmp(traveler -> word, word) == 0)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
// Integer to store the hash value of the word
    int c = 0;
    
// Loop to sum every char in the word in C
	for (int i = 0; i < strlen(word); i++)
	{
	    if (ispunct(word[i]) || strlen(word) < 2)
	    {
            continue;
	    }
        c += tolower(word[i]) -75 - i;
	}
//  Return hash value  
	return c;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
// Pointer to read the data inside the dictionary file
    char *ptr = malloc(sizeof(char)* LENGTH + 1); 
    
// Pointer to open the file    
    FILE *reader = fopen(dictionary,"r");
    
// If it fails to malloc memory for ptr or does not open the file return false   
    if (ptr == NULL || reader == NULL)
    {
        return false;
    }
    
// While loop iterate through each string in the dictionary and add to the table    
    while (fscanf(reader, "%s", ptr) != EOF)
    {
// Temporal int var to store the word hash value        
            int temp1 = hash(ptr);
            node *temp2 = malloc(sizeof(node));
            
// If it fails to malloc return false             
            if (temp2 == NULL)
            {
                return false;
            }
            
// Copies the word from the dictionary to the new node created for it            
            strcpy(temp2 -> word, ptr);
            
// If the word being added is the first in that table, then just add it to the table            
            if (table[temp1] == NULL)
            {
                table[temp1] = temp2;
                temp2 -> next = NULL;
                wordcounter++;
                continue;
            }
            
// If there is already one or more words on that table, points the new node pointer to the old first element of the list
// then point the table pointer to the new node
            if (table[temp1] != NULL)
            {
                node *trv = table[temp1];
                table[temp1] = temp2;
                temp2 -> next = trv;
                wordcounter++;
            }
    }
    
// Close the file and free the pointer used to read the file
    fclose(reader);
    free(ptr);
    
// If no problem found through the load process return true     
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        unload_helper(table[i]);
    }
    
    return true;   
}

// Recursive loop to free each word on the table
int unload_helper(node *tble)
{
    if (tble == NULL)
    {
      return 0;  
    }
    node *trvl = tble;
    
    if (trvl -> next != NULL)
    {
        unload_helper(trvl -> next);
    }
    
    if (trvl -> next == NULL)
    {
        free(trvl);
    }
    return 0;
}

