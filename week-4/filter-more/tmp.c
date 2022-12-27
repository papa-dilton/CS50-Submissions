#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "bmp.h"

typedef struct
{
    int rgbtRed;
    int rgbtGreen;
    int rgbtBlue;
}LARGERGBTRIPLE;


int sobel_gx(BYTE kernel[]);
int sobel_gy(BYTE kernel[]);
int main(void)
{
    /*if (argc != 4)
    {
        printf("Incorrect usage\n");
        return 1;
    }*/


    RGBTRIPLE a = {25, 10, 0};
    RGBTRIPLE b = {30, 10, 0};
    RGBTRIPLE j = {80, 60, 40};
    RGBTRIPLE d = {90, 30, 20};
    RGBTRIPLE e = {100, 40, 30};
    RGBTRIPLE f = {80, 70, 90};
    RGBTRIPLE g = {40, 20, 20};
    RGBTRIPLE h = {30, 10, 30};
    RGBTRIPLE i = {10, 40, 50};
    RGBTRIPLE image[] = {a, b, j, d, e, f, g, h, i};

/*
    int r = 1;
    int c = 1;
    RGBTRIPLE image[][] = {{a, b, j}, {d, e, f}, {g, h, i}};



    RGBTRIPLE AVG;
    AVG.rgbtRed =   round(((double) image[r-1][c-1].rgbtRed + image[r-1][c].rgbtRed + image[r-1][c+1].rgbtRed + image[r][c-1].rgbtRed + image[r][c].rgbtRed + image[r][c+1].rgbtRed + image[r+1][c-1].rgbtRed + image[r+1][c].rgbtRed + image[r+1][c+1].rgbtRed) / 9);
    AVG.rgbtGreen = round(((double) image[r-1][c-1].rgbtGreen + image[r-1][c].rgbtGreen + image[r-1][c+1].rgbtGreen + image[r][c-1].rgbtGreen + image[r][c].rgbtGreen + image[r][c+1].rgbtGreen + image[r+1][c-1].rgbtGreen + image[r+1][c].rgbtGreen + image[r+1][c+1].rgbtGreen) / 9);
    AVG.rgbtBlue =  round(((double) image[r-1][c-1].rgbtBlue + image[r-1][c].rgbtBlue + image[r-1][c+1].rgbtBlue + image[r][c-1].rgbtBlue + image[r][c].rgbtBlue + image[r][c+1].rgbtBlue + image[r+1][c-1].rgbtBlue + image[r+1][c].rgbtBlue + image[r+1][c+1].rgbtBlue) / 9);


    printf("Average is : %i\n", AVG.rgbtRed);


*/


BYTE pixel_data_r[9];
BYTE pixel_data_g[9];
BYTE pixel_data_b[9];

for (int q = 0; q < 9; q++)
{
    pixel_data_r[q] = image[q].rgbtRed;
    pixel_data_g[q] = image[q].rgbtGreen;
    pixel_data_b[q] = image[q].rgbtBlue;
}


LARGERGBTRIPLE sobelx;
LARGERGBTRIPLE sobely;
//apply sobel operatior
sobelx.rgbtRed = sobel_gx(pixel_data_r);
sobelx.rgbtGreen = sobel_gx(pixel_data_g);
sobelx.rgbtBlue = sobel_gx(pixel_data_b);

sobely.rgbtRed = sobel_gy(pixel_data_r);
sobely.rgbtGreen = sobel_gy(pixel_data_g);
sobely.rgbtBlue = sobel_gy(pixel_data_b);
//in temp to later check if values are over 255
LARGERGBTRIPLE tmp_sobel;
tmp_sobel.rgbtRed = round(sqrt((sobelx.rgbtRed ^ 2) + (sobely.rgbtRed ^ 2)));
tmp_sobel.rgbtGreen = round(sqrt((sobelx.rgbtGreen ^ 2) + (sobely.rgbtGreen ^ 2)));
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



printf("%i, %i, %i\n", tmp_sobel.rgbtBlue, sobelx.rgbtBlue, sobely.rgbtBlue);

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

