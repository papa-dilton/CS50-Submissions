#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    const string key = argv[1];

    //make sure we have right num of args
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    //make sure key is 26 letters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        //makes sure key has valid chars
        if (!(key[i] >= 65 && key[i] <= 90) && !(key[i] >= 97 && key[i] <= 122))
        {
            return 1;
        }
        for (int n = i + 1; n < 26; n++)
        {
            //make sure no letters in key are duplicate
            if (key[i] == key[n])
            {
                return 1;
            }
        }
    }


    const string plaintext = get_string("plaintext:  ");
    char cyphertext[strlen(plaintext)];


    //each plaintext char
    for(int p = 0; p < strlen(plaintext); p++)
    {
        const int offset = toupper(plaintext[p]) - 65;
        //printf("%i", toupper(plaintext[p]));

                //if plaintext is uppercase
                if (plaintext[p] >= 65 && plaintext[p] <= 90)
                {
                    cyphertext[p] = toupper(key[offset]);
                }
                else if (plaintext[p] >= 97 && plaintext[p] <= 122)
                {
                    cyphertext[p] = tolower(key[offset]);
                }
                else
                {
                    cyphertext[p] = plaintext[p];
                }


        }
    //fixes issue where strig terminator is not present
    cyphertext[strlen(plaintext)] = '\0';

    printf("ciphertext: %s\n", cyphertext);
    /*
    printf("ciphertext: ");
    int i = 0;
    while (cyphertext[i] != '\0')
    {
        printf("%c", cyphertext[i]);
        i++;
    }
    printf("\n");
    return 0;*/

}