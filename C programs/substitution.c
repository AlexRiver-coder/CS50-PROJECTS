#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
void convertToUpperCase();
bool validateKey();
bool verifyKeyOnlyContainsLetters();
bool checkIfKeyContainsAllUniqueCharacters();
string convertToCipherText(string plainttext);
 
string key;
 
int main(int argc, string argv[])
{
    //Checks if no key has been provided.
    if (argv[1] == NULL)
    {
        printf("You must provide a 26 digit alphabetic key containing each letter once and only once.\n");
        printf("e.g VCHPRZGJNTLSKFBDQWAXEUYMOI\n");
        return 1;
    }
 
    //Assigns the key from command line to the global variable 'key' and converts it all to uppercase.
    key = argv[1];
    convertToUpperCase(key);
 
    //Checks if function validateKey returns false. See line for function.
    if (!validateKey())
    {
        return 1;
    }
 
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: %s\n", convertToCipherText(plaintext)); //See line 119 for function.
    //Returns 0 to exit program successfully.
    return 0;
}
 
//Function to simply loop over every character in the key and convert them to uppercase.
void convertToUpperCase()
{
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }
}
 
//Performs a couple of checks by function calls to verify key is valid as per the specification given.
bool validateKey()
{
    bool result = false;
    if (!verifyKeyOnlyContainsLetters()) //See line 75.
    {
        printf("Key must only contain letters.\n");
        return result;
    }
    if (strlen(key) != 26) //Makes sure the key is exactly 26 characters long.
    {
        printf("Key must contain exactly 26 characters.\n");
        return result;
    }
 
    if (!checkIfKeyContainsAllUniqueCharacters()) //See line 91.
    {
        printf("Key must contain each character once and only once.\n");
        return result;
    }
 
    //If all the tests pass, result is assigned true and returned.
    result = true;
    return result;
}
 
bool verifyKeyOnlyContainsLetters()
{
    bool result = true;
 
    //Loops through every character of the key and checks that they're all between the range of the uppercase alphabet.
    //(key was converted to uppercase earlier to avoid checking the lowercase letters.)
    for (int i = 0; i < strlen(key); i++)
    {
        if (!(key[i] >= 'A' && key[i] <= 'Z'))
        {
            result = false;
        }
    }
    return result;
}
 
bool checkIfKeyContainsAllUniqueCharacters()
{
    bool result = false;
    int containsLetter = 0;
 
    //Function loops through the alphabet checking each character of the key as it goes.
    for (char currentChar = 'A'; currentChar <= 'Z'; currentChar++)
    {
        for (int i = 0; i <= strlen(key); i++)
        {
            //If the key contains the current letter, it incriments the counter variable (containsLetter) and then moves on to the next letter.
            if (currentChar == key[i])
            {
                containsLetter++;
                //Break statement is essential as once it see's a character in the key it stops and moves on to the next alphabetic character, this checks for duplicate letters within the key.
                break;
            }
        }
    }
 
    //If the counter was successfully incremented to 26 i.e it contains each letter once and only once, result is then assigned true and returned.
    if (containsLetter == 26)
    {
        result = true;
    }
    return result;
}
 
string convertToCipherText(string plaintext)
{
    string ciphertext = plaintext;
 
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        //If block to ignore punctuation.
        if (plaintext[i] == ' ' || plaintext[i] == ',' || plaintext[i] == '.' || plaintext[i] == '?')
        {
            //DO NOTHING
        }
        //Checks if the plaitext is a capital letter, if so it takes off 97 (see asciichart.com) to get the index to 0 and assigns the corresponding key value to the ciphertext.
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            ciphertext[i] = key[plaintext[i] - 65];
        }
        //Same as previous step but for lowercase letters. Takes off 97 this time and then converts the assigned character to lowercase as the key is all uppercase characters.
        if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            ciphertext[i] = key[plaintext[i] - 97];
            ciphertext[i] = tolower(ciphertext[i]);
        }
    }
 
    return ciphertext;
}