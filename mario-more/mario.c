#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    int height = 0;

    //Get user input, reprompt for answer if input is not between 1 and 8
    while(height < 1 || height > 8)
    {
        fflush(stdin);
        printf("Height: ");
        scanf("%i", &height);
    }

    //Printing each row of pyramid
    for(int i = 0; i < height; i++)
    {
        //Printing first half of pyramid
        for(int j = 0; j < height; j++)
        {
            if(j >= height - i - 1) printf("#");
            else printf(" ");
        }
        printf("  ");

        //Printing second half of pyramid
        for(int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}