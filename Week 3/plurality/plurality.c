#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //TODO
    /*This function get an name and verify if the name is valid (is a candidate)
    If is a valid vote, then the candidate plus one vote*/
    for (int i = 0; i < candidate_count; i++)
    {
        //Comparing if the string input is igual to a candidate name, and add a vote
        if (!strcmp(candidates[i].name, name))
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    /*This function verify in a array of candidates with one of them have more votes
    and then print the winner*/
    int max_votes = candidates[0].votes;
    string winners[MAX];


    //getting the highest votes
    for (int i = 1; i < candidate_count; i++)
    {
        if(candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    int winner_count = 0;

    //adding the winner in the winners array
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == max_votes)
        {
            winners[winner_count] = candidates[i].name;
            winner_count++;
        }
    }

    //printig the winners
    for (int i = 0; i < winner_count; i++)
    {
        printf("%s\n",winners[i]);
    }
}
