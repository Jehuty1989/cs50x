#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //This checks to see if there is more or less than 1 cmd line arg.
    if (argc != 2)
    {
        printf("Key must be input as 1 command line argument.\n");
        return 1;
    }

    int a = strlen(argv[1]);
    //This for function will convert any of the cmd line arg chars to lower case.
    for (int d = 0; d < a; d ++)
    {
        if (isupper(argv[1][d]))
        {
            argv[1][d] = tolower(argv[1][d]);
        }
    }

    //This checks if the string length of the cmd line arg is 26.
    if (a != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //This for function checks each char in the cmd line arg.
    for (int x = 0; x < a; x++)
    {
        //If any of the chars aren't letters it will return 1 to main.
        if (argv[1][x] < 65 || (argv[1][x] > 90 && argv[1][x] < 97) || argv[1][x] > 122)
        {
            printf("Key must contain alphabet characters only.\n");
            return 1;
        }

        //This for loop checks the xth char against all the following chars for any duplicates.
        for (int y = x + 1; y < 26; y ++)
        {
            if (argv[1][x] == argv[1][y])
            {
                printf("Key must not contain duplicate letters.\n");
                return 1;
            }
        }
    }

    string s = get_string("plaintext:  ");
    printf("ciphertext: ");

    int b = strlen(s);
    //This is the beginning of the substitution process
    for (int z = 0; z < b; z++)
    {
        //This if function checks for any chars that aren't alphabet and prints them as is.
        if ((s[z] < 65 || s[z] > 90) && (s[z] < 97 || s[z] > 122))
        {
            printf("%c", s[z]);
        }
        //This step checks if the zth char in the plaintext is uppercase and converts it to the correct location within the key array.
        //It then prints back as an uppercase cipher char. This is necessary as the entire key was either previously converted to all lowercase or may have been typed in lowercase.
        else if (isupper(s[z]))
        {
            int e = s[z] - 65;
            printf("%c", toupper(argv[1][e]));
        }
        //This converts a lowercase plaintext char to a relevant cipherkey char.
        else
        {
            int c = s[z] - 97;
            printf("%c", argv[1][c]);
        }
    }
    printf("\n");
    return 0;
}