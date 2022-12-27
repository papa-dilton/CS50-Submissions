#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
bool recursive_check(int j, int iterations);
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
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            int pref_a = preferences[pairs[j].winner][pairs[j].loser];
            int pref_b = preferences[pairs[j + 1].winner][pairs[j + 1].loser];
            if(pref_a < pref_b)
            {
                pair temp_a = pairs[j + 1];
                pairs[j + 1] = pairs[j];
                pairs[j] = temp_a;
            }
        }
    }
    return;
}
/*
pair[] merge_sort(pair cur_pairs)
{
    int size = sizeof cur_pairs / sizeof cur_pairs[0];
    if (size > 1)
    {
        pair left[floor(size / 2)];
        pair right[ceil(size / 2)];

        for (int i = 0; i < size; i++)
        {
            if (i < size / 2)
            {
                left[i] = cur_pairs[i];
            }
            else
            {
                right[i - ceil(size/2)];
            }
        }

        pair sorted_left[] = merge_sort(left);
        pair sorted_right[] = merge_sort(right);

        int left_ind = 0;
        int right_ind = 0;

        pair to_return[size];

        for (int i = 0; i < size; i++)
        {
            if (sorted_right[right_ind] >= sorted_left[left_ind])
            {
                to_return[i] = sorted_right[right_ind];
                right_ind++;
            }
            else
            {
                to_return[i] = sorted_left[left_ind];
                left_ind++;
            }
        }

        return to_return;
    }
    else
    {
        return cur_pairs;
    }

}*/


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    //lock 1st pair
    locked[pairs[0].winner][pairs[0].loser] = true;


    //check and lock all other pairs
    for (int i = 1; i < pair_count; i++)
    {
        if (!recursive_check(pairs[i].loser, 0))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool recursive_check(int j, int iterations)
{
    //DEBUG -------------------------
    bool* temp[9][9];
    for (int i = 0; i < MAX; i++)
    {
        for (int q = 0; q < MAX; q++)
        {
            temp[i][q] = &locked[i][q];
        }
    }
    //END DEBUG -----------------------
    for (int k = 0; k < candidate_count; k++)
    {
        if (locked[j][k])
        {
            bool tmp = recursive_check(k, iterations + 1);
            return tmp;
        }
    }
    if (iterations >= candidate_count - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Print the winner of the election
void print_winner(void)
{
    //start looking at the strongest win
    int to_look_above = pairs[0].winner;

    //look to see if anyone is winning against current winner
    bool has_found_top = false;
    while (!has_found_top)
    {
        has_found_top = true;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][to_look_above])
            {
                to_look_above = i;
                has_found_top = false;
                break;
            }
        }
    }

    printf("%s\n", candidates[to_look_above]);
    return;
}