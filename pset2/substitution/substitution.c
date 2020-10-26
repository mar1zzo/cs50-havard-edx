// program that implements a substitution cipher by Mari Rizzo

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Creating a vector data type
typedef char vetor[100];

int main(int argc, string argv[])
{
    // 1. Get key and validates if there is a key
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    else
    {
        // 2. Validate key
        // 2.1. Check key length
        if (strlen(argv[1]) < 26 || strlen(argv[1]) > 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        // 2.2. Check for non-aplphabetic characters
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
        // 2.3. Check for repeated characters (case-insensitive)
        int count_repeat = 0;
        int n = 0;

        string haystack = argv[1];

        while (n < strlen(haystack))
        {
            char letter[256];
            sprintf(letter, "%c", argv[1][n]);
            string needle = letter;

            for (int i = 0; i < strlen(haystack); i++)
            {
                // convert to type char
                char str[256];
                sprintf(str, "%c", haystack[i]);
                string letter_haystack = str;

                // Scan the sentence for repeated characters and counting
                if (strcmp(letter_haystack, needle) == 0)
                {
                    count_repeat++;
                }
            }
            //If there are repeated letters
            if (count_repeat == 2)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
            else
            {
                count_repeat = 0;
                n++;
            }
        }
        // declaration of vectors
        vetor palavra, alfabeto, codificacao;
        // declaration of variables
        int indice;

        // 3. Getting the key and text to be encrypted
        sprintf(alfabeto, "%s", argv[1]);

        //Prompts for text to be encrypted
        sprintf(palavra, "%s", get_string("plaintext: "));

        //4. Encipher for text
        for (int j = 0, z = strlen(palavra); j <= z; j++)
        {
            //limits the size of the vector
            if (j == z)
            {
                codificacao[j] = '\0';
            }
            else
            {
                //Encrypts the capital letter
                if (isupper(palavra[j]))
                {
                    indice = palavra[j] - 65; //calcula a posicao da futura letra ja do novo alfabeto
                    codificacao[j] = toupper(alfabeto[indice]); //insere a nova letra na posicao i do vetor
                }
                //Encrypts the lower case letter
                else if (islower(palavra[j]))
                {
                    indice = palavra[j] - 97; //calcula a posicao da futura letra ja do novo alfabeto
                    codificacao[j] = tolower(alfabeto[indice]); //insere a nova letra na posicao i do vetor
                }
                else // insert the scores and spaces
                {
                    codificacao[j] = palavra[j];
                }
            }
        }
        //5. Print ciphertext
        printf("ciphertext: %s\n", codificacao);
        return 0;
    }
}
