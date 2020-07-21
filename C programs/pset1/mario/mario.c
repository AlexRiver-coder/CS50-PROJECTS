#include <stdio.h>
#include <cs50.h>
#include <unistd.h>

// Program to make a tree made of #

int main(void)
{
    int n;
    
// loop to ask a number between 0 and 8

    do
    {
        n = get_int("digit heigh please\n");
    }
    while (n < 1 || n > 8);
    
// left part of the tree

    for (int i = 0; i < n; i++)
    {
        for (int h = 1; h < n - i; h++)
        {
            printf(" ");
        }
        
        for (int g = -1; g < i; g++)    
        {
            printf("#");
        }
        
//space between the parts of the tree

        printf("  ");
        
// right part of the tree

        for (int g = -1; g < i; g++)
        {
            printf("#");
        }
        
        printf("\n");
    }    
}