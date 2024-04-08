#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int get_text_info(string text, int *spaces, int *letters, int *sentences);
float get_grade(int qtspaces,int qtletters,int qtsentences);


int main(void)
{
    // Getting user input
    string text = get_string("Text: ");

    //Initializing the variables to count the number of words, letters and sentences.
    int qtspaces = 1;
    int qtletters = 0;
    int qtsentences = 0;

    //sending the text and pointers for the variables to the get_text_info function
    int l = get_text_info(text, &qtspaces, &qtletters, &qtsentences);

    //calculating the grade
    int grade = round(get_grade(qtspaces,qtletters,qtsentences));

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
    return 0;
}

int get_text_info(string text, int *spaces, int *letters, int *sentences)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // For each char, verifing if is a space or a letter
        // and adding to equivalent counters
        if (*spaces == 100)
        {
            break;
        }
        if (text[i] == ' ')
        {
            (*spaces)++;
        }
        else if (isalpha(text[i]))
        {
            (*letters)++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            (*sentences)++;
        }
    }
    return 0;
}


float get_grade(qtspaces,qtletters,qtsentences)
{
    //This function receives the quantity of spaces, letters and sentences
    //and calcule the Coleman-Liau index.
    float aver_letter = (float) qtletters/qtspaces * 100;
    float aver_sent = (float) qtsentences/qtspaces *100;

    float index = 0.0588 * aver_letter - 0.296 * aver_sent - 15.8;
    return index;
}