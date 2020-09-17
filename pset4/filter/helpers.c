#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through all pixels (rows, cols)
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            // calculate average color value
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;

            // assign new average values to color pixels
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            // save copies of original color values
            int orgRed = image[i][j].rgbtRed;
            int orgGreen = image[i][j].rgbtGreen;
            int orgBlue = image[i][j].rgbtBlue;

            // calculate sepia values based on given formula
            int sepRed = round(0.393 * orgRed + 0.769 * orgGreen + 0.189 * orgBlue);
            int sepGreen = round(0.349 * orgRed + 0.686 * orgGreen + 0.168 * orgBlue);
            int sepBlue = round(0.272 * orgRed + 0.534 * orgGreen + 0.131 * orgBlue);

            // check if new 24 bit color values are out of range and adjust accordingly
            (sepRed >= 255) ? (image[i][j].rgbtRed = 255) : (image[i][j].rgbtRed = sepRed);
            (sepGreen >= 255) ? (image[i][j].rgbtGreen = 255) : (image[i][j].rgbtGreen = sepGreen);
            (sepBlue >= 255) ? (image[i][j].rgbtBlue = 255) : (image[i][j].rgbtBlue = sepBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width / 2 - 1; j++)
        {
            // save copies of original color values
            int orgRed = image[i][j].rgbtRed;
            int orgGreen = image[i][j].rgbtGreen;
            int orgBlue = image[i][j].rgbtBlue;

            // swap color values of opposite horizontal sides
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = orgRed;

            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = orgGreen;

            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = orgBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image to save original values
    RGBTRIPLE original[height][width];
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    // loop through all pixels (rows, cols)
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            // calculate average color value
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0;

            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= j + 1; col++)
                {
                    // check for edges and corners
                    if (row >= 0 && row <= height - 1 && col >= 0 && col <= width - 1)
                    {
                        sumRed = sumRed + original[row][col].rgbtRed;
                        sumGreen = sumGreen + original[row][col].rgbtGreen;
                        sumBlue = sumBlue + original[row][col].rgbtBlue;
                        counter++;
                    }
                }
            }

            float avgRed = sumRed / counter;
            float avgGreen = sumGreen / counter;
            float avgBlue = sumBlue / counter;

            // assign new average values to color pixels
            image[i][j].rgbtBlue = round(avgBlue);
            image[i][j].rgbtRed = round(avgRed);
            image[i][j].rgbtGreen = round(avgGreen);
        }
    }
    return;
}