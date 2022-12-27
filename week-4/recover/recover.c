#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Get correct number of inputs
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    char *fname = argv[1];
    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE *buffer = malloc(sizeof(BYTE) * 512);

    const int BLOCK_SIZE = 512;
    int cur_file = -1;
    char *foutname = malloc(sizeof(char) * 9);
    // foutptr starts as temporary file 00-1.jpg to store garbage at start of file. removed at end.
    FILE *foutptr = fopen("00-1.jpg", "w");

    while (fread(buffer, 1, BLOCK_SIZE, fptr) == BLOCK_SIZE)
    {

        // detect start of JPEG
        if (*buffer == 0xff && *(buffer + 1) == 0xd8 && *(buffer + 2) == 0xff && (*(buffer + 3) >= 0xe0 && *(buffer + 3) <= 0xef))
        {
            fclose(foutptr);
            cur_file++;

            if (cur_file < 10)
            {
                sprintf(foutname, "00%i.jpg", cur_file);
            }
            else if (cur_file < 100)
            {
                sprintf(foutname, "0%i.jpg", cur_file);
            }
            else
            {
                sprintf(foutname, "%i.jpg", cur_file);
            }

            // Create output file
            foutptr = fopen(foutname, "w");
            if (foutptr == NULL)
            {
                fclose(fptr);
                printf("Could not create %s.\n", foutname);
                return 1;
            }
        }

        if (foutptr != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, foutptr);
        }
    }
    free(foutname);
    free(buffer);
    free(foutptr);
    fclose(fptr);
    remove("00-1.jpg");
}
