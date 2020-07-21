#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// substitution || pset2 || cs50  //

int main(int argc, string argv[])
{
    
// confirms if the key inserted is more than 0 chars //
    
    if (argv[1] == 0)
    {
        printf("Usage: ./substitution key.\n");
        
        return 1;
    }
    
// variables to represent the key inserted and the key lengh //
    
    string key = argv[1];
    
    long key_lengh = strlen(key);
    
// checks if the key lengh is 26, if it's less or more than 26 chars the program ends //
    
    if (key_lengh != 26)
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }
    
// some usefull variables //
    
    int check_key = 0;
    int rpt_char = 0;
    int char_c = 0; 
    string alpha_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alpha_l = "abcdefghijklmnopqrstuvwxyz";
    
// checks if the key's characters are only letters //
    
    for (int i = 0; i != key_lengh; i++)
    {
        if (islower(key[i]))
        {
            check_key++;
        }
        
        else if (isupper(key[i]))
        {
            check_key++;
        }
    }
    
// checks if there are repeated characters in the key //
    
    for (int n = 0; n != key_lengh; n++)
    {
        for (int c = 0; c != key_lengh ; c++)
        {
            if (key[n] == key[c])
            {
                rpt_char++; 
            }
        }
    }
    
    rpt_char -= 26;
    
// if there is any char in the key that are not letters, or if repeated chars are present,
// return 1 and stop program, so this line validates the key it's self.
    
    if (check_key != key_lengh || rpt_char != 0)
    
    {
        printf("Usage: ./substitution key.\n");
        
        return 1;
    }
    
    printf("plain text: ");
    
    string text = get_string("");
    string cyph = text;
    
// cipher process //
    
    for (int z = 0; z < strlen(text); z++)
    {
        
// checks if the current character is an uppercase or not
        
        if (isupper(text[z]) != '\0')
        {
            
//checks which letter in the alphabet the current text char is
            
            for (int x = 0; x < 26; x++)
            {
                if (alpha_u[x] == (text[z]))
                {
                    
//sets the key to upper in order to keep the format and sums on the cipher variable.
                    
                    cyph[z] = toupper(key[x]);
                    break;
                }
            }
        }
        
//checks if the current character is an lowercase
        
        else if (islower(text[z]) != '\0')
        {
            for (int x = 0; x < 26; x++)
            {
                
//just as before, checks which letter in the alphabet represents the current character in the text

                if (alpha_l[x] == (text[z]))
                {
                    
//sets the current key character to lowercase in oder to keep the format
                    
                    cyph[z] = tolower(key[x]);
                    break;
                }
            }
        }
        
//stores the ponctuation and " " of the text inside the cipher variable
        
        else if (text[z] != '\0')
        {
            cyph[z] = text[z];
           
        }
    }  
    
    printf("ciphertext: %s\n", cyph);
    
    return 0;
}
