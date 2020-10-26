//valid credit card check program by Mari Rizzo
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int isParity(int n);
int isZero(int n);

int main(void)
{
    //Get and verify a long valid number
    long nPrompt;
    do
    {
        nPrompt = get_long("Number: ");
    }
    while (nPrompt <= 0);

    long visa = nPrompt;
    char str[256];
    sprintf(str, "%li", visa);

    //checks the number of characters
    if (strlen(str) < 13 || strlen(str) > 16)
    {
        printf("INVALID\n");
    }
    else
    {
        int total_penultimos = 0;
        int total_ultimos = 0;
        int total_parcial = 0;
        int total_final = 0;

        //calculation checksum
        for (int i = 0, n = strlen(str); i < n; i++)
        {
            //returns digit from number
            long digit = visa % 10;

            //returns the number without the final digit
            visa = visa / 10;

            //calculating penultimate digits
            if (isParity(i) != 0)
            {
                //multiplies by 2 and adds the penultimate numbers
                int number = digit * 2;
                if (number > 9)
                {
                    while (number > 0)
                    {
                        int p = number % 10;
                        number = number / 10;
                        total_penultimos = total_penultimos + p;
                    }
                }
                else
                {
                    total_penultimos += number;
                }
            }
            else //calculates the other digits
            {
                total_ultimos += digit;
            }
        } //final do for

        total_final = total_ultimos + total_penultimos;

        char two[256];
        sprintf(two, "%c%c", str[0], str[1]);
        int twoI = atoi(two);

        //check if card is valid
        if (isZero(total_final) != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            //check if there is a number VISA stars 4
            if (str[0] == '4')
            {
                printf("VISA\n");
            }
            else
            {
                //check if there is a number American Express (15 digits, stars 34 or 37)
                if (strlen(str) == 15 && (twoI == 34 || twoI == 37))
                {
                    printf("AMEX\n");
                }
                else if (strlen(str) == 16 && twoI >= 51 && twoI <= 55)
                {
                    //validate MASTERCARD
                    //16 digits, stars 51, 52, 53, 54 or 55
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
    }
}

// Check parity of integer
int isParity(int n)
{
    if (n % 2 == 0)
    {
        return 0; //even
    }
    else
    {
        return 1; //odd
    }
}

//Last digit validation card
int isZero(int n)
{
    int r = n % 10;
    if (r == 0)
    {
        return r;
    }
    else
    {
        return -1;
    }

}