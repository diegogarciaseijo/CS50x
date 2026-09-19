#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Declaring necessary variables
    const int BUFFER_SIZE = 512;
    unsigned char buffer[BUFFER_SIZE];
    int jpeg_count = 0;
    FILE *output = NULL;
    char filename[8];
    // Checking that the user executed the program correctly
    if (argc != 2)
    {
        printf("Usage: ./recover <name>\n");
        return 1;
    }
    // Opening the input file
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
    {
        printf("Failed to open the file\n");
        return 1;
    }
    // Repeating this while there is still unread data on the file
    while (fread(buffer, sizeof(char), BUFFER_SIZE, f) == BUFFER_SIZE)
    {
        // Checking for the starting sequence
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If there was an open file it is closed
            if (output != NULL)
            {
                fclose(output);
            }
            // Creating a new file
            sprintf(filename, "%03d.jpg", jpeg_count);
            output = fopen(filename, "wb");
            if (output == NULL)
            {
                printf("Failed to open the file\n");
                fclose(f);
                return 1;
            }
            jpeg_count++;
        }
        // Writing the data on the current output file
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), BUFFER_SIZE, output);
        }
    }
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(f);
}
