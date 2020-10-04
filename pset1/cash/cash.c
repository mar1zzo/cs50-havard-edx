//program change owed by Mari Rizzo
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int residual(int r, int c);
int coins(int v, int c);
int typecoins(int i);

int main(void)
{
    float cash;

    //Prompt user and check value is valid
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash <= 0);

    //round your cents
    int residue = round(cash * 100);
    int count = 0;

    //get the number of coins to change
    for (int i = 1; i != 5; i++)
    {
        int coin = typecoins(i);
        count += coins(residue, coin);
        residue = residual(residue, coin);
    }
    printf("%i\n", count);
}

//get the rest
int residual(int r, int c)
{
    r %= c;
    return r;
}

//get the number of coins
int coins(int v, int c)
{
    v /= c;
    return v;
}

//change the type of currency (25, 10, 5 or 1)
int typecoins(int i)
{
    int c;
    if (i == 1)
    {
        return c = 25;
    }
    else if (i == 2)
    {
        return c = 10;
    }
    else if (i == 3)
    {
        return c = 5;
    }
    else
    {
        return c = 1;
    }
}