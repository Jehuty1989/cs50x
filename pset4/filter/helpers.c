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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // I created a struct to hold all the colour values to be calculated
    typedef struct
    {
        // I used a signed 32 bit integer to hold all possible calculated values
        int32_t gx_red;
        int32_t gy_red;
        int32_t final_red;
        int32_t gx_green;
        int32_t gy_green;
        int32_t final_green;
        int32_t gx_blue;
        int32_t gy_blue;
        int32_t final_blue;
    }
    edge;

    // A 2d array of the struct
    edge img_edge[height][width];

    // a 2 tier for loop to go through all the individual pixel values
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // if checks to go though all possible edge cases
            // Each if check contains the appropriate formula to calculate the correct colour values for edge detection
            if (a == 0 && b == 0)
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b + 1].rgbtRed * 2) + (image[a + 1][b].rgbtRed * 0) +
                                                 (image[a + 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b + 1].rgbtRed * 0) + (image[a + 1][b].rgbtRed * 2) +
                                                 (image[a + 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b + 1].rgbtGreen * 2) +
                                                   (image[a + 1][b].rgbtGreen * 0) + (image[a + 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b + 1].rgbtGreen * 0) +
                                                   (image[a + 1][b].rgbtGreen * 2) + (image[a + 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b + 1].rgbtBlue * 2) + (image[a + 1][b].rgbtBlue * 0) +
                                                  (image[a + 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b + 1].rgbtBlue * 0) + (image[a + 1][b].rgbtBlue * 2) +
                                                  (image[a + 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (a == 0 && b != 0 && b != (width - 1))
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * -2) + (image[a][b + 1].rgbtRed * 2) +
                                                 (image[a + 1][b - 1].rgbtRed * -1) +
                                                 (image[a + 1][b].rgbtRed * 0) + (image[a + 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * 0) + (image[a][b + 1].rgbtRed * 0) +
                                                 (image[a + 1][b - 1].rgbtRed * 1) +
                                                 (image[a + 1][b].rgbtRed * 2) + (image[a + 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * -2) +
                                                   (image[a][b + 1].rgbtGreen * 2) + (image[a + 1][b - 1].rgbtGreen * -1) +
                                                   (image[a + 1][b].rgbtGreen * 0) + (image[a + 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * 0) +
                                                   (image[a][b + 1].rgbtGreen * 0) + (image[a + 1][b - 1].rgbtGreen * 1) +
                                                   (image[a + 1][b].rgbtGreen * 2) + (image[a + 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * -2) + (image[a][b + 1].rgbtBlue * 2) +
                                                  (image[a + 1][b - 1].rgbtBlue * -1) +
                                                  (image[a + 1][b].rgbtBlue * 0) + (image[a + 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * 0) + (image[a][b + 1].rgbtBlue * 0) +
                                                  (image[a + 1][b - 1].rgbtBlue * 1) +
                                                  (image[a + 1][b].rgbtBlue * 2) + (image[a + 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (b == (width - 1) && a == 0)
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * -2) + (image[a + 1][b].rgbtRed * 0) +
                                                 (image[a + 1][b - 1].rgbtRed * -1)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * 0) + (image[a + 1][b].rgbtRed * 2) +
                                                 (image[a + 1][b - 1].rgbtRed * 1)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * -2) +
                                                   (image[a + 1][b].rgbtGreen * 0) + (image[a + 1][b - 1].rgbtGreen * -1)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * 0) +
                                                   (image[a + 1][b].rgbtGreen * 2) + (image[a + 1][b - 1].rgbtGreen * 1)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * -2) + (image[a + 1][b].rgbtBlue * 0) +
                                                  (image[a + 1][b - 1].rgbtBlue * -1)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * 0) + (image[a + 1][b].rgbtBlue * 2) +
                                                  (image[a + 1][b - 1].rgbtBlue * 1)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (b == (width - 1) && a != 0 && a != (height - 1))
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * -2) + (image[a - 1][b - 1].rgbtRed * -1) +
                                                 (image[a + 1][b - 1].rgbtRed * -1) +
                                                 (image[a + 1][b].rgbtRed * 0) + (image[a - 1][b].rgbtRed * 0)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * 0) + (image[a - 1][b - 1].rgbtRed * -1) +
                                                 (image[a + 1][b - 1].rgbtRed * 1) +
                                                 (image[a + 1][b].rgbtRed * 2) + (image[a - 1][b].rgbtRed * -2)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * -2) +
                                                   (image[a - 1][b - 1].rgbtGreen * -1) + (image[a + 1][b - 1].rgbtGreen * -1) +
                                                   (image[a + 1][b].rgbtGreen * 0) + (image[a - 1][b].rgbtGreen * 0)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * 0) +
                                                   (image[a - 1][b - 1].rgbtGreen * -1) + (image[a + 1][b - 1].rgbtGreen * 1) +
                                                   (image[a + 1][b].rgbtGreen * 2) + (image[a - 1][b].rgbtGreen * -2)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * -2) +
                                                  (image[a - 1][b - 1].rgbtBlue * -1) + (image[a + 1][b - 1].rgbtBlue * -1) +
                                                  (image[a + 1][b].rgbtBlue * 0) + (image[a - 1][b].rgbtBlue * 0)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * 0) +
                                                  (image[a - 1][b - 1].rgbtBlue * -1) + (image[a + 1][b - 1].rgbtBlue * 1) +
                                                  (image[a + 1][b].rgbtBlue * 2) + (image[a - 1][b].rgbtBlue * -2)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (b == (width - 1) && a == (height - 1))
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * 2) + (image[a - 1][b].rgbtRed * 0) +
                                                 (image[a - 1][b - 1].rgbtRed * 1)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * 0) + (image[a - 1][b].rgbtRed * 2) +
                                                 (image[a - 1][b - 1].rgbtRed * 1)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * 2) +
                                                   (image[a - 1][b].rgbtGreen * 0) + (image[a - 1][b - 1].rgbtGreen * 1)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * 0) +
                                                   (image[a - 1][b].rgbtGreen * 2) + (image[a - 1][b - 1].rgbtGreen * 1)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * 2) + (image[a - 1][b].rgbtBlue * 0) +
                                                  (image[a - 1][b - 1].rgbtBlue * 1)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * 0) + (image[a - 1][b].rgbtBlue * 2) +
                                                  (image[a - 1][b - 1].rgbtBlue * 1)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (a == (height - 1) && b != 0 && b != (width - 1))
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * -2) + (image[a - 1][b - 1].rgbtRed * -1) +
                                                 (image[a - 1][b + 1].rgbtRed * 1) +
                                                 (image[a][b + 1].rgbtRed * 2) + (image[a - 1][b].rgbtRed * 0)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b - 1].rgbtRed * 0) + (image[a - 1][b - 1].rgbtRed * -1) +
                                                 (image[a - 1][b + 1].rgbtRed * -1) +
                                                 (image[a][b + 1].rgbtRed * 0) + (image[a - 1][b].rgbtRed * -2)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * -2) +
                                                   (image[a - 1][b - 1].rgbtGreen * -1) + (image[a - 1][b + 1].rgbtGreen * 1) +
                                                   (image[a][b + 1].rgbtGreen * 2) + (image[a - 1][b].rgbtGreen * 0)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b - 1].rgbtGreen * 0) +
                                                   (image[a - 1][b - 1].rgbtGreen * -1) + (image[a - 1][b + 1].rgbtGreen * -1) +
                                                   (image[a][b + 1].rgbtGreen * 0) + (image[a - 1][b].rgbtGreen * -2)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * -2) +
                                                  (image[a - 1][b - 1].rgbtBlue * -1) + (image[a - 1][b + 1].rgbtBlue * 1) +
                                                  (image[a][b + 1].rgbtBlue * 2) + (image[a - 1][b].rgbtBlue * 0)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b - 1].rgbtBlue * 0) +
                                                  (image[a - 1][b - 1].rgbtBlue * -1) + (image[a - 1][b + 1].rgbtBlue * -1) +
                                                  (image[a][b + 1].rgbtBlue * 0) + (image[a - 1][b].rgbtBlue * -2)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (a == (height - 1) && b == 0)
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b + 1].rgbtRed * 2) + (image[a - 1][b].rgbtRed * 0) +
                                                 (image[a - 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a][b + 1].rgbtRed * 0) + (image[a - 1][b].rgbtRed * -2) +
                                                 (image[a - 1][b + 1].rgbtRed * -1)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b + 1].rgbtGreen * 2) +
                                                   (image[a - 1][b].rgbtGreen * 0) + (image[a - 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a][b + 1].rgbtGreen * 0) +
                                                   (image[a - 1][b].rgbtGreen * -2) + (image[a - 1][b + 1].rgbtGreen * -1)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b + 1].rgbtBlue * 2) + (image[a - 1][b].rgbtBlue * 0) +
                                                  (image[a - 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a][b + 1].rgbtBlue * 0) + (image[a - 1][b].rgbtBlue * -2) +
                                                  (image[a - 1][b + 1].rgbtBlue * -1)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else if (b == 0 && a != 0 && a != (height - 1))
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a + 1][b].rgbtRed * 0) + (image[a + 1][b + 1].rgbtRed * 1) +
                                                 (image[a - 1][b + 1].rgbtRed * 1) +
                                                 (image[a][b + 1].rgbtRed * 2) + (image[a - 1][b].rgbtRed * 0)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a + 1][b].rgbtRed * 2) + (image[a + 1][b + 1].rgbtRed * 1) +
                                                 (image[a - 1][b + 1].rgbtRed * -1) +
                                                 (image[a][b + 1].rgbtRed * 0) + (image[a - 1][b].rgbtRed * -2)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a + 1][b].rgbtGreen * 0) +
                                                   (image[a + 1][b + 1].rgbtGreen * 1) + (image[a - 1][b + 1].rgbtGreen * 1) +
                                                   (image[a][b + 1].rgbtGreen * 2) + (image[a - 1][b].rgbtGreen * 0)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a + 1][b].rgbtGreen * 2) +
                                                   (image[a + 1][b + 1].rgbtGreen * 1) + (image[a - 1][b + 1].rgbtGreen * -1) +
                                                   (image[a][b + 1].rgbtGreen * 0) + (image[a - 1][b].rgbtGreen * -2)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a + 1][b].rgbtBlue * 0) +
                                                  (image[a + 1][b + 1].rgbtBlue * 1) + (image[a - 1][b + 1].rgbtBlue * 1) +
                                                  (image[a][b + 1].rgbtBlue * 2) + (image[a - 1][b].rgbtBlue * 0)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a + 1][b].rgbtBlue * 2) +
                                                  (image[a + 1][b + 1].rgbtBlue * 1) + (image[a - 1][b + 1].rgbtBlue * -1) +
                                                  (image[a][b + 1].rgbtBlue * 0) + (image[a - 1][b].rgbtBlue * -2)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
            else
            {
                img_edge[a][b].gx_red = ((float)((image[a][b].rgbtRed * 0) + (image[a - 1][b - 1].rgbtRed * -1) + (image[a - 1][b].rgbtRed * 0) +
                                                 (image[a - 1][b + 1].rgbtRed * 1)
                                                 + (image[a][b - 1].rgbtRed * -2) + (image[a][b + 1].rgbtRed * 2) + (image[a + 1][b - 1].rgbtRed * -1) +
                                                 (image[a + 1][b].rgbtRed * 0) +
                                                 (image[a + 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].gy_red = ((float)((image[a][b].rgbtRed * 0) + (image[a - 1][b - 1].rgbtRed * -1) + (image[a - 1][b].rgbtRed * -2) +
                                                 (image[a - 1][b + 1].rgbtRed * -1)
                                                 + (image[a][b - 1].rgbtRed * 0) + (image[a][b + 1].rgbtRed * 0) + (image[a + 1][b - 1].rgbtRed * 1) +
                                                 (image[a + 1][b].rgbtRed * 2) +
                                                 (image[a + 1][b + 1].rgbtRed * 1)));
                img_edge[a][b].final_red = round(sqrt((float)(pow(img_edge[a][b].gx_red, 2) + pow(img_edge[a][b].gy_red, 2))));

                img_edge[a][b].gx_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a - 1][b - 1].rgbtGreen * -1) +
                                                   (image[a - 1][b].rgbtGreen * 0) + (image[a - 1][b + 1].rgbtGreen * 1)
                                                   + (image[a][b - 1].rgbtGreen * -2) + (image[a][b + 1].rgbtGreen * 2) + (image[a + 1][b - 1].rgbtGreen * -1) +
                                                   (image[a + 1][b].rgbtGreen * 0) +
                                                   (image[a + 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].gy_green = ((float)((image[a][b].rgbtGreen * 0) + (image[a - 1][b - 1].rgbtGreen * -1) +
                                                   (image[a - 1][b].rgbtGreen * -2) + (image[a - 1][b + 1].rgbtGreen * -1)
                                                   + (image[a][b - 1].rgbtGreen * 0) + (image[a][b + 1].rgbtGreen * 0) + (image[a + 1][b - 1].rgbtGreen * 1) +
                                                   (image[a + 1][b].rgbtGreen * 2) +
                                                   (image[a + 1][b + 1].rgbtGreen * 1)));
                img_edge[a][b].final_green = round(sqrt((float)(pow(img_edge[a][b].gx_green, 2) + pow(img_edge[a][b].gy_green, 2))));

                img_edge[a][b].gx_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a - 1][b - 1].rgbtBlue * -1) +
                                                  (image[a - 1][b].rgbtBlue * 0) + (image[a - 1][b + 1].rgbtBlue * 1)
                                                  + (image[a][b - 1].rgbtBlue * -2) + (image[a][b + 1].rgbtBlue * 2) + (image[a + 1][b - 1].rgbtBlue * -1) +
                                                  (image[a + 1][b].rgbtBlue * 0) +
                                                  (image[a + 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].gy_blue = ((float)((image[a][b].rgbtBlue * 0) + (image[a - 1][b - 1].rgbtBlue * -1) +
                                                  (image[a - 1][b].rgbtBlue * -2) + (image[a - 1][b + 1].rgbtBlue * -1)
                                                  + (image[a][b - 1].rgbtBlue * 0) + (image[a][b + 1].rgbtBlue * 0) + (image[a + 1][b - 1].rgbtBlue * 1) +
                                                  (image[a + 1][b].rgbtBlue * 2) +
                                                  (image[a + 1][b + 1].rgbtBlue * 1)));
                img_edge[a][b].final_blue = round(sqrt((float)(pow(img_edge[a][b].gx_blue, 2) + pow(img_edge[a][b].gy_blue, 2))));
            }
        }
    }

    // This 2 tier for loop and individual if checks are to check if any of the pixel values are over 255 or under 0
    // I think it is impossible to have a value lower than 0 but I am not sure so I included it just in case
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            if (img_edge[c][d].final_red < 0)
            {
                img_edge[c][d].final_red = 0;
            }
            if (img_edge[c][d].final_red > 255)
            {
                img_edge[c][d].final_red = 255;
            }
            if (img_edge[c][d].final_green < 0)
            {
                img_edge[c][d].final_green = 0;
            }
            if (img_edge[c][d].final_green > 255)
            {
                img_edge[c][d].final_green = 255;
            }
            if (img_edge[c][d].final_blue < 0)
            {
                img_edge[c][d].final_blue = 0;
            }
            if (img_edge[c][d].final_blue > 255)
            {
                img_edge[c][d].final_blue = 255;
            }
        }
    }

    // Another 2 tier for loop to write the adjusted colour values to the 2d image array
    for (int e = 0; e < height; e++)
    {
        for (int f = 0; f < width; f++)
        {
            image[e][f].rgbtRed = img_edge[e][f].final_red;
            image[e][f].rgbtGreen = img_edge[e][f].final_green;
            image[e][f].rgbtBlue = img_edge[e][f].final_blue;
        }
    }
    return;
}