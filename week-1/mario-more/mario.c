#include <cs50.h>
#include <stdio.h>

void makeBlock(void);
void makeAir(void);

int main(void)
{
    int size;
    //keep getting size until acceptable
    do
    {
        size = get_int("What size pyramids would you like to have? ");
    }
    while (size < 1 || size > 8);

    //gets number of chars in a row
    const int PRINT_WIDTH = (size * 2) + 2;

    //repeat each row
    for (int i = 1; i <= size; i++)
    {
        //repeat columns side 1
        for (int j = 0; j < size; j++)
        {
            //j+i creates 45° slope
            if (j + i >= size)
            {
                makeBlock();
            }
            else
            {
                makeAir();
            }
        }

        //print space between pyramid sides
        for (int k = 0; k < 2; k++)
        {
            makeAir();
        }

        //print one more block than row number (accounts for starting at row 0)
        for (int l = 0; l < i; l++)
        {
            makeBlock();
        }

        //start new row
        printf("\n");
    }
}


void makeBlock(void)
{
    printf("#");
}

void makeAir(void)
{
    printf(" ");
}