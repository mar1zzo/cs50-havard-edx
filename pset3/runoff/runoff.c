#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int exist_candidate = 0;
    int pos_candidate = 0;

    // Valid candidate check
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        string candidate = candidates[i].name;

        //If it is a valid candidate, keep the position and mark it as valid
        if (strcmp(name, candidate) == 0)
        {
            exist_candidate = 1;
            pos_candidate = i;
        }
    }

    //If the candidate is not a valid candidate, returns false
    if (exist_candidate == 0)
    {
        return false;
    }
    else // If not, update the candidate's predecessor matrix
    {
        preferences[voter][rank] = pos_candidate;
        return true;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int count_votes = 0;
    int new_vote = 0;

    // sweeps candidates vector
    for (int z = 0; z < candidate_count; z++)
    {
        if (candidates[z].eliminated == true)
        {
            for (int x = 0; x < voter_count; x++)
            {
                // checks whether the eliminated candidate was preferred more than once and counts
                if (preferences[x][0] == z)
                {
                    count_votes += 1;
                    new_vote = preferences[x][count_votes];

                    //if the next option is for an eliminated candidate, it adds up to 1
                    if (candidates[new_vote].eliminated == true)
                    {
                        count_votes += 1;
                        // checks if there is a next alternative vote, if not, does not count votes
                        if (count_votes < candidate_count)
                        {
                            new_vote = preferences[x][count_votes];
                            candidates[new_vote].votes += 1;
                        }
                    }
                    else
                    {
                        candidates[new_vote].votes += 1;
                    }
                }
            }
            count_votes = 0;
        }
    }

    // scans the two-dimensional preference vector
    for (int i = 0; i < voter_count; i++)
    {
        // get the id of the preferred candidate
        int id_1_candidate = preferences[i][0];

        // checks whether the candidate was NOT eliminated from the election
        if (candidates[id_1_candidate].eliminated != true)
        {
            candidates[id_1_candidate].votes += 1; //count vote
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // checks the number of votes and calculates the number needed to win the election
    int count_votes_winner = round(voter_count / 2);

    for (int i = 0; i < candidate_count; i++)
    {
        // if any candidate has more than half the votes, it returns true
        if (candidates[i].votes > count_votes_winner)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = candidates[0].votes;

    // Take the smallest number of votes from the candidate vector
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated != true && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    //returns the lowest value
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tie = 0;
    int count_candidates_active = 0;

    //get the amount of ties
    for (int i = 0; i <= candidate_count; i++)
    {
        if (candidates[i].eliminated != true && candidates[i].votes == min)
        {
            tie += 1; // sum one in the repeated value
        }
    }

    // Get the number of candidates that are not eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated != true)
        {
            count_candidates_active += 1; // soma um no valor de candidatos que nao estao eliminados
        }
    }

    // checks that all active candidates have the same number of votes
    if (tie == count_candidates_active)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // checks candidates with the least amount of votes and marks as eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
