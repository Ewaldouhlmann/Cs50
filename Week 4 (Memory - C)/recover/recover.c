#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char filename[512];

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card and create a buffer, starting a img with NULL
    FILE *card = fopen(argv[1], "r");
    uint8_t buffer[512];
    int jpeg_counter = 0;
    FILE *img = NULL;
    while (fread(buffer, 1, 512, card) == 512)
    {
        /*Checking if is a start of new JPEG*/
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            /*Creating a sprintf for current jpeg*/
            sprintf(filename, "%03i.jpg", jpeg_counter);
            /*Checking if is the first JPEG file and writing a new one*/
            if (jpeg_counter == 0)
            {
                img = fopen(filename, "w");
            }
            /*If isn't the first JPEG, close the last one and creating a new*/
            else
            {
                fclose(img);
                img = fopen(filename, "w");
            }
            fwrite(buffer, 1, 512, img);
            jpeg_counter++;
        }
        else
        {
            /*Checking if the jpeg_counter is greater than 0, and writting if it is*/
            if (jpeg_counter > 0 && img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }

    /*Closing the last image (if have one) and the card*/
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}
