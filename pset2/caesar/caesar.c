#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string cipherText(string text, int key); 

int main(int argc, string argv[])
{
    // check for valid command line argument (only one argument, positive integer)
    
    int key = 0;
    int digit_check;
    if (argc == 2) 
    {
        for (int i = 0, argLeng = strlen(argv[1]); i < argLeng; i++)

            // check whether every element of the command line argument is a digit

        {
            if (!isdigit(argv[1][i]))
            {
                digit_check = 0;
                //printf("Digit check: %i\n", digit_check);
                break;
            }
            else
            {
                digit_check = 1;
                //printf("Digit check: %i\n", digit_check);
            }
            
        }    
        
        if (digit_check == 1)

            // if so move on with asking the user for a text to cipher

        {
            key = atoi(argv[1]);
            string text = get_string("Please enter text: ");
            printf("plaintext: %s\n", text);
            string cipher = cipherText(text, key);
            printf("ciphertext: %s\n", cipher);
            return 0;
        }
        else 

            // if not ask for a valid command line argument

        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else 
       
        // if more than one argument is present, ask the user for a valid command line argument      

    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
   
    
}

string cipherText(string text, int key) 
{
    int cypher_key;
    char cypher_char;
    key = key % 26; // make sure key doesn't overflow
    
    string cipher_text = text; //this was tricky, needed to set the lenght of the string first.
    for (int i = 0, inputLen = strlen(text);  i <= inputLen; i++) 
    {        
        // check for alphabetic characters
        if ((text[i] >= 'a' && text[i] <= 'z')) 
        {   
            // chars range from 97 - 122
            cypher_key = (text[i] + key) % 122;
            if (cypher_key < 97)
            {
                cipher_text[i] = cypher_key + 96;  
            }
            else 
            {
                cipher_text[i] = cypher_key;
            }
            //printf("cipher_key: %c\n", cypher_key);

        }
        else if ((text[i] >= 'A' && text[i] <= 'Z'))
        {
            // chars range from 65 - 90
            cypher_key = (text[i] + key) % 90;
            if (cypher_key < 65)
            {
                cipher_text[i] = cypher_key + 64;  
            }
            else 
            {
                cipher_text[i] = cypher_key;
            }
            //printf("cipher_key: %c\n", cypher_key);
        }
        else 
        {
            cipher_text[i] = text[i];
        }
    }
    return cipher_text;
}