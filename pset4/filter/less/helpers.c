#include "helpers.h"
// Including some header files
#include <math.h>
#include <stdint.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;

    // Simple 2 layer for loop to access 2D image array
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // Simple average calculation
            // I first change the colour values into floats before dividing them and then rounding them off
            average = round((float)(image[a][b].rgbtRed + image[a][b].rgbtGreen + image[a][b].rgbtBlue) / 3);

            // Changing the pixel colour values to the new averages
            image[a][b].rgbtRed = average;
            image[a][b].rgbtGreen = average;
            image[a][b].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int new_red, new_green, new_blue;

            new_red = round((float)((.393 * image[a][b].rgbtRed) + (.769 * image[a][b].rgbtGreen) + (.189 * image[a][b].rgbtBlue)));
            new_green = round((float)((.349 * image[a][b].rgbtRed) + (.686 * image[a][b].rgbtGreen) + (.168 * image[a][b].rgbtBlue)));
            new_blue = round((float)((.272 * image[a][b].rgbtRed) + (.534 * image[a][b].rgbtGreen) + (.131 * image[a][b].rgbtBlue)));

            // if checks to see if any colour values are over 255
            if (new_red > 255)
            {
                new_red = 255;
            }
            if (new_green > 255)
            {
                new_green = 255;
            }
            if (new_blue > 255)
            {
                new_blue = 255;
            }

            image[a][b].rgbtRed = new_red;
            image[a][b].rgbtGreen = new_green;
            image[a][b].rgbtBlue = new_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // I decided that a new struct is the simplest way to store the new reflected pixels before rewriting them into the image array
    typedef struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    }
    reflected;

    reflected ref_img[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            ref_img[a][b].red = image[a][(width - 1) - b].rgbtRed;
            ref_img[a][b].green = image[a][(width - 1) - b].rgbtGreen;
            ref_img[a][b].blue = image[a][(width - 1) - b].rgbtBlue;
        }
    }

    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            image[c][d].rgbtRed = ref_img[c][d].red;
            image[c][d].rgbtGreen = ref_img[c][d].green;
            image[c][d].rgbtBlue = ref_img[c][d].blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    }
    blurs;

    blurs blur[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // All the edge cases are accounted for in these different if checks
            if (a == 0 && b == 0)
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b +
                                                1].rgbtRed)) / 4);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b +
                                                  1].rgbtGreen)) / 4);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b +
                                                 1].rgbtBlue)) / 4);
            }
            else if (a == 0 && b != 0 && b != (width - 1))
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b +
                                                1].rgbtRed + image[a][b - 1].rgbtRed + image[a + 1][b - 1].rgbtRed)) / 6);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b +
                                                  1].rgbtGreen + image[a][b - 1].rgbtGreen + image[a + 1][b - 1].rgbtGreen)) / 6);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b +
                                                 1].rgbtBlue + image[a][b - 1].rgbtBlue + image[a + 1][b - 1].rgbtBlue)) / 6);
            }
            else if (b == 0 && a != 0 && a != (height - 1))
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b +
                                                1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed)) / 6);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b +
                                                  1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen)) / 6);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b +
                                                 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue)) / 6);
            }
            else if (a == (height - 1) && b == 0)
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b +
                                                1].rgbtRed)) / 4);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b +
                                                  1].rgbtGreen)) / 4);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b +
                                                 1].rgbtBlue)) / 4);
            }
            else if (a == (height - 1) && b == (width - 1))
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b -
                                                1].rgbtRed)) / 4);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b -
                                                  1].rgbtGreen)) / 4);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b -
                                                 1].rgbtBlue)) / 4);
            }
            else if (a == 0 && b == (width - 1))
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b -
                                                1].rgbtRed)) / 4);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b -
                                                  1].rgbtGreen)) / 4);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b -
                                                 1].rgbtBlue)) / 4);
            }
            else if (b == (width - 1) && a != 0 && a != (height - 1))
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b -
                                                1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b - 1].rgbtRed)) / 6);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b -
                                                  1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b - 1].rgbtGreen)) / 6);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b -
                                                 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b - 1].rgbtBlue)) / 6);
            }
            else if (a == (height - 1) && b != 0 && b != (width - 1))
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a][b + 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b +
                                                1].rgbtRed + image[a][b - 1].rgbtRed + image[a - 1][b - 1].rgbtRed)) / 6);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b +
                                                  1].rgbtGreen + image[a][b - 1].rgbtGreen + image[a - 1][b - 1].rgbtGreen)) / 6);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b +
                                                 1].rgbtBlue + image[a][b - 1].rgbtBlue + image[a - 1][b - 1].rgbtBlue)) / 6);
            }
            // This is simply for pixels that aren't an edge case
            else
            {
                blur[a][b].red = round(((float)(image[a][b].rgbtRed + image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b +
                                                1].rgbtRed + image[a][b - 1].rgbtRed + image[a][b + 1].rgbtRed + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a +
                                                        1][b + 1].rgbtRed)) / 9);
                blur[a][b].green = round(((float)(image[a][b].rgbtGreen + image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b
                                                  + 1].rgbtGreen + image[a][b - 1].rgbtGreen + image[a][b + 1].rgbtGreen + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen +
                                                  image[a + 1][b + 1].rgbtGreen)) / 9);
                blur[a][b].blue = round(((float)(image[a][b].rgbtBlue + image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b +
                                                 1].rgbtBlue + image[a][b - 1].rgbtBlue + image[a][b + 1].rgbtBlue + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue +
                                                 image[a + 1][b + 1].rgbtBlue)) / 9);
            }
        }
    }

    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            image[c][d].rgbtRed = blur[c][d].red;
            image[c][d].rgbtGreen = blur[c][d].green;
            image[c][d].rgbtBlue = blur[c][d].blue;
        }
    }
    return;
}