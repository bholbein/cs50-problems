/**
 * recover.c
 *
 * CS 50 / Problem Set 4
 *
 * Implement a program that recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    FILE *img = NULL;
    char filename[7];
    int img_counter = 0;

    // reading file
    BYTE buffer[BLOCK_SIZE];
    while (fread(&buffer, BLOCK_SIZE, 1, inputfile) == 1)
    {
        // look for a beginning of a JPEG
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 &&
            buffer[3] >= 224 && buffer[3] <= 239)
        {
            // check if new image is alread open, if yes close first
            if (img_counter > 0)
            {
                fclose(img);
            }

            // create a new incremental filename
            sprintf(filename, "%03i.jpg", img_counter);

            // open a new image
            img = fopen(filename, "w");

            if (img == NULL)
            {
                fprintf(stderr, "Not able to create %s. \n", filename);
            }

            img_counter++;
        }

        if (img != NULL)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, img);
        }
    }
    if (feof(inputfile))
    {
        printf("end of file");
    }
    else
    {
        printf("An unknown error occured.");
    }

    fclose(img);
    fclose(inputfile);
}