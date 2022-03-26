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
}
pair;

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

bool chain(int og_win, int lose);

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
    //Simple for loop to check if voters names match the candidates
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(name, candidates[a]) == 0)
        {
            ranks[rank] = a;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //A 2 tier for loop to update the preferences array based on votes
    for (int a = 0; a < candidate_count - 1; a++)
    {
        for (int b = a + 1; b < candidate_count; b++)
        {
            preferences[ranks[a]][ranks[b]] = preferences[ranks[a]][ranks[b]] + 1;
        }
    }

    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //2 tier for loop that updates winners and losers in the pairs struct while also updating the int pair_count
    for (int a = 0; a < candidate_count - 1; a++)
    {
        for (int b = a + 1; b < candidate_count; b++)
        {
            if (preferences[a][b] > preferences[b][a])
            {
                pairs[pair_count].winner = a;
                pairs[pair_count].loser = b;

                pair_count++;
            }
            else if (preferences[b][a] > preferences[a][b])
            {
                pairs[pair_count].winner = b;
                pairs[pair_count].loser = a;

                pair_count++;
            }
        }
    }

    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //ints to keep track of strength of victory
    int strength[pair_count];
    int strong;
    int weak;

    //Update strength array with strength of victory based on preferences array
    for (int a = 0; a < pair_count; a++)
    {
        strength[a] = preferences[pairs[a].winner][pairs[a].loser] - preferences[pairs[a].loser][pairs[a].winner];
    }

    //2 tier for loop to sort pairs with strongest first
    for (int b = 0; b < pair_count - 1; b++)
    {
        for (int c = b + 1; c < pair_count; c++)
        {
            strong = strength[b];
            weak = strength[c];

            if (strong < weak)
            {
                strong = weak;
                weak = strength[b];
                strength[b] = strong;
                strength[c] = weak;
            }
        }
    }

    int winner;
    int loser;
    
    //Use strength array to sort the preferences array
    for (int d = 0; d < pair_count - 1; d++)
    {
        for (int e = d + 1; e < pair_count; e++)
        {
            if (preferences[pairs[d].winner][pairs[d].loser] - preferences[pairs[d].loser][pairs[d].winner] != strength[d])
            {
                winner = pairs[d].winner;
                loser = pairs[d].loser;
                pairs[d].winner = pairs[e].winner;
                pairs[d].loser = pairs[e].loser;
                pairs[e].winner = winner;
                pairs[e].loser = loser;
            }
        }
    }

    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int a = 0; a < pair_count; a++)
    {
        //If statement that calls the recursive function chain and sends the winner and loser of a pairs array
        if (chain(pairs[a].winner, pairs[a].loser))
        {
            locked[pairs[a].winner][pairs[a].loser] = true;
        }
    }

    // TODO
    return;
}

//A recursive function to see if there will be any cycles
bool chain(int og_win, int lose)
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (locked[lose][a])
        {
            //If the candidate being checked is the same as the original winner then that would create a cycle
            if (og_win == a)
            {
                return false;
            }
            else
            {
                //Use and if statement incase no cycle is found on the first try it can try again with the next check on the same candidate
                if (!chain(og_win, a))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Print the winner of the election
void print_winner(void)
{
    for (int a = 0; a < candidate_count; a++)
    {
        int false_how_many = 0;
        
        for (int b = 0; b < candidate_count; b++)
        {
            if (!locked[b][a])
            {
                false_how_many++;
                
                //If a candidate has no true values(arrows) on their locked array they they are the source and the winner
                if (false_how_many == candidate_count)
                {
                    printf("%s\n", candidates[a]);
                }
            }
        }
    }
    
    // TODO
    return;
}