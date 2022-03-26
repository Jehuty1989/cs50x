#include <stdio.h>
#include <cs50.h>
//Including the math.h for the round command
#include <math.h>

int main(void)

{
    float dollars;
    int coins = 0;
    {
        do
        {
            dollars = get_float("Change owed: ");
        }
        while (dollars < 0);
    }
    
    //This command declares the cents int as a rounded value dollars float x 100
    int cents = round(dollars * 100);
    
    //If I didn't use the >= in these if statements it wouldn't subtract 25 from 25 as 25 is NOT greater than 25. The same applies for 10, 5 and 1.
    if (cents >= 25)
        do
        {
            cents = cents - 25;
            coins ++;
        }
        while (cents >= 25);
        
    if (cents >= 10)
        do
        {
            cents = cents - 10;
            coins ++;
        }
        while (cents >= 10);
        
    if (cents >= 5)
        do
        {
            cents = cents - 5;
            coins ++;
        }
        while (cents >= 5);
    
    //I now realise that >=1 and >0 are essentially the same!
    if (cents >= 1)
        do
        {
            cents = cents - 1;
            coins ++;
        }
        while (cents >= 1);
    
    printf("%i\n", coins);
    
}