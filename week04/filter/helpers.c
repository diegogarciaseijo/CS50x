#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed + 1) / 3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = temp.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = temp.rgbtGreen;
            image[i][width - j - 1].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Use a copy so modified pixels don't affect neighboring calculations
    RGBTRIPLE copy[height][width];
    int averageBlue = 0;
    int averageGreen = 0;
    int averageRed = 0;
    int validpixels = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di >= 0 && i + di <= height - 1 && j + dj >= 0 && j + dj <= width - 1)
                    {
                        averageBlue += image[i + di][j + dj].rgbtBlue;
                        averageGreen += image[i + di][j + dj].rgbtGreen;
                        averageRed += image[i + di][j + dj].rgbtRed;
                        validpixels++;
                    }
                }
            }
            copy[i][j].rgbtBlue = (averageBlue + validpixels / 2) / validpixels;
            copy[i][j].rgbtGreen = (averageGreen + validpixels / 2) / validpixels;
            copy[i][j].rgbtRed = (averageRed + validpixels / 2) / validpixels;
            averageBlue = 0;
            averageGreen = 0;
            averageRed = 0;
            validpixels = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // Sobel kernels for detecting horizontal and vertical edges
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int GxBlue = 0;
    int GxGreen = 0;
    int GxRed = 0;
    int GyBlue = 0;
    int GyGreen = 0;
    int GyRed = 0;
    int result = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di >= 0 && i + di <= height - 1 && j + dj >= 0 && j + dj <= width - 1)
                    {
                        GxBlue += Gx[di + 1][dj + 1] * image[i + di][j + dj].rgbtBlue;
                        GxGreen += Gx[di + 1][dj + 1] * image[i + di][j + dj].rgbtGreen;
                        GxRed += Gx[di + 1][dj + 1] * image[i + di][j + dj].rgbtRed;
                        GyBlue += Gy[di + 1][dj + 1] * image[i + di][j + dj].rgbtBlue;
                        GyGreen += Gy[di + 1][dj + 1] * image[i + di][j + dj].rgbtGreen;
                        GyRed += Gy[di + 1][dj + 1] * image[i + di][j + dj].rgbtRed;
                    }
                }
            }
            result = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            if (result < 255)
            {
                copy[i][j].rgbtBlue = result;
            }
            else
            {
                copy[i][j].rgbtBlue = 255;
            }
            result = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            if (result < 255)
            {
                copy[i][j].rgbtGreen = result;
            }
            else
            {
                copy[i][j].rgbtGreen = 255;
            }
            result = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            if (result < 255)
            {
                copy[i][j].rgbtRed = result;
            }
            else
            {
                copy[i][j].rgbtRed = 255;
            }
            GxBlue = 0;
            GxGreen = 0;
            GxRed = 0;
            GyBlue = 0;
            GyGreen = 0;
            GyRed = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    return;
}
