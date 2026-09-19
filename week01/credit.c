#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number1 = get_long("Number: ");
    long number2 = number1;
    long number3 = number2;
    long number4 = number3;
    int luhn = 0;
    int digit = 0;
    int totaldigits = 0;
    // Calculate the luhn checksum
    while (number1 != 0)
    {
        digit = (((number1 / 10) % 10) * 2);
        number1 = number1 / 100;
        if (digit >= 10)
        {
            luhn = luhn + (digit / 10) + (digit % 10);
        }
        else
        {
            luhn = luhn + digit;
        }
    }
    while (number2 != 0)
    {
        digit = number2 % 10;
        number2 = number2 / 100;
        luhn = luhn + digit;
    }
    // Count the number of digits
    while (number3 != 0)
    {
        number3 = number3 / 10;
        totaldigits++;
    }
    // Get the first 2 digits
    for (int i = totaldigits - 2; i > 0; i--)
    {
        number4 = number4 / 10;
    }
    // Determine the card issuer and print it
    if ((luhn % 10) != 0)
    {
        printf("INVALID\n");
    }
    else if ((number4 == 34 || number4 == 37) && totaldigits == 15)
    {
        printf("AMEX\n");
    }
    else if ((number4 == 51 || number4 == 52 || number4 == 53 || number4 == 54 || number4 == 55) &&
             totaldigits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (((number4 / 10) == 4) && (totaldigits == 13 || totaldigits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
