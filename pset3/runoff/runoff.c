#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
} candidate;

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
string lower(string input);

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

    /* TODO test loop to be deleted 

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Preferences %i, %i \n", i, preferences[i][j]);
        }
    } 
    */
    

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        /* ToDo delete before submission
        for (int i = 0; i < candidate_count; i++)
        {
            printf("Candidate %s, has %i votes \n", candidates[i].name, candidates[i].votes);
        }
        */

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
    // check for valid name
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i].name, name) == 0)
        {
            //update preference array
            preferences[voter][rank] = i;
            return true;
            break;
        }
    return false;
}
//TODO tabulate counts votes when multiple candidates are eliminated
// Tabulate votes for non-eliminated candidates
void tabulate(void)
{        
    for (int i = 0; i < voter_count; i++)
    {   
        // loop through all candidates
        for (int j = 0; j < candidate_count; j++)
        {   
            
            // identify top position based on candidates left
            int position = 0;
            for (int k =0; k < candidate_count; k++)
            {
                if(preferences[i][position] == k && candidates[k].eliminated == true)
                {
                    position++;
                }
            }
            // !!!TODO check for top vote (need to check later if that's the correct approach)
            if (j == preferences[i][position])
            {
                candidates[j].votes++;
                //printf("%s \n", candidates[j].name);
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //TODO
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // check if candidate i is the winner
        // ToDo Do we need to check if a candidate has been eliminited?
        if ((candidates[i].eliminated == false) && (candidates[i].votes > (voter_count / 2)))
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
    // define local variable to store minimum vote count
    int min_votes = voter_count;
    // loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes <= min_votes)
            {
                min_votes = candidates[i].votes;
            }
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // loop through all remaining candidates and check if anyone has a more votes than min
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > min)
            {
                return false;
            }
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
}

// Transform strings to lowercase to avoid false inputs
string lower(string input)
{
    string transformed_string = input;
    for (int i = 0, string_length = strlen(input); i < string_length; i++)
    {
        transformed_string[i] = tolower(input[i]);
    }
    return transformed_string;
}