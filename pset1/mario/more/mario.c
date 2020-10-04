//Exercise Mario More - Adjacent pyramids of blocks by Mari Rizzo
#include <cs50.h>
#include <stdio.h>

int get_height(void);
void adjPramids(int n);

int main(void)
{
    //function call to get pyramid height
    int height = get_height();

    //call the Adjacent pyramids of blocks function
    adjPramids(height);
}

//Prompts the user for the height of the adjacent pyramids of blocks
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

// Print Mario's Adjacent pyramids of blocks
void adjPramids(int n)
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

        //iteration for creating the blocks empty
        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }

        //iteration for creating the blocks
        for (int f = 0; f < i; f++)
        {
            printf("#");
        }
        printf("\n");
    }
}
