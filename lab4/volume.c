// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // I need to create an array of 44 1 byte ints for header to be copied into. It doesn't seem as though I can directly copy the bits from file to file
    uint8_t header_buffer[HEADER_SIZE];

    // Read the first 44 bytes of 1 byte data and write it into the header_buffer array filling each array
    fread(header_buffer, HEADER_SIZE, 1, input);

    // Write the data into FILE output from header_buffer in bulk
    fwrite(header_buffer, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    // int to store the 2 byte ints
    int16_t buffer;

    // do while loop that will only break if end of file error (feof) is reached
    do
    {
        // Cursor position remains where it left of after the first fread with header_buffer. This is useful to simply carry on reading the file where you last left off
        fread(&buffer, sizeof(int16_t), 1, input);
        // Important break to the infinite loop
        if (feof(input))
        {
            break;
        }
        // Simple maths to multiply current buffer value by factor
        buffer = buffer * factor;
        // Write the new 16 bit buffer value into FILE output
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // do while loops always start at value "1" so without an if break statement it would go on forever
    while (1);

    // Close files
    fclose(input);
    fclose(output);
}