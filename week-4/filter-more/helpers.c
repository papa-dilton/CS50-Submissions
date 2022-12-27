#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

typedef struct
{
    int16_t rgbtGreen;
    int16_t rgbtRed;
    int16_t rgbtBlue;
} LARGERGBTRIPLE;

int sobel_gx(BYTE kernel[]);
int sobel_gy(BYTE kernel[]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            const BYTE avg = round(((double)image[r][c].rgbtRed + image[r][c].rgbtGreen + image[r][c].rgbtBlue) / 3);
            image[r][c].rgbtRed = avg;
            image[r][c].rgbtGreen = avg;
            image[r][c].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < floor(width / 2); c++)
        {
            // Buffer the current pixel
            buffer.rgbtRed = image[r][c].rgbtRed;
            buffer.rgbtGreen = image[r][c].rgbtGreen;
            buffer.rgbtBlue = image[r][c].rgbtBlue;

            // Move right to left pixel
            image[r][c].rgbtRed = image[r][width - c - 1].rgbtRed;
            image[r][c].rgbtGreen = image[r][width - c - 1].rgbtGreen;
            image[r][c].rgbtBlue = image[r][width - c - 1].rgbtBlue;

            // Buffer to right pixel
            image[r][width - c - 1].rgbtRed = buffer.rgbtRed;
            image[r][width - c - 1].rgbtGreen = buffer.rgbtGreen;
            image[r][width - c - 1].rgbtBlue = buffer.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[width][height];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j].rgbtRed = image[i][j].rgbtRed;
            tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // make array of all 9 available neighbors and remove if unavailable
            int options[] = {true, true, true, true, true, true, true, true, true};
            if (r == 0)
            {
                // top
                options[0] = options[1] = options[2] = false;
            }
            else if (r == height - 1)
            {
                // bottom
                options[6] = options[7] = options[8] = false;
            }

            if (c == 0)
            {
                // left
                options[0] = options[3] = options[6] = false;
            }
            else if (c == width - 1)
            {
                // right
                options[2] = options[5] = options[8] = false;
            }

            // make a place for the new pixel to wait (not a pixel because a byte is too small)
            int red_sums = 0;
            int green_sums = 0;
            int blue_sums = 0;

            int count = 0;

            // loop through available pixels
            for (int i = 0; i < 9; i++)
            {
                if (options[i])
                {
                    const int CUR_ROW = floor(r + ((double)i / 3) - 1);
                    const int CUR_COL = c + (i % 3) - 1;

                    red_sums += tmp[CUR_ROW][CUR_COL].rgbtRed;
                    green_sums += tmp[CUR_ROW][CUR_COL].rgbtGreen;
                    blue_sums += tmp[CUR_ROW][CUR_COL].rgbtBlue;

                    count++;
                }
            }

            image[r][c].rgbtRed = round((double)red_sums / count);
            image[r][c].rgbtGreen = round((double)green_sums / count);
            image[r][c].rgbtBlue = round((double)blue_sums / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // read is a file of non-edited values to store
    RGBTRIPLE read[height][width];
    for (long i = 0; i < height; i++)
    {
        for (long j = 0; j < width; j++)
        {
            read[i][j].rgbtRed = image[i][j].rgbtRed;
            read[i][j].rgbtGreen = image[i][j].rgbtGreen;
            read[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // make array of all 9 available neighbors and remove if unavailable
            bool options[] = {true, true, true, true, true, true, true, true, true};
            if (r == 0)
            {
                // top
                options[0] = options[1] = options[2] = false;
            }
            else if (r == height - 1)
            {
                // bottom
                options[6] = options[7] = options[8] = false;
            }

            if (c == 0)
            {
                // left
                options[0] = options[3] = options[6] = false;
            }
            else if (c == width - 1)
            {
                // right
                options[2] = options[5] = options[8] = false;
            }

            // array of pixel data to input to sobel operator
            // separate into color values fpr function usage
            BYTE pixel_data_r[9];
            BYTE pixel_data_g[9];
            BYTE pixel_data_b[9];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    const int INDEX = (i * 3) + j;

                    if (options[INDEX])
                    {
                        pixel_data_r[INDEX] = read[r + i - 1][c + j - 1].rgbtRed;
                        pixel_data_g[INDEX] = read[r + i - 1][c + j - 1].rgbtGreen;
                        pixel_data_b[INDEX] = read[r + i - 1][c + j - 1].rgbtBlue;
                    }
                    else
                    {
                        pixel_data_r[INDEX] = (BYTE)0;
                        pixel_data_g[INDEX] = (BYTE)0;
                        pixel_data_b[INDEX] = (BYTE)0;
                    }
                }
            }

            LARGERGBTRIPLE sobelx;
            LARGERGBTRIPLE sobely;
            // apply sobel operatior
            sobelx.rgbtRed = sobel_gx(pixel_data_r);
            sobelx.rgbtGreen = sobel_gx(pixel_data_g);
            sobelx.rgbtBlue = sobel_gx(pixel_data_b);

            sobely.rgbtRed = sobel_gy(pixel_data_r);
            sobely.rgbtGreen = sobel_gy(pixel_data_g);
            sobely.rgbtBlue = sobel_gy(pixel_data_b);

            // in temp to later check if values are over 255
            LARGERGBTRIPLE tmp_sobel;
            tmp_sobel.rgbtRed = round(sqrt((sobelx.rgbtRed * sobelx.rgbtRed) + (sobely.rgbtRed * sobely.rgbtRed)));
            tmp_sobel.rgbtGreen = round(sqrt((sobelx.rgbtGreen * sobelx.rgbtGreen) + (sobely.rgbtGreen * sobely.rgbtGreen)));
            tmp_sobel.rgbtBlue = round(sqrt((sobelx.rgbtBlue * sobelx.rgbtBlue) + (sobely.rgbtBlue * sobely.rgbtBlue)));
            if (tmp_sobel.rgbtRed > 255)
            {
                tmp_sobel.rgbtRed = 255;
            }
            if (tmp_sobel.rgbtGreen > 255)
            {
                tmp_sobel.rgbtGreen = 255;
            }
            if (tmp_sobel.rgbtBlue > 255)
            {
                tmp_sobel.rgbtBlue = 255;
            }

            image[r][c].rgbtRed = tmp_sobel.rgbtRed;
            image[r][c].rgbtGreen = tmp_sobel.rgbtGreen;
            image[r][c].rgbtBlue = tmp_sobel.rgbtBlue;
        }
    }

    return;
}

int sobel_gx(BYTE kernel[])
{
    int sum = 0;
    sum += kernel[0] * -1;
    sum += kernel[1] * 0;
    sum += kernel[2] * 1;
    sum += kernel[3] * -2;
    sum += kernel[4] * 0;
    sum += kernel[5] * 2;
    sum += kernel[6] * -1;
    sum += kernel[7] * 0;
    sum += kernel[8] * 1;
    return sum;
}

int sobel_gy(BYTE kernel[])
{
    int sum = 0;
    sum += kernel[0] * -1;
    sum += kernel[1] * -2;
    sum += kernel[2] * -1;
    sum += kernel[3] * 0;
    sum += kernel[4] * 0;
    sum += kernel[5] * 0;
    sum += kernel[6] * 1;
    sum += kernel[7] * 2;
    sum += kernel[8] * 1;
    return sum;
}
