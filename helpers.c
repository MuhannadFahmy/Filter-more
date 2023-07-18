#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            (image[i][j].rgbtBlue = (image[i][j].rgbtRed = (image[i][j].rgbtGreen = grey)));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) // there is a more efficient way but it will require changing the structure of the given project and will not allowing submitting it
{
    RGBTRIPLE copy;
    for (int i = 0; i < height; i++) // in one loop
    {
        for (int j = 0; j < width/2; j++)
        {
            copy = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = copy;
        }
    }
    return;
}

RGBTRIPLE sum(int countY, int countX, int height, int width, RGBTRIPLE image[height][width])
{
    double red = 0, blue = 0, green = 0;
    RGBTRIPLE blur;
    double count = 0;

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if (countY + i < 0)  i++;
            if (countX + j < 0)  j++;
            if(countY + i < height && countX + j < width)
            {
                blue += image[countY + i][countX + j].rgbtBlue;
                green += image[countY + i][countX + j].rgbtGreen;
                red += image[countY + i][countX + j].rgbtRed;
                count++;
            }
        }
    }
    blur.rgbtBlue = round(blue/count);
    blur.rgbtRed = round(red/count);
    blur.rgbtGreen = round(green/count);

    return blur;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur[height][width];
    for (int i = 0; i < height; i++) // in one loop
    {
        for (int j = 0; j < width; j++)
        {
            blur[i][j] = sum(i,j,height, width,image);
        }
    }

    for (int i = 0; i < height; i++) // in one loop
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blur[i][j];
        }
    }
    return;
}

RGBTRIPLE edgee(int countY, int countX, int height, int width, RGBTRIPLE image[height][width])
{
    double red[3] = {0,0,0}, blue[3] = {0,0,0}, green[3] = {0,0,0}; //0 gx, 1 gy, 2 g
    double g=0;
    RGBTRIPLE edge;
    //double count = 0;

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(countY + i < 0)  i++;
            if(countX + j < 0)  j++;
            if(countY + i < height && countX + j < width)
            {
                if(i == 0)
                {
                    blue[0] += (2*j*image[countY + i][countX + j].rgbtBlue);
                    green[0] += (2*j*image[countY + i][countX + j].rgbtGreen);
                    red [0] += (2*j*image[countY + i][countX + j].rgbtRed);
                }
                else
                {
                    blue[0] += (j*image[countY + i][countX + j].rgbtBlue);
                    green[0] += (j*image[countY + i][countX + j].rgbtGreen);
                    red [0] += (j*image[countY + i][countX + j].rgbtRed);
                }

                if(j == 0)
                {
                    blue[1] += (2*i*image[countY + i][countX + j].rgbtBlue);
                    green[1] += (2*i*image[countY + i][countX + j].rgbtGreen);
                    red [1] += (2*i*image[countY + i][countX + j].rgbtRed);
                }
                else
                {
                    blue[1] += (i*image[countY + i][countX + j].rgbtBlue);
                    green[1] += (i*image[countY + i][countX + j].rgbtGreen);
                    red [1] += (i*image[countY + i][countX + j].rgbtRed);
                }
            }
        }
    }

    edge.rgbtBlue = ((sqrt(pow(blue[0] , 2) + pow(blue[1] , 2))) > 255) ? 255 : round((sqrt(pow(blue[0] , 2) + pow(blue[1] , 2))));
    edge.rgbtRed = ((sqrt(pow(red[0] , 2) + pow(red[1] , 2))) > 255) ? 255 : round((sqrt(pow(red[0] , 2) + pow(red[1] , 2))));
    edge.rgbtGreen = ((sqrt(pow(green[0] , 2) + pow(green[1] , 2))) > 255) ? 255 : round((sqrt(pow(green[0] , 2) + pow(green[1] , 2))));
    return edge;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edge[height][width];
    for (int i = 0; i < height; i++) // in one loop
    {
        for (int j = 0; j < width; j++)
        {
            edge[i][j] = edgee(i,j,height, width,image);
        }
    }

    for (int i = 0; i < height; i++) // in one loop
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edge[i][j];
        }
    }
    return;
    return;
}
