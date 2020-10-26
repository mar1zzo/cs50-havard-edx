#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

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
    int exist = 0;

    // check if it is a valid candidate
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        string candidate = candidates[i].name;

        if (strcmp(name, candidate) == 0)
        {
            exist += 1;
        }
    }

    // if it is an INvalid candidate returns false
    if (exist == 0)
    {
        return false;
    }
    else // if not, count the votes
    {
        for (int i = 0, n = candidate_count; i < n; i++)
        {
            string candidate = candidates[i].name;

            if (strcmp(name, candidate) == 0)
            {
                candidates[i].votes += 1;
            }
        }
        return true;
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_votes = candidates[0].votes;
    int deadlock = 0;
    int pos_winner = 0;

    // check which candidate had the most votes
    for (int i = 1, n = candidate_count; i < n; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
            pos_winner = 1;
        }
    }

    // Check if there was a deadlock
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (candidates[i].votes == highest_votes)
        {
            deadlock += 1;
        }
    }

    // shows the candidates with the highest number of votes and possible draws
    if (deadlock > 0)
    {
        for (int i = 0, n = candidate_count; i < n; i++)
        {
            if (candidates[i].votes == highest_votes)
            {
                printf("%s\n", candidates[i].name);
            }
        }
    }
    else
    {
        printf("%s\n", candidates[pos_winner].name);
    }
    return;
}