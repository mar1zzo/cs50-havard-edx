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

//Declaration of the function of counting only sentences
int sentences_counter(string text);

//Declaration of the function that calculates the Coleman-Liau index
void coleman_liau_index(float sentences, float words, float letters);

int main(void)
{
    // Prompt for user's name
    string text = get_string("Text: ");

    //Calculates the number of sentences
    float sentences = sentences_counter(text);

    //Calculates the number of words
    float words = words_counter(text);

    //Calculates the number of letters
    float letters = letters_counter(text);

    //Displays the degree according to the Coleman-Liau index
    coleman_liau_index(sentences, words, letters);

}

//calculate of the function of counting only letters
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

//calculate of the function of counting only words
int words_counter(string text)
{
    int n = 0;
    int count_words = 0;

    // Count number of words up until '\0' (aka NUL)
    while (n < strlen(text))
    {
        //verifica se tem espaco
        if (isspace(text[n]))
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

//calculate of the function of counting only words
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

// Check the grade according to the Coleman-Liau index
void coleman_liau_index(float sentences, float words, float letters)
{
    // average number of letters per 100 words
    float l = letters / words * 100;

    // average number of sentences per 100 words
    float s = sentences / words * 100;

    // Calculating Coleman-Liau
    int index = round((0.0588 * l - 0.296 * s) - 15.8);

    // Check the grade according to Coleman-Liau
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