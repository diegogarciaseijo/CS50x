#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if the user entered exactly 1 argument after the command
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check that the key has exactly 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        // Check that the key contains only letters
        char letter = argv[1][i];
        if (!isalpha(letter))
        {
            printf("Key can only contain letters\n");
            return 1;
        }
        // Check that no letter is repeated (case-insensitive)
        for (int j = i + 1; j < 26; j++)
        {
            if (toupper(letter) == toupper(argv[1][j]))
            {
                printf("Letters can not be repeated\n");
                return 1;
            }
        }
    }
    string text = get_string("plaintext: ");
    // Replace each letter with its corresponding letter in the key
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char c = text[i];
        if (isupper(c))
        {
            int index = c - 'A';
            text[i] = toupper(argv[1][index]);
        }
        else if (islower(c))
        {
            int index = c - 'a';
            text[i] = tolower(argv[1][index]);
        }
    }
    printf("ciphertext: %s\n", text);
}
