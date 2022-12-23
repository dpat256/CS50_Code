#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
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
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][width - j];
            image[i][width - j] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redAvg = 0;
            int greenAvg = 0;
            int blueAvg = 0;
            int lowerHBound = i - 1;
            int lowerWBound = j - 1;
            int upperHBound = i + 1;
            int upperWBound = j + 1;
            int avgCount = 0;

            if (i < 1)
            {
                lowerHBound = i;
            }
            else if (upperHBound == height)
            {
                upperHBound = i;
            }
            if (j < 1)
            {
                lowerWBound = j;
            }
            else if (upperWBound == width)
            {
                upperWBound = j;
            }
            while (lowerHBound <= upperHBound)
            {
                for (int k = lowerWBound; k <= upperWBound; k++)
                {
                    redAvg += image[lowerHBound][k].rgbtRed;
                    greenAvg += image[lowerHBound][k].rgbtGreen;
                    blueAvg += image[lowerHBound][k].rgbtBlue;
                    avgCount++;
                }
                lowerHBound++;
            }
            redAvg = redAvg / avgCount;
            greenAvg = greenAvg / avgCount;
            blueAvg = blueAvg / avgCount;
            image[i][j].rgbtRed = redAvg;
            image[i][j].rgbtGreen = greenAvg;
            image[i][j].rgbtBlue = blueAvg;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{   RGBTRIPLE edge [height][width];
    int GxKernel [3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int GyKernel [3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            int lowerHBound = i - 1;
            int lowerWBound = j - 1;
            int upperHBound = i + 1;
            int upperWBound = j + 1;
            int GxRed [3][3] = 
            {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            int GxGreen [3][3] =
            {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            int GxBlue [3][3] =
            {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            int GyRed [3][3] =
            {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            int GyGreen [3][3] = 
            {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            int GyBlue [3][3] =
            {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            int GxRedSum = 0;
            int GxGreenSum = 0;
            int GxBlueSum = 0;
            int GyRedSum = 0;
            int GyGreenSum = 0;
            int GyBlueSum = 0;
            int rLower = 0;
            int rUpper = 2;
            int cLower = 0;
            int cUpper = 2;
            int redFinal = 0;
            int greenFinal = 0;
            int blueFinal = 0;
            int tempCount = 0;
            
            if (i < 1)
            {
                lowerHBound = i;
                rLower = 1;
            }
            else if (upperHBound == height)
            {
                upperHBound = i;
                rUpper = 1;
                
            }
            if (j < 1)
            {
                lowerWBound = j;
                cLower = 1;
                tempCount = cLower;
            }
            else if (upperWBound == width)
            {
                upperWBound = j;
                cUpper = 1;
            }
            while (lowerHBound <= upperHBound && rLower <= rUpper)
            {
                for (int k = lowerWBound; k <= upperWBound && cLower <= cUpper; k++)
                {
                    GxRed [rLower][cLower] = image[lowerHBound][k].rgbtRed;
                    GyRed [rLower][cLower] = image[lowerHBound][k].rgbtRed;
                    GxGreen [rLower][cLower] = image[lowerHBound][k].rgbtGreen;
                    GyGreen [rLower][cLower] = image[lowerHBound][k].rgbtGreen;
                    GxBlue [rLower][cLower] = image[lowerHBound][k].rgbtBlue;
                    GyBlue [rLower][cLower] = image[lowerHBound][k].rgbtBlue;
                    cLower++;
                }
                rLower++;
                cLower = tempCount;
                lowerHBound++;
            }
            for(int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    GxRed[x][y] *= GxKernel[x][y];
                    GxGreen[x][y] *= GxKernel[x][y];
                    GxBlue[x][y] *= GxKernel[x][y];
                    GyRed[x][y] *= GyKernel[x][y];
                    GyGreen[x][y] *= GyKernel[x][y];
                    GyBlue[x][y] *= GyKernel[x][y];
                }
            }
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    GxRedSum += GxRed[x][y];
                    GyRedSum += GyRed[x][y];
                    GxGreenSum += GxGreen[x][y];
                    GyGreenSum += GyGreen[x][y];
                    GxBlueSum += GxBlue[x][y];
                    GyBlueSum += GyBlue[x][y];
                }
            }
            redFinal = (int)round(sqrt(pow(GxRedSum, 2) + pow(GyRedSum, 2)));
            greenFinal = (int)round(sqrt(pow(GxGreenSum, 2) + pow(GyGreenSum, 2)));
            blueFinal = (int)round(sqrt(pow(GxBlueSum, 2) + pow(GyBlueSum, 2)));
            if (redFinal > 255)
            {
                redFinal = 255;
            }
            if (greenFinal > 255)
            {
                greenFinal = 255;
            }
            if (blueFinal > 255)
            {
                blueFinal = 255;
            }
            edge[i][j].rgbtRed = redFinal;
            edge[i][j].rgbtGreen = greenFinal;
            edge[i][j].rgbtBlue = blueFinal;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edge[i][j];
        }
    }
    return;
}
