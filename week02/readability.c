#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float index(int letters, int words, int sentences);

int main(void)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;

    string text = get_string("Text: ");

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Count the number of letters
        if (isalpha(text[i]))
        {
            letters++;
        }
        // Count the number of words
        if (text[i] == ' ')
        {
            words++;
        }
        // Count the number of sentences
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    // Calculate the Coleman-Liau index and display the result
    int grade = round(index(letters, words, sentences));
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Create a function that calculates the Coleman-Liau index
float index(int letters, int words, int sentences)
{
    return 0.0588 * letters * 100 / words - 0.296 * sentences * 100 / words - 15.8;
}
