#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *inFile = fopen(argv[1], "r");

    if (argc != 2)
    {
        printf("./recover [File...]\n");
        return 1;
    }
    else
    {
        if (inFile == NULL)
        {
            printf("Error: cannot open %s\n", argv[1]);
            return 1;
        }
    }
    BYTE buffer[512];

    // Number of images
    int count = 0;

    FILE *outFile = NULL;
    char filename[8];
    while (fread(&buffer, 512, 1, inFile) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!(count == 0))
            {
                fclose(outFile);
            }
            // Initialise file
            sprintf(filename, "%03i.jpg", count);
            outFile = fopen(filename, "w");
            count++;
        }
        if (!(count == 0))
        {
            fwrite(&buffer, 512, 1, outFile);
        }
    }
    fclose(inFile);
    fclose(outFile);
    return 0;
}

