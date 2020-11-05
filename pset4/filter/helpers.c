#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // variables for calculating the mean
    float media;

    // Apply the gray scale filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating the average
            media = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.000);

            //checking if the average of each tone is negative
            if (media < 0)
            {
                media = 0;
            }

            //verifying that each tone has exceeded the 8-bit limit
            if (media > 255)
            {
                media = 255;
            }

            //applying the pixel gray scale tone
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtRed = media;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // variables for calculating the mean
    int blue, green, red, sepiaBlue, sepiaGreen, sepiaRed = 0;

    // Apply the gray scale filter
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, x = width; j < x; j++)
        {
            //getting the current tone of each pixel
            blue    = image[i][j].rgbtBlue;
            green   = image[i][j].rgbtGreen;
            red     = image[i][j].rgbtRed;

            //calculating the sepia tone
            sepiaRed    = round(.393 * red + .769 * green + .189 * blue);

            sepiaGreen  = round(.349 * red + .686 * green + .168 * blue);

            sepiaBlue   = round(.272 * red + .534 * green + .131 * blue);

            //checking if each tone is negative
            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }

            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }

            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }

            //checking that each tone has exceeded the 8-bit limit
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //applying the pixel gray scale tone
            image[i][j].rgbtBlue    = sepiaBlue;
            image[i][j].rgbtGreen   = sepiaGreen;
            image[i][j].rgbtRed     = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary variables
    int tempBlue    = 0;
    int tempGreen   = 0;
    int tempRed     = 0;

    //Apply the filter to the copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            tempBlue    = image[i][j].rgbtBlue;
            tempGreen   = image[i][j].rgbtGreen;
            tempRed     = image[i][j].rgbtRed;

            image[i][j].rgbtBlue    = image[i][(width - 1) - j].rgbtBlue;
            image[i][j].rgbtGreen   = image[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtRed     = image[i][(width - 1) - j].rgbtRed;

            image[i][(width - 1) - j].rgbtBlue  = tempBlue;
            image[i][(width - 1) - j].rgbtGreen = tempGreen;
            image[i][(width - 1) - j].rgbtRed   = tempRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //variable for calculating the mean of neighboring values
    int sBlue, sGreen, sRed;
    int average_blue, average_green, average_red;
    float count;

    //temporary array
    RGBTRIPLE temp[height][width];

    // sweeps the entire image and applies the rule to the blur filter
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sBlue           = 0;
            sGreen          = 0;
            sRed            = 0;
            count           = 0.00;
            average_blue    = 0;
            average_green   = 0;
            average_red     = 0;

            // calculates the average by adding the pixel in the neighbors
            for (int x = -1; x < 2; x++)
            {
                //ignores the neighboring pixel neighbors (height)
                if (j + x < 0 || j + x > height - 1)
                {
                    continue;
                }

                //calculates the average by adding the pixel in the neighbors
                for (int y = -1; y < 2; y++)
                {
                    //ignores the pixel neighbors of the edges (width)
                    if (i + y < 0 || i + y > width - 1)
                    {
                        continue;
                    }

                    sBlue     += image[j + x][i + y].rgbtBlue;
                    sGreen    += image[j + x][i + y].rgbtGreen;
                    sRed      += image[j + x][i + y].rgbtRed;
                    count++;
                }
            }

            average_blue    = round(sBlue / count);
            average_green   = round(sGreen / count);
            average_red     = round(sRed / count);

            //checking if each tone is negative
            if (average_blue < 0)
            {
                average_blue = 0;
            }

            if (average_green < 0)
            {
                average_green = 0;
            }

            if (average_red < 0)
            {
                average_red = 0;
            }

            // checking that each tone has exceeded the 8-bit limit
            if (average_blue > 255)
            {
                average_blue = 255;
            }

            if (average_green > 255)
            {
                average_green = 255;
            }

            if (average_red > 255)
            {
                average_red = 255;
            }

            // fills the temporary table with the blotting calculation
            temp[j][i].rgbtBlue     = average_blue;
            temp[j][i].rgbtGreen    = average_green;
            temp[j][i].rgbtRed      = average_red;
        }
    }

    // transfers the values from the temporary table to the original table
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            image[h][w].rgbtBlue    = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen   = temp[h][w].rgbtGreen;
            image[h][w].rgbtRed     = temp[h][w].rgbtRed;
        }
    }
}