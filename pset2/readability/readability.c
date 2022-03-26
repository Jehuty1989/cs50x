#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//If I want to declare a function before it is used I must declare its variables as well.
int count_letters(int a, string t);
int count_words(int b, string u);
int count_sentences(int c, string v);

int main(void)
{
    string s = get_string("Text: ");

    int s_len = strlen(s);

    //This is beginning of the Coleman-Liau formula
    float L = (100 / (float) count_words(s_len, s)) * count_letters(s_len, s);
    float S = (100 / (float) count_words(s_len, s)) * count_sentences(s_len, s);
    float coleman = 0.0588 * L - 0.296 * S - 15.8;
    //This function either rounds up or rounds down depending on the decimal digits then truncates it to an interger.
    int coleman_r = round(coleman);

    //These if checks the C-L score and print the correct grade.
    if (coleman_r < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_r > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", coleman_r);
    }
}

int count_letters(int a, string t)
{
    //int letters = int a = string length s
    //The reason for declaring int letters as int a is because int letters may change in value but int a can not change in value.
    //If int letters = string length s then the length of of the text would seemingly get smaller every time a non alphabet char is found meaning the for loop would end early.
    int letters = a;
    for (int x = 0; x < a; x ++)
    {
        //This if function checks to see if any chars fall outside the ascii value of of letters. If they do it subtracts from int letters.
        if ((t[x] < 65 || t[x] > 90) && (t[x] < 97 || t[x] > 122))
        {
            letters = letters - 1;
        }
    }
    return letters;
}

int count_words(int b, string u)
{
    //int words starts at 1 because it is assumed that the passage will not end in a SPACE.
    int words = 1;
    for (int y = 0; y < b; y ++)
    {
        //This checks for any SPACE chars.
        if (u[y] == 32)
        {
            words = words + 1;
        }
    }
    return words;
}

int count_sentences(int c, string v)
{
    int sentences = 0;
    for (int z = 0; z < c; z ++)
    {
        //This checks for any punctuation (.) (!) (?) These 3 in particular.
        if (v[z] == 33 || v[z] == 46 || v[z] == 63)
        {
            sentences = sentences + 1;
        }
    }
    return sentences;
}