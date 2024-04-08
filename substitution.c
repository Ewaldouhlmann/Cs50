#include <stdio.h>
#include <stdlib.h> // Inclua a biblioteca stdlib.h para usar malloc e free
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int isalphastr(string str);
char* get_cipher(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int is_validEntry = isalphastr(argv[1]);
        if (strlen(argv[1]) == 26 && !is_validEntry)
        {
            string plaintext = get_string("Plaintext: ");
            string upper_cipher = toupper(argv[1])
            char* ciphertext = get_cipher(plaintext, upper_cipher);
            printf("ciphertext: %s\n", ciphertext);
            free(ciphertext);
        }
        else
        {
            printf("Error: Argument must contain 26 alphabetic characters non-repetitive\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./program_name key\n");
        return 1;
    }

    return 0;
}

int isalphastr(string str)
{
    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(str[i]))
        {
            return 1;
        }
        else
        {
            for (int j = i + 1; j < length; j++)
            {
                if (str[j] == str[i])
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

char* get_cipher(string plaintext, string key)
{

    int strlength = strlen(plaintext);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* cipherstring = malloc((strlength + 1) * sizeof(char)); // Alocação dinâmica de memória
    for (int i = 0; i < strlength; i++)
    {
        if (isalpha(plaintext[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    cipherstring[i] = key[j];
                }
                else if (toupper(plaintext[i]) == alphabet[j])
                {
                    cipherstring[i] = tolower(key[j]);
                }
            }
        }
        else
        {
            cipherstring[i] = plaintext[i];
        }
    }
    cipherstring[strlength] = '\0'; // Null terminate the string
    return cipherstring;
}
