#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Readability program //
// cs50 2020; problem set 2 ; problem 1 //

int main(void)
{
    string text = get_string("text\n");
    
    int words = 1, sentences = 0, letters = 0;
    
    float index = 0;
    
// finding word, sentences and letters quantities //

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    
        else if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentences++;
        }   
    
        else if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    
    
    // classifing process (coleman - leau index //
    
    index = 0.0588 * (100 * (float) letters / (float) words) - 0.296 * (100 * (float) sentences / (float)words) - 15.8;
    
    if (index <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    
    else
    {
        printf("Grade %.0f\n", round(index));   
    }
    
}