#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Create a variable called name which is a string
    //Store this variable after asking What is your name?
    string name = get_string("What is your name?\n");

    {
        //Now to display the stored variable
        //Show hello, then the string called name
        printf("hello, %s\n", name);
    }
}