#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int digit;
    int count = 0;
    int odd = 0;
    int even = 0;
    char result[12] = "INVALID\n";
    long long input = get_long_long("Number: ");
    long long number = input;

    //Loop to count the character of the input string
    while (number > 0)
    {
        //Check for the last first 2 digit
        if (number > 9 && number < 100)
        {
            count += 2;
            switch (count)  //Switch statement to check the length of number
            {
                case 13:
                    if (number / 10 == 4)
                    {
                        strcpy(result, "VISA\n");
                    }
                    break;
                case 15:
                    if (number == 34 || number == 37)
                    {
                        strcpy(result, "AMEX\n");
                    }
                    break;
                case 16:
                    if (number / 10 == 4)
                    {
                        strcpy(result, "VISA\n");
                    }
                    else if (number > 50 && number < 56)
                    {
                        strcpy(result, "MASTERCARD\n");
                    }
                    break;
                default:
                    printf("%s", result);
                    return 0;
            }
            number = 0;
        }
        else
        {
            number = number / 10;
            count++;
        }
    }

    number = input;

    //Luhn’s Algorithm - Get the total of all digits
    while (number > 0)
    {
        digit = number % 100;
        number = number / 100;

        odd += digit % 10;
        int a = (digit / 10) * 2;
        even += a % 10 + a / 10;
    }

    //Luhn’s Algorithm - Check the last digit of the sum
    if ((odd + even) % 10 != 0)
    {
        strcpy(result, "INVALID\n");
    }

    printf("%s", result);
    return 0;
}