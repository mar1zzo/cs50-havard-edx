//Exercise Mario Less - Right-aligned pyramid by Mari Rizzo
#include <cs50.h>
#include <stdio.h>

int get_height(void);
void pyramid(int n);

int main(void)
{
    //function call to get pyramid height
    int height = get_height();

    //call the pyramid building function
    pyramid(height);
}

//Prompts the user for the height of the right-aligned pyramid
int get_height(void)
{
    int n;

    //requests the height of the pyramid
    do
    {
        n = get_int("Height:");
    }
    while (n < 1 || n > 8);
    return n;
}

// Print Mario's right-aligned pyramid
void pyramid(int n)
{
    //iteration for creation height of the pyramid
    for (int i = 1; i <= n; i++)
    {
        //iteration to align right
        for (int c = n; c > i; c--)
        {
            printf(" ");
        }

        //iteration for creating the blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
