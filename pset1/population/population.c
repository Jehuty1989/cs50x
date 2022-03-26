#include <cs50.h>
#include <stdio.h>

int main(void)

{
    //Declare 3 variables
    //intergers x, y and z
    //Declare var z as 0 because user is not prompted for it.
    int x, y, z = 0;

    //Prompt for start size(x)
    do
    {
        x = get_int("Start size: ");
    }
    //Keep prompting if x is less than 9
    while (x < 9);

    //Prompt for end size(y)
    do
    {
        y = get_int("End size: ");
    }
    //Keep prompting if y is less than x
    while (y < x);

    //Calculate number of years until we reach threshold

    //Repeat this code until start size(x) is larger than
    //or equal to end size(y)
    //Add a year(z) everytime this step is repeated
    //if else added when x=y
    if (x < y)
    {
        do
        {
            x = x + (x / 3) - (x / 4);
            z ++;
        }
        while (x < y);
    }
    else;
    //Print number of years(z)
    {
        printf("Years: %i\n", z);
    }
}