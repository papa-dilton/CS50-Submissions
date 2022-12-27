#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int num_letters(char text[]);
int num_words(char text[]);
int num_sentences(char text[]);

int main(void)
{
    const string text = get_string("Text: ");

    const int letters = num_letters(text);
    const int words = num_words(text);
    const int sentences = num_sentences(text);

    const float letters_per_100words = (((float) letters / words) * 100);
    const float sentences_per_100words = (((float) sentences / words) * 100);


    //Coleman-Liau index math
    int index = round(0.0588 * letters_per_100words - 0.296 * sentences_per_100words - 15.8);

    if (index <= 0)
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
    return 0;

}



int num_letters(char text[])
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        // if char is an english letter
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
    }
    return letters;
}


int num_words(char text[])
{
    const int length = (int) strlen(text);
    int words = 0;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    //accounts for last word not having space afterwards
    if (text[length] != ' ')
    {
        words++;
    }
    return words;
}


int num_sentences(char text[])
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}