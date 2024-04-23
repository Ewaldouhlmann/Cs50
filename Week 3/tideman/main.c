#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_cycle(int winner, int loser, bool visited[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    /*percurring a loop to find a candidate with the same name*/
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            // Setting rank for the preferences
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    /*This function receives the ranks by each voter and update the preferences array*/
    for (int i = 0; i < candidate_count; i++)
    {
        // getting the row
        int row = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Getting the col and plus one in preferences matrix
            int col = ranks[j];
            preferences[row][col]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    /*This function add pair of candidates to pairs array if one candidadte is preferred
    over the others */
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        /*Percurring the preferences matrix and comparing if the preferences for candidate A
        is diferent then the preferences for B*/
        {
            if (preferences[i][j] != preferences[j][i])
            {
                /*If is different, check who is bigger and create a pair to them*/
                pair newPair;
                if (preferences[i][j] > preferences[j][i])
                {
                    newPair.winner = i;
                    newPair.loser = j;
                    pairs[pair_count] = newPair;
                }
                else
                {
                    newPair.winner = j;
                    newPair.loser = i;
                    pairs[pair_count] = newPair;
                }
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // This function receives an array of pairs and use bublle sort in the array
    while (1)
    {
        // creating a flag to
        bool isSorted = true;
        for (int i = 0; i < pair_count - 1; i++)
        {
            // getting the index of the actual winner and the next one
            int idx_winner = pairs[i].winner;
            int idx_loser = pairs[i].loser;

            int idx_nextwinner = pairs[i + 1].winner;
            int idx_nextloser = pairs[i + 1].loser;

            if (preferences[idx_winner][idx_loser] < preferences[idx_nextwinner][idx_nextloser])
            {
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                isSorted = false;
            }
        }
        if (isSorted)
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    /*This function go through one pair per time and lock them into the graph*/
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Define and initialize the visited array to verify if is a cycle
        bool visited[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            visited[j] = false;
        }
        if (!is_cycle(winner, loser, visited))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Initializing the array to check the winner
    bool is_winner[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        is_winner[i] = true;
    }

    // checking income edges for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // verifing if candidate j has an edge to candidate i, then i isn't a winner
            if (locked[j][i])
            {
                is_winner[i] = false;
                break;
            }
        }
    }

    // Printing the winners
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_winner[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
}

bool is_cycle(int winner, int loser, bool visited[])
{
    // adding a true to currently visited loser in array
    visited[loser] = true;

    for (int j = 0; j < candidate_count; j++)
    {
        // verifing if locked in row loser, col j and j isn't true in viset array
        if (locked[loser][j] && !visited[j])
        {
            // Making a recursion with j instead loser
            if (j == winner || is_cycle(winner, j, visited))
            {
                return true;
            }
        }
        // returning true if a cycle is founded
        else if (locked[loser][j] && visited[j])
        {
            return true;
        }
    }
    // Returning false after verify all candidates
    return false;
}
