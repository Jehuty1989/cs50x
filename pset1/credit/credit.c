#include <stdio.h>
#include <cs50.h>

//Declaring prototype for the Luhn formula that may be used if the card number falls within a specified number range.
int get_luhn(void);
//Declaring a global variable that will be used in both processes.
long x;

int main(void)
{
    //I had to define these variables individually. I am still not sure why.
    int visa = 0;
    int amex = 0;
    int mc = 0;
    int z = 0;

    x = get_long("Number: ");

    //These if statements make sure the card number falls in a specific number range.
    if ((x > 3999999999999999 && x < 5000000000000000) || (x > 3999999999999 && x < 5000000000000))
    {
        visa = 1;
        
        //If a card number falls within the specified number range it must now pass a Luhn formula test to be autheticated.
        z = get_luhn();
    }

    else if ((x > 339999999999999 && x < 350000000000000) || (x > 369999999999999 && x < 380000000000000))
    {
        amex = 1;

        z = get_luhn();
    }

    else if (x > 5099999999999999 && x < 5600000000000000)
    {
        mc = 1;
        
        z = get_luhn();
    }

    //These last steps check to see if the inputted number both changed the visa, amex or mc variable to 1 AND if
    //they passed the Luhn test by outputting a final number of 0 in the Luhn formula.
    if (visa == 1 && z == 0)
    {
        printf("VISA\n");
    }

    else if (amex == 1 && z == 0)
    {
        printf("AMEX\n");
    }

    else if (mc == 1 && z == 0)
    {
        printf("MASTERCARD\n");
    }

    else
    {
        printf("INVALID\n");
    }
}

int get_luhn(void)
{
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p = 0;
    int luhn;
    
    //I worked out a formula to separate the card numbers and store them as their own variables.
    a = x % 10;
    b = ((x / 10) % 10) * 2;
    c = (x / 100) % 10;
    d = ((x / 1000) % 10) * 2;
    e = (x / 10000) % 10;
    f = ((x / 100000) % 10) * 2;
    g = (x / 1000000) % 10;
    h = ((x / 10000000) % 10) * 2;
    i = (x / 100000000) % 10;
    j = ((x / 1000000000) % 10) * 2;
    k = (x / 10000000000) % 10;
    l = ((x / 100000000000) % 10) * 2;
    m = (x / 1000000000000) % 10;
    n = ((x / 10000000000000) % 10) * 2;
    o = (x / 100000000000000) % 10;
    p = ((x / 1000000000000000) % 10) * 2;

    //In Luhns formula if there is a double digit, e.g. 13 then you would separate the digits and add them together, 1+3=4. This is the same as subtracting 9 from whatever the
    //double digit number may be, 13-9=4. I found that subtracting 9 from any potential double digit number would require less steps than trying to separate the numbers and add them.
    if (b > 9)
    {
        b = b - 9;
    }

    if (d > 9)
    {
        d = d - 9;
    }

    if (f > 9)
    {
        f = f - 9;
    }

    if (h > 9)
    {
        h = h - 9;
    }

    if (j > 9)
    {
        j = j - 9;
    }

    if (l > 9)
    {
        l = l - 9;
    }

    if (n > 9)
    {
        n = n - 9;
    }

    if (p > 9)
    {
        p = p - 9;
    }

    //This is the final part of Luhns formula. This will be the sum of all the individual digits then modulo 10.
    luhn = (a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p) % 10;
    
    return luhn;
}