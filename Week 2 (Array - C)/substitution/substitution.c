#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int isalphastr(string str);
char* get_cipher(string plaintext, string key);
string to_upperstr(string str);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int is_validEntry = isalphastr(argv[1]);
        //If the entry string cipher alphabet has 26 letters non reppetible
        //continue asking for a input, else it will return a error msg
        char *upper = to_upperstr(argv[1]);
        if (strlen(argv[1]) == 26 && !is_validEntry)
        {
            string plaintext = get_string("Plaintext: ");
            /*Getting the cippertext converted msg and printing*/
            char* ciphertext = get_cipher(plaintext, upper);
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
    /*This function verify if the cipher alfabet is valid(has only letters and 1 equivalent letter per alfabet)*/
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

    //This function receives a plaintext and a key and returns a converted message with the key for each letter
    //making a dynamic memory alloc to cipherstring
    int strlength = strlen(plaintext);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* cipherstring = malloc((strlength + 1) * sizeof(char));
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
    cipherstring[strlength] = '\0';
    return cipherstring;
}


char* to_upperstr(char *str)
{
    //This function just upper bound an array
    int str_length = strlen(str);
    char *upper_string = malloc((str_length + 1) * sizeof(char));  // Allocate memory for uppercase string
    if (upper_string == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);  // Exit program if memory allocation fails
    }

    for (int i = 0; i < str_length; i++)
    {
        upper_string[i] = toupper(str[i]);
        //converting each char to upper case
    }
    //adding a null char in final of string
    upper_string[str_length] = '\0';
    return upper_string;
}