#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

string get_text(void);
float calc_coli_index(string input);

int main(void)
{
    string text = get_text();

    int result = calc_coli_index(text);

    if (result <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result <= 16)
    {
        printf("Grade %i\n", result);
    }
    else
    {
        printf("Grade 16+\n")    ;
    }

}

string get_text(void)
{
    /**
     * Get the users input (looking for a text)
     * Output es Text
     */

    string input = get_string("Text: ");
    return input;
}

float calc_coli_index(string input)
{
    /**
     *  Coleman-Liau index: index = 0.0588 * L - 0.296 * S - 15.8
     *  Calculate L as avg. number of letters per 100 words in the text
     *  Count letters (a-z, A-Z)
     *  Loop through string and increment letter counter if char is a letter
     *      Count words (any sequence of characters seperated by spaces)
     *      Loop through the string and increment word counter after spaces
     * Calculate S as avg. number of sentences per 100 words in the text
     *      Count sentences (seperated by period, exclamation point, or question mark)
     *      Loop through the string and increment sentences if a punctuation mark appears
     *      What about "!!!" etc.?
    */

    int letter_count = 0;
    int word_count = 1;
    int sentence_count = 1;


    for (int i = 0, inputLen = strlen(input); i <= inputLen; i++)
    {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            //increment letter_count
            letter_count++;
        }
        else if (input[i] == 32)
        {
            //increment word_count
            word_count++;
        }
        else if ((input[i] == 33 || input[i] == 46 || input[i] == 63) && (input[i+1] == 32))
        {
            //increment scentence_count
            sentence_count++;
        }
    }

    printf("Letter: %d, Words: %d, Sentences: %d, \n", letter_count, word_count, sentence_count);

    float index = 0.0588 * (100 * (float) letter_count / (float) word_count) - 0.296 * (100 * (float) 
                  sentence_count / (float) word_count) - 15.8;
    return round(index);
}