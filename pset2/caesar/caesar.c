#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
//Added library stdlib.h for the atoi function which turns char numbers into intergers
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //This function will return 1 to main if there aren't exactly 2 command line arguments including ./caesar as the first one.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //This function checks to see if every char in the cmd line arg is a number.
    int a = strlen(argv[1]);
    for (int x = 0; x < a; x++)
    {
        if (argv[1][x] < 48 || argv[1][x] > 58)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //Function atoi converts char numbers in ints even a whole string of numbers.
    int b = atoi(argv[1]);
    string s = get_string("plaintext:  ");
    int c = strlen(s);
    printf("ciphertext: ");
    for (int y = 0; y < c; y++)
    {
        //This first if function is used to wrap back to a or A after z or Z.
        if (s[y] + b % 26 > 122)
        {
            s[y] = (s[y] + b % 26) - 26;
            printf("%c", s[y]);
        }
        //These else if functions are different because sometimes the caesar algorithm = 0 for some chars .
        else if (s[y] + b % 26 > 90 && s[y] + b % 26 < 97)
        {
            s[y] = (s[y] + b % 26) - 26;
            printf("%c", s[y]);
        }
        else if ((s[y] > 96 && s[y] < 103) || (s[y] > 76 && s[y] < 90) || s[y] == 122)
        {
            printf("%c", s[y] + b % 26);
        }
        else if ((s[y] > 64 && s[y] < 77) || s[y] == 90)
        {
            printf("%c", s[y] + b % 26);
        }
        else if (s[y] > 102 && s[y] < 122)
        {
            printf("%c", s[y] + b % 26);
        }
        //This last else function handles any punctuation.
        else
        {
            printf("%c", s[y]);
        }
    }
    printf("\n");
    return 0;
}