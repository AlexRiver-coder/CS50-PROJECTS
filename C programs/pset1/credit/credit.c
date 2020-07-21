#include <stdio.h>
#include <cs50.h>
#include <math.h>

void cardCheck(long n);

// Check sum and Card brand //

int main(void)
{
    cardCheck(get_long("write your card number\n"));
}

void cardCheck(long n)
{
    
    // Most variables used //

    int countDigits = 2;
    int test1 = 0;
    long cardNumber = n;
    long Cn = n;
    int sum = 0;
   
    // Check how much digits the card has //

    while (cardNumber > 100)
    {
        cardNumber = cardNumber / 10;
        countDigits++;
    }
    
    /* checks if the Luhn's algorithm works in this card,
    if a card number is divided by 10 the reminder is the last number,
    so we divide to find the last number and after the sorting process,
    we divide the card number for 10 so we lower one decimal place in order to get
    the next number */ 
    
    for (int i = 1; i <= countDigits; i++)
    {
        int number = Cn % 10;
        
        /* just as Luhn's algorithm suggests, we alternate the multiplication process,
        the i works just as a filter, it helps to  alternate between the number that has to be multiplied,
        and the number that doesn't, not only that but helps to format the quantity of numbers the card has */
    
        if (i % 2 == 0)
        {
            if (number * 2 > 9)
            {
                sum += (number * 2) - 9;
            }
            else
            {
                sum += number * 2;   
            }
        }
        else
        {
            sum += number;
        }
            
        Cn /= 10;
    }
    
    sum = sum % 10;
    
    // sorting process to find the brand of the card //
    
    if (sum == 0)
    {
        if ((countDigits == 13 || countDigits == 16) && (cardNumber / 10 == 4))
        {
            printf("VISA\n");
        }
        else if (countDigits == 16 && (cardNumber  > 50 && cardNumber  < 59))
        {
            printf("MASTERCARD\n");
        }
        else if (countDigits == 15 && (cardNumber == 34 || cardNumber == 37))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    else
    {
        printf("INVALID\n");
    }
}
