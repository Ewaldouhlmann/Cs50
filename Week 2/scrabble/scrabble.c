#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_points(string str);
void get_winner (int points_a, int points_b);


int main (void)
{
    //Initializing the strings
    string first_string = get_string("Player 1: ");
    string second_string = get_string("Player 2: ");

    //getting the points for each player
    int points_p1 = get_points(first_string);
    int points_p2 = get_points(second_string);

    //printing the results
    get_winner(points_p1, points_p2);
    return 0;
}

int get_points(string str)
{
    int points = 0;

    //Creating an string for each equivalent points per letter
    char  one_point[] = "AEILNORSTU";
    char  two_points[] = "DG";
    char  three_points[] = "BCMP";
    char  four_points[] = "FHVWY";
    char  five_points[] = "K";
    char  eight_points[] = "JX";
    char ten_points[] = "QZ";

    for (int i = 0, lenght = strlen(str);i < lenght;i++)
    {
        //upper bound each char and add points for equivalent letter
        char upper_char = toupper(str[i]);

        if (strchr(one_point, upper_char) != NULL)
        {
            points++;
        }
        else if (strchr(two_points, upper_char) != NULL)
        {
            points += 2;
        }
        else if (strchr(three_points, upper_char) != NULL)
        {
            points += 3;
        }
        else if (strchr(four_points, upper_char) != NULL)
        {
            points += 4;
        }
        else if (strchr(five_points, upper_char) != NULL)
        {
            points += 5;
        }
        else if (strchr(eight_points, upper_char) != NULL)
        {
            points += 8;
        }
        else if (strchr(ten_points, upper_char) != NULL)
        {
            points += 10;
        }
    }

    return points;
}


void get_winner (int points_a, int points_b)
{
    // A simple comparing between the player 1 points and player two
    if ( points_a > points_b )
    {
        printf("Player 1 wins!\n");
    }
    else if ( points_a < points_b )
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}