#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "cs50.h"

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void) 
{
    string text = get_string("Please enter a string: ");
    float L = (float)count_letters(text) / (float)count_words(text) * 100;
    float S = (float)count_sentences(text) / (float)count_words(text) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}

int count_letters(string text)
{
    int letterCount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
            letterCount ++;
        }
    }
    return letterCount;
}

int count_words(string text)
{
    int wordCount = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        if(text[i] == 32 || text[i] == 0)
        {
            if(text[i-1] != 32)
            {
                wordCount++;
            }
        }
    }
    return wordCount;
}

int count_sentences(string text)
{
    int sentenceCount = 0;
    for (int i =0; i < strlen(text); i++)
    {
        if(text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}