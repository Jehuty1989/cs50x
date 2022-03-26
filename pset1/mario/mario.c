#include <stdio.h>
#include <cs50.h>

int main(void)

{
    int x;
    
    //Get the height for the blocks. The height must be between 1 and 8
    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x > 8);
    
    //Create an interger a. This value will be how many spaces must be created to indent the stairs to the right. The reason for x-1 is because the stairs closest to the ground do not
    //need a space. This will make sense when int b is explained soon. This command is placed here so it doesn't reset the value of a while running the top for loop.
    int a = x - 1;
    
    //Now to create conditional loops within conditional loops!
    //This top loop will run as long as y is less than x. Each time it is run to the bottom it will add 1 to y and recheck the boolean condition, is y less than x, if true then it will
    //run again without resetting y to 0
    for (int y = 0; y < x; y ++)
    {
        //This conditional loop will display the spaces before the # to indent the stairs to the right. I did this by setting variable b to variable a which is x-1. If the height is 3
        //then x=3 and a=x-1=3-1=2 so therefore b=a=2. This for loop will run as long as b is greater than 0. Each time it runs it subtracts 1 from b then checks to if b is greater than
        //0 and if it is it will run again.
        for (int b = a; b > 0; b --)
        {
            printf(" ");
        }
        
        //When b is no longer greater than 0, 1 is subtracted from a and stored as the new value. If x=3 then a=3-1=2. After the next line of code a will equal 3-1-1=1. The previous for
        //loop relied on int b which equaled a. When the previous for loop is run it will begin with a new value of 1.
        a --;

        //This for loop is to display # as stairs. This will loop as long as z is less than y. z always starts as -1 and y as 0. Because int z resets when it is no longer smaller than
        //y this will always loop the appropriate number of times. With a height of 3, x=3, y=0, z=-1. After 1 cycle of this for loop x still equals 3, y=0 and z=0 so the loop ends and
        //goes on next command which creates a new line before returning to the top level loop. This top level will then y+1 and check the condition y<x. If true then all will run again
        //to this point where z is set back to -1. So if height is 3, x=3, y now equals 1 and z=-1, this for loop will run twice before ending and going on to the next command.
        for (int z = -1; z < y; z ++)
        {
            printf("#");
        }
        
        //I added the next 2 commands to complete the mario more problem set.
        //This command adds the 2 spaces inbetween the stairs.
        printf("  ");
        
        //This command will create the right side of the stairs and runs similarly to the for loop interger z.
        for (int c = -1; c < y; c ++)
        {
            printf("#");
        }
        
        //adds a line at the very last second before returning to the top level for loop and adding 1 to y and rechecking the condition y<x.
        printf("\n");
    }

}