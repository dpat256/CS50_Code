#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// This program reads an input .wav file and outputs the .wav in reserse

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int check_format(uint8_t header[]);
int get_block_size(uint8_t header[]);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    char *check = ".wav";
    int count = 3;
    for (int i = sizeof(argv[1]); i > sizeof(argv[1])-4; i--)
    {
        if(check[count] != argv[1][i])
        {
            printf("ERROR: Input file is not .wav\n");
            return 1;
        }
        count--;
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out;
    if (in == NULL) 
    {
        printf("ERROR: File Open Unsuccessful.\n");
        return 1;
    }
    uint8_t header [HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, in);
    int hpos = ftell(in);
    if (check_format(header) == 0)
    {
        out = fopen(argv[2], "w");
    }
    else
    {
        printf("ERROR: input file is not a .wav\n");
        return 1;
    }
    fwrite(header, HEADER_SIZE, 1, out);
    int BLOCK_SIZE = get_block_size(header);

    fseek(in, -BLOCK_SIZE, SEEK_END);
    uint8_t buffer [BLOCK_SIZE];
    while (fread(buffer, BLOCK_SIZE, 1, in))
    {
        if(ftell(in) >= 44)
        {
            fwrite(buffer, BLOCK_SIZE, 1, out);
            fseek(in, (BLOCK_SIZE * -2), SEEK_CUR);
        }
        else
        {
            break;
        }
    }
    fclose(in);
    fclose(out);
}

int check_format(uint8_t header[])
{
    if (header[8] == 87 && header[9] == 65 && header[10] == 86 && header[11] == 69)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(uint8_t header[])
{
    int channels = (header[23] * 256) + header[22];
    int sample = ((header[35] * 256) + header[34])/8;
    return channels * sample;
}