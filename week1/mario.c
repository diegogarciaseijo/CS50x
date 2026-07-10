#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int spaces;
    int hashs;
    do
    {
        height = get_int("Height: ");
    }
    while (1 > height || height > 8);
    for (int i = 0; i < height; i++)
    {
        for (spaces = 0; spaces < height - i - 1; spaces++)
        {
            printf(" ");
        }
        for (hashs = 0; hashs < i + 1; hashs++)
            printf("#");
        printf("  ");
        for (hashs = 0; hashs < i + 1; hashs++)
            printf("#");
        printf("\n");
    }
}
