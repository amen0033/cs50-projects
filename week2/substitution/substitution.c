#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];

    // Check key length
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check that all characters are letters
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only letters.\n");
            return 1;
        }
    }

    // Check for repeated letters (case-insensitive)
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }
    }

    // Get plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Encrypt each character
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            int index = plaintext[i] - 'A';
            printf("%c", toupper(key[index]));
        }
        else if (islower(plaintext[i]))
        {
            int index = plaintext[i] - 'a';
            printf("%c", tolower(key[index]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}
