#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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

    for (int n = 0; n < candidate_count; n++)
    {
        if (strcmp(candidates[n].name, name) == 0)
        {
            preferences[voter][rank] = preferences[voter][rank] + n;
            return true;
        }
    }

    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int candi_count = 0;
    for (int a = 0; a < voter_count; a++)
    {
        if (!candidates[(preferences[a][candi_count])].eliminated)
        {
            candidates[(preferences[a][candi_count])].votes = candidates[(preferences[a][candi_count])].votes + 1;
        }
        else
        {
            while (candidates[(preferences[a][candi_count])].eliminated)
            {
                candi_count = candi_count + 1;
            }
            candidates[(preferences[a][candi_count])].votes = candidates[(preferences[a][candi_count])].votes + 1;
            candi_count = 0;
        }
    }

    // TODO
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int check = 0; check < candidate_count; check++)
    {
        if (candidates[check].votes > round((float) voter_count / 2))
        {
            fprintf(stdout, "%s\n", candidates[check].name);
            return true;
        }
    }

    // TODO
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_score = 0;
    for (int a = 0; a < candidate_count; a++)
    {
        if ((min_score < candidates[a].votes) && !candidates[a].eliminated)
        {
            min_score = candidates[a].votes;
        }
    }
    return min_score;
    // TODO
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int candi_in = 0;
    int candi_with_min = 0;
    for (int b = 0; b < candidate_count; b++)
    {
        if (!candidates[b].eliminated && candidates[b].votes == min)
        {
            candi_with_min = candi_with_min + 1;
        }
    }
    for (int c = 0; c < candidate_count; c++)
    {
        if (!candidates[c].eliminated)
        {
            candi_in = candi_in + 1;
        }
    }
    if (candi_in == candi_with_min)
    {
        return true;
    }

    // TODO
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int d = 0; d < candidate_count; d++)
    {
        if (candidates[d].votes == min)
        {
            candidates[d].eliminated = true;
        }
    }
    // TODO
    return;
}