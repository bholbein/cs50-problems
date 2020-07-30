#include <stdio.h>
#include <cs50.h>

void build(int);

int main(void)
{
    // ask user for valid input (integer between 1 and 8)
    int height;
    do 
    {
        height = get_int("Height: "); 
    } 
    while (height < 1 || height > 8);
   
    // call function for building the pyramidd
    build(height); 
    
}

void build(int height) 
{
    // build the pyramid
    for (int i = 0; i < height; i++)
    {
        printf("%*s", height - i - 1, "");
        printf("%.*s", i + 1, "########");
        printf("  ");
        printf("%.*s\n", i + 1, "#########");
    }
}