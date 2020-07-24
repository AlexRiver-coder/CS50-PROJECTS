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

int voter_count;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count; // contador de pares
int candidate_count; // contador de candidatos;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    voter_count = get_int("Number of voters: ");

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Useful vars to sort
int temp1 = 0;
int temp2 = 0;
int preference_temp = 0;
pair pairtemp [MAX * (MAX - 1) / 2];

// Sort pairs in decreasing order by strength of victory

void sort_pairs(void)
{  
    int d = 0;
    
    for (int i = 0; i < pair_count * pair_count; i++)
    {
        temp1 = pairs[d].winner;
        temp2 = pairs[d].loser;
        preference_temp = preferences[temp1][temp2];
        
        if (preference_temp < preferences[pairs[d + 1].winner][pairs[d + 1].loser])
        {
            pairtemp[d] = pairs[d];
            pairs[d] = pairs[d + 1];
            pairs[d + 1] = pairtemp[d];
        }
       
        if (d < pair_count - 1)
        {
            d++;
        }
        if (d == pair_count - 1)
        {
            d = 0;
        }
    }
}

// variable to skip pairs

bool pair_skip[MAX];

// loop to check if there's a cycle

void iscycle(int index)
{
// Main loop

    for (int i = index; i < pair_count; i++)
    {
// Checks if the winner of this pair has lost to someone

        if (pairs[i].loser == pairs[index].winner)
        {
// Checks if the one who lost is not the strongest pair

            if (index != pairs[0].winner)
            {
// Checks to see if the loser of the main pair has not won the winner

                if (pairs[i].winner != pairs[index].loser)
                {
// Second loop

                    for (int j = 0; j < pair_count; j++)
                    {
// Checks to see if the guy who lost in the main pair, has not won against some other candidate

                        if (pairs[index].loser == pairs[j].winner)
                        {
// third loop

                            for (int f = 0; f < pair_count; f++)
                            {
// Checks to see if the guy who lost to the guy who lost in the main pair has not won agains some other candidate

                                if (pairs[j].loser == pairs[f].winner)
                                {
// Checks to see if the winner of the main pair has not lost to someone whom the loser of his pair has won against

                                    if (pairs[f].loser == pairs[index].winner)
                                    {
                                        pair_skip[i] = true;
                                    }
                                }
                                
                            }
                            
                        }
                    }
                }
            }
        }
    }
}


// Lock pairs into the candidate graph in order, without creating cycles

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i ++)
    {
        if (!pair_skip[i])
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            iscycle(i);
        }
    }
}



// Print the winner of the election

void print_winner(void)
{
    int temp3;
    
// Loop to look if any candidate has not a edge pointing towards him 

    for (int i = 0; i < candidate_count; i++)
    {
        temp3 = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                temp3++;
            }
        } 
        
// If the candidate is found, prints the name ( include draws )

        if (temp3 == candidate_count)
        {
            printf("%s\n", candidates[i]);  
        }
        
    }
}





