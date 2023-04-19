#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Store a copy of the original image
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int total[3] = {0};

            //Loop through 3x3 square around the target pixel
            for (int n = i - 1; n < i + 2; n++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    if (n >= 0 && m >= 0 && n < height && m < width)
                    {
                        //Adding the RGB value to the sum
                        total[0] += original[n][m].rgbtRed;
                        total[1] += original[n][m].rgbtGreen;
                        total[2] += original[n][m].rgbtBlue;                            
                        count++;
                    }
                }
            }

            //Calculate the average
            image[i][j].rgbtRed = round((float)total[0] / (float)count);
            image[i][j].rgbtGreen = round((float)total[1] / (float)count);
            image[i][j].rgbtBlue = round((float)total[2] / (float)count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Value for Sobel Operator
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //Store a copy of the original image
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    //Loop through every pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalGx[3] = {0};
            int totalGy[3] = {0};

            //Loop through 3x3 square around the target pixel
            for (int n = i - 1, y = 0; n < i + 2; n++, y++)
            {
                for (int m = j - 1, x = 0; m < j + 2; m++, x++)
                {
                    if (n >= 0 && m >= 00 && n < height && m < width)
                    {
                        totalGx[0] += original[n][m].rgbtRed * Gx[y][x];
                        totalGx[1] += original[n][m].rgbtGreen * Gx[y][x];
                        totalGx[2] += original[n][m].rgbtBlue * Gx[y][x];

                        totalGy[0] += original[n][m].rgbtRed * Gy[y][x];
                        totalGy[1] += original[n][m].rgbtGreen * Gy[y][x];
                        totalGy[2] += original[n][m].rgbtBlue * Gy[y][x];
                    }
                }
            }

            //Applying Sobel Operator
            int sobel[3];
            sobel[0] = round(sqrt((float)pow(totalGx[0], 2) + (float)pow(totalGy[0], 2)));
            sobel[1] = round(sqrt((float)pow(totalGx[1], 2) + (float)pow(totalGy[1], 2)));
            sobel[2] = round(sqrt((float)pow(totalGx[2], 2) + (float)pow(totalGy[2], 2)));

            //Check if the result is larger than 255
            image[i][j].rgbtRed = sobel[0] > 255 ? 255 : sobel[0];
            image[i][j].rgbtGreen = sobel[1] > 255 ? 255 : sobel[1];
            image[i][j].rgbtBlue = sobel[2] > 255 ? 255 : sobel[2];
        }
    }

    return;
}
