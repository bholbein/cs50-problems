/**
 * recover.c
 *
 * CS 50 / Problem Set 4
 *
 * Implement a program that recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // check if only 1 command line argument has been passed
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // Open input file
    FILE *inputfile = fopen(argv[1], "r");
    if (inputfile == NULL)
    {
        printf("Can't read file.");
        return 2;
    }

    FILE *outputfile = NULL;

    // reading file
    BYTE buffer[BLOCK_SIZE];
    while (fread(&buffer, BLOCK_SIZE, 1, inputfile) == 1)
    {
        // look for a beginning of a JPEG
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && 
            buffer[3] >= 224 && buffer[3] <= 239)
            printf("%x %x %x %x \n", buffer[0], buffer[1], buffer[2], buffer[3]);

        // open a new JPEG file
        // filenames ###.jpg starting with 000.jpg
        // sprintf(filename, "%03i.jpg", 2);

        // Write in 512 byte chunks until a new JPEG is found

        // FILE *img = fopen(filename, "w");
        // fwrite(data, size, number, outptr);
    }
    if (feof(inputfile))
    {
        printf("end of file");
    }
    else
    {
        printf("An unknown error occured.");
    }    

    fclose(inputfile);
}
