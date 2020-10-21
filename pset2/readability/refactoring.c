//program that calculates an approximate series needed to understand some text by Mari Rizzo
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Declaration of the function of counting only letters
int letters_counter(string t);

//Declaration of the function of counting only words
int words_counter(string text);

//Call of the function of counting only sentences
int sentences_counter(string text);

int main(void)
{
    // Prompt for user's name
    string text = get_string("Text: ");

    // Shows the number of letters
    //printf("%i letter(s)\n", letters_counter(text));

    // Shows the number of words
    //printf("%i word(s)\n", words_counter(text));

    // Shows the number of sentences
    //printf("%i sentence(s)\n", sentences_counter(text));

    // Calculando o Coleman-Liau
    //index = 0.0588 * L - 0.296 * S - 15.8

    float sentences = sentences_counter(text);
    float words = words_counter(text);
    float letters = letters_counter(text);

    //número médio de letras por 100 palavras
    //L = Letras ÷ Palavras × 100 = 639 ÷ 119 × 100 ≈ 537
    float l = letters / words * 100;
    //printf("l = %f\n", l);

    //número médio de sentenças por 100 palavras
    //S = Frases ÷ Palavras × 100 = 5 ÷ 119 × 100 ≈ 4,20
    float s = sentences / words * 100;
   // printf("s = %f\n\n", s);


    //float a = 0.0588 * l;
    //printf("a = %f\n", a);

    //float b =  0.296 * s;
    //printf("b = %f\n", b);

    //float ab = 0.0588 * l - 0.296 * s;
    //printf("ab = %f\n", ab);

    //float abc = (0.0588 * l - 0.296 * s) - 15.8;
    //printf("abc = %f\n", abc);

    // Calculando o Coleman-Liau
    int index = round((0.0588 * l - 0.296 * s) - 15.8);
    //printf("Index = %i\n", index);

    //Verifica qual o grau de acordo com a Coleman-Liau
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

//Call of the function of counting only letters
int letters_counter(string text)
{
    int n = 0;
    int count_letters = 0;

    // Count number of letters up until '\0' (aka NUL)
    while (text[n] != '\0')
    {
        if (isalpha(text[n]))
        {
            count_letters++;
            n++;
        }
        else
        {
            n++;
        }
    }
    return count_letters;
}

//Call of the function of counting only words
int words_counter(string text)
{
    int n = 0;
    int count_words = 0;

    // Count number of words up until '\0' (aka NUL)
    while (n < strlen(text))
    {
        //verifica se tem espaco
        if ( isspace(text[n]))
        {
            count_words++;
            n++;
        }
        else
        {
            n++;
        }
    }
    return count_words + 1;
}

//Call of the function of counting only words
int sentences_counter(string text)
{
    int n = 0;
    int count_sentences = 0;

    // Count number of words up until '\0' (aka NUL)
    while (n < strlen(text))
    {
        //verifica se o caracter da sentenca eh um . ou ! ou ??
        if (text[n] == '.' || text[n] == '!' || text[n] == '?')
        {
            count_sentences++;
            n++;
        }
        else
        {
            n++;
        }
    }
    return count_sentences;
}
