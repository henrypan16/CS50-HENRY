#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void) 
{
    int letters;
    int words;
    int sentences;
    float L, S;
    int index;

    string text = get_string("Text: ");
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);

    //Coleman-Liau index calculation
    L = ((float)letters / (float)words * 100);
    S = ((float)sentences / (float)words * 100);
    index = round(0.0588 * L - 0.296 * S - 15.8);


    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", index);
    }

    printf("\n"); 
    return 0;
}

//Count letter by checking if each character of the string is alphabetical
int count_letters(string text)
{
    int i = 0;
    int count = 0;
    
    while (text[i])
    {
        if (isalpha(text[i]))
        {
            count++;
        }
        i++;
    }
    return count;
}

//Count word by counting the blank space, plus 1 for final word
int count_words(string text)
{
    int i = 0;
    int count = 0;
    
    while (text[i])
    {
        if (isblank(text[i]))
        {
            count++;
        }
        i++;
    }
    return count + 1;
}

//Count word by counting the characters ".", "?" or "!"
int count_sentences(string text)
{
    int i = 0;
    int count = 0;
    
    while (text[i])
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
        i++;
    }
    return count;
}