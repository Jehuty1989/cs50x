#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//This int array is for Scrabble points. POINTS[0] represents the points for "a"
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//This function will calculate the score of a word
//It requires 2 inputs, int length and string w. These will be called upon later.
int calc(int length, string w)
{
    int score = 0;
    int scrab = 0;
    //This for loop will run the same number of times as the word is long. E.g., code is 4 letters long so this for loop will run 4 times.
    //int a will always start at 0. As long as a is less than x this loop will run. int x will always be the length of string w.
    for (int a = 0, x = strlen(w); a < x; a++)
    {
        //This formula will convert a lower case letter to a number between 0 & 25. This range of numbers is assosiated with the array of Scrabble POINTS.
        score = w[a] - 97;
        //This if command will check to see if any of the chars in the string do not range from a to z. char a = 0 on the Scrabble POINTS array and so on until char z = 25.
        //If any other char is used the int scrab is set to 0 otherwise it will get a seemingly random score from outside the POINTS array.
        if (score < 0 || score > 25)
        {
            scrab = scrab + 0;
        }
        //If the int score falls into the 0 to 25 range it must now be assigned points based on the Scrabble scoring system. This is gained from POINTS array.
        else
        {
            scrab = scrab + POINTS[score];
        }
    }
    //This return command says what value will be returned once this function has been called to and completed.
    return scrab;
}

int main(void)
{
    //Declaring 2 strings s using an array instead of declaring 2 separate string.
    string s[2];
    s[0] = get_string("Player 1: ");
    s[1] = get_string("Player 2: ");

    //This checks to see if any of the letters in string[0] are uppercase and if they are they will be set to lower case.
    //This is important because uppercase letters have a different ascii value to lowercase so they would fail the if (score < 0 || score > 25) check in function int calc.
    for (int i = 0, n = strlen(s[0]); i < n; i ++)
    {
        if (isupper(s[0][i]))
        {
            s[0][i] = tolower(s[0][i]);
        }
    }

    for (int i = 0, n = strlen(s[1]); i < n; i ++)
    {
        if (isupper(s[1][i]))
        {
            s[1][i] = tolower(s[1][i]);
        }
    }

    //Again I am declaring 2 ints using arrays.
    int scores[2];
    //These ints call upon function calc and send 2 variables. int calc requires values for int length and string w.
    //As below, int length = strlen(s[0]), the number of chars in s[0] and string w = s[0], the actual string itself.
    //Technically I could've kept the variables names the same as they are local variables but I changed them to avoid confusion and to help with debugging.
    scores[0] = calc(strlen(s[0]), s[0]);
    scores[1] = calc(strlen(s[1]), s[1]);

    //A simple if else if else condition check to display who wins based on scores.
    if (scores[0] > scores[1])
    {
        printf("Player 1 Wins!\n");
    }
    else if (scores[0] < scores[1])
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}