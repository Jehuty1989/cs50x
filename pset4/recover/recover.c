#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Using typedef for the first time. This almost creates a new definition for uint8_t called BYTE.
typedef uint8_t BYTE;

// A prototype for function to write the files. I am still trying to wrap head around pointers.
int file_write(FILE **image, FILE **outfile);

// Creation 3 global variables that will be used.
// BYTE for the data of 1 block. A block being 512 bytes of binary data.
BYTE buffer[512];
// This is the char array that will store the filename.
char filename[8];
// This int will update every time a new file is created.
int fileno = 0;

int main(int argc, char *argv[])
{
    // sprintf will fill the char filename[8] with a 3 digit buffer, %.3, as well as the current int fileno followed by ".jpg".
    sprintf(filename, "%.3i.jpg", fileno);

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *image = fopen(argv[1], "r");
    if (image == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    FILE *output = fopen(filename, "w");
    if (output == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", filename);
        return 1;
    }
    
    // Simple infinite loop
    while (1)
    {
        // Fill the buffer with 512 BYTEs of data.
        fread(&buffer, sizeof(BYTE), 512, image);
        
        // The first 4 bytes of a JPEG will always contain this data.
        // The 4th byte will always start with 0xe1-f. Instead of writing a check for each one, e.g. 0xe0 and 0xe1 etc., you can check the first 4 bytes of
        // the 8 bytes are at least 0xe using &.
        // "buffer[3] & 0xf0" will check the first 4 bytes. 0xf0 in binary is 11110000. 0xe0 in binary is 11100000. So as long as the first 4 bytes of buffer[3]
        // (0xf0 or "1111"0000) are 0xe0 or "1110"0000
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Call file_write function and send the address for image and output.
            file_write(&image, &output);
        }

        // If the end of the file is reached then break the loop.
        if (feof(image))
        {
            break;
        }
    }

    fclose(image);
}

int file_write(FILE **image, FILE **outfile)
{
    while (1)
    {
        // If file-write is called it is only because the beggining of a JPEG has been found.
        fwrite(&buffer, sizeof(BYTE), 512, *outfile);
        // Fill the buffer with a next 512 BYTEs of data.
        fread(&buffer, sizeof(BYTE), 512, *image);

        // End of file check.
        if (feof(*image))
        {
            // If feof is true the output file must still be closed.
            fclose(*outfile);
            break;
        }

        // Check to see if the start of a new JPEG has been found in the buffer.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a new JPEG is found, close the current output file.
            fclose(*outfile);
            // Add 1 to int fileno.
            fileno ++;

            // Create a new filename using sprintf and an updated fileno.
            sprintf(filename, "%.3i.jpg", fileno);

            // Create a new file to write into with the new filename.
            FILE *output = fopen(filename, "w");
            if (output == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 1;
            }
        }
    }
    return 0;
}