#include "helpers.h"
#include "math.h"

//RGBTRIPLE test(int height, int width, RGBTRIPLE image[height][width], int divisor)

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

// Variable temporary to armazen the collors

    float r = 0, g = 0, b = 0;

// Loops to check pixel by pixel

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = round((r + g + b) / 3);
            image[i][j].rgbtBlue = round((r + g + b) / 3);
            image[i][j].rgbtRed = round((r + g + b) / 3);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
// Copy of the image array
    RGBTRIPLE arr[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = image[i][j];
        }
    }
    
// Count variable to loop through image array    
    int count = 0;
    
// Loop to inverse the pixel line
    for (int i = 0; i < height; i ++)
    {
        count = 0;
        for (int h = width - 1; h > -1; h--)
        {
            image[i][count] = arr[i][h];
            count++;
        }
    }
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
// Copy the array image inside the array arr
    RGBTRIPLE arr[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = image[i][j];
        }
    }

// For loop to loop through lines
    for (int i = 0; i < height; i++)
    {
        
// Loops through columns         
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            
// Variables to amarzen the collors value            
            float r = 0, g = 0, b = 0;
            
// For to forsee edges or exceptions            
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && j + l >= 0 && i + k <= height - 1 && j + l <= width - 1)
                    {
                        r += arr[i + k][j + l].rgbtRed;
                        b += arr[i + k][j + l].rgbtBlue;
                        g += arr[i + k][j + l].rgbtGreen;
                        counter++;
                    }
                }
            }
            r = r / counter;
            b = b / counter;
            g = g / counter;
            
// Check for any uncommon value            
            if (r > 255)
            {
                r = 255;
            }
            if (r < 0)
            {
                r = 0;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (g < 0)
            {
                g = 0;
            }
            if (b > 255)
            {
                b = 255;
            }
            if (b < 0)
            {
                b = 0;
            }
            
// Change the value in image array            
            image[i][j].rgbtRed = round(r);
            image[i][j].rgbtBlue = round(b);
            image[i][j].rgbtGreen = round(g);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
// Variables used
    RGBTRIPLE arr[height][width];
    int rx = 0, gx = 0, bx = 0, count = 0;
    float r = 0, g, b = 0;
    int ry = 0, gy = 0, by = 0;
// Kernels    
    int variatorx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int variatory[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    
// Copy the image array to arr    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        { 
            for (int h = i - 1; h < i + 2; h++)
            {
                for (int k = j - 1; k < j + 2; k++)
                {
                    
// Checks for edges and prevents segfault
                    if (k != -1 && h != -1 && k < width && h < height)
                    {
// Sum the values for each collor in the 3x3 grid                        
                        rx += (arr[h][k].rgbtRed * variatorx[count]);
                        gx += (arr[h][k].rgbtGreen * variatorx[count]);
                        bx += (arr[h][k].rgbtBlue * variatorx[count]);
                        ry += (arr[h][k].rgbtRed * variatory[count]);
                        gy += (arr[h][k].rgbtGreen * variatory[count]);
                        by += (arr[h][k].rgbtBlue * variatory[count]);
                    }
                    count ++;
                }
            }
// Do the Sobel Operator            
            r = pow(rx, 2) + pow(ry, 2);
            g = pow(gx, 2) + pow(gy, 2);
            b = pow(bx, 2) + pow(by, 2);
            r = sqrtf(r);
            g = sqrtf(g);
            b = sqrtf(b);
            
// Check for uncommun results            
            if (r > 255)
            {
                r = 255;
            }
            if (r < 0)
            {
                r = 0;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (g < 0)
            {
                g = 0;
            }
            if (b > 255)
            {
                b = 255;
            }
            if (b < 0)
            {
                b = 0;
            }
// Change the pixel Value in the image array            
            image[i][j].rgbtRed = round(r);
            image[i][j].rgbtGreen = round(g);
            image[i][j].rgbtBlue = round(b);
            count = rx = gx = bx = ry = gy = by = r = g = b = 0;
        }
    }
    return;
}




