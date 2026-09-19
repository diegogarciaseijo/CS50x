#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);
// Declare an array that contains the points assigned to each letter
int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt both players for their words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate each player's score
    int points1 = compute_score(word1);
    int points2 = compute_score(word2);

    // Check who won and display it
    if (points1 > points2)
    {
        printf("Player 1 wins!\n");
    }
    else if (points2 > points1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Create a function that calculates each word score
int compute_score(string word)
{
    int score = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Ignore symbols that are not letters
        if (isalpha(word[i]))
        {
            // Convert the letter to uppercase so uppercase and lowercase letters are scored equally
            int n = toupper(word[i]) - 'A';
            score += POINTS[n];
        }
    }
    return score;
}
