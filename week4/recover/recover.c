#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open forensic image
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    FILE *output = NULL;
    char filename[8];
    int file_count = 0;

    // Read the image one 512-byte block at a time
    while (fread(buffer, 1, 512, input) == 512)
    {
        // Check for JPEG signature
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous JPEG
            if (output != NULL)
            {
                fclose(output);
            }

            // Create a new filename
            sprintf(filename, "%03i.jpg", file_count);

            output = fopen(filename, "w");

            if (output == NULL)
            {
                fclose(input);
                return 1;
            }

            file_count++;
        }

        // Write block if a JPEG file is open
        if (output != NULL)
        {
            fwrite(buffer, 1, 512, output);
        }
    }

    // Close remaining files
    if (output != NULL)
    {
        fclose(output);
    }

    fclose(input);

    return 0;
}
