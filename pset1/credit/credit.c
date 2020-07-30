#include <stdio.h>
#include <cs50.h>

long get_card_number();
int check_credit_card_number(long);

int main(void)
{
    long card_number = get_card_number();
    check_credit_card_number(card_number);
}

long get_card_number(long card_number)
{
    // ask the user for input: credit card number
    // check whether the input is correct (only integer)
    do
    {
        card_number = get_long("Please type in a valid credit card number: ");
    }
    while (!(card_number >= 0));
    return card_number;
}

int check_credit_card_number(long card_number)
{
    // check credit card lenghts
    int length = 0;
    long exp = 1;
    
    //get length of card nummber
    do 
    {
        length++;
        exp = exp * 10;
    }
    while (card_number / exp >= 1);
    
    int card[length];
    
    //create array
    exp = 1;
    for (int i = 0; i <= (length - 1); i++)
    {
        card[i] = card_number % 10;
        card_number = card_number / 10;
        // printf("%d", card[i]);
    }
    
    //loop through array

    long sum_a = 0;
    long sum_b = 0;
    long sum_c = 0;
    
    for (int j = 0; j <= length - 1; j = j + 2)
    {
        if ((card[j + 1] * 2 / 10) >= 1) // multiply every other digit by 2 starting with the second last
        {
            sum_a = sum_a + ((card[j + 1] * 2) / 10) + ((card[j + 1] * 2) % 10);
        }
        else 
        {
            sum_a = sum_a + (card[j + 1] * 2); 
        }
        sum_b = sum_b + card[j];
    }
    sum_c = sum_a + sum_b;
    // printf("sum_a %li, sum_b %li, sum_c %li", sum_a, sum_b, sum_c);
    
    // check whether the card is valid
    // check wich type of card it is & output the results
    if (sum_c % 10 == 0 && length >= 13)
    {
        if (card[length - 1] == 3 && (card[length - 2] == 4 || card[length - 2] == 7)) 
        {
            return printf("AMEX\n");
        }
        else if (card[length - 1] == 4)
        {
            return printf("VISA\n");
        }
        else if (card[length - 1] == 5 && 
                 (card[length - 2] == 1 || card[length - 2] == 2 || card[length - 2] == 3 || card[length - 2] == 4 || card[length - 2] == 5))
        {
            return printf("MASTERCARD\n");
        }
        else 
        {
            return printf("INVALID\n"); 
        }
    }
    else
    {
        return printf("INVALID\n");
    }
}

