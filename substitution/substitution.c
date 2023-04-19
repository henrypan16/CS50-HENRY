#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[]) 
{
    //Check for correct number of argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Check for correct number of letters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {   
        bool alphabet[26] = {false};
        //Loop through the key
        for (int i = 0; argv[1][i]; i++)
        {
            //Check for special character
            if (!isalpha(argv[1][i]))
            {
                printf("Key must not have special characters.\n");
                return 1;
            }

            //Check for duplicate
            int ascii = (int)toupper(argv[1][i]) - 65;
            if (alphabet[ascii])
            {
                printf("Key must not have duplicate characters.\n");
                return 1;
            }
            alphabet[ascii] = true;
        }

        string plain = get_string("plaintext: ");
        char *cipher = malloc(sizeof(plain));
        strcpy(cipher, plain);

        //Loop through plain text and encrypt each letter at a time
        for (int i = 0; plain[i]; i++)
        {
            //If character is a special character, do not encrypt
            if (isalpha(cipher[i]))
            {
                cipher[i] = argv[1][toupper((int)plain[i]) - 65];
            }
            if (islower(plain[i]))
            {
                cipher[i] = tolower(cipher[i]);
            }
            if (isupper(plain[i]))
            {
                cipher[i] = toupper(cipher[i]);
            }
        }
        printf("ciphertext: %s\n", cipher);
        free(cipher);
    }
    return 0;
}