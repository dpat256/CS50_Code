#include <stdio.h>
#include <stdlib.h>
 
typedef u_int8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File unreadable. Exiting program.");
        return 1;
    }
    BYTE buffer[BLOCK_SIZE];
    char imgName[8];
    int imgCount = 0;
    int b = 0; 
    FILE *jpg = fopen("000.jpg", "w");

    while (fread(buffer, BLOCK_SIZE, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if(imgCount > 0)
            {
                fclose(jpg);
                if (imgCount >= 10)
                {
                    sprintf(imgName, "0%i.jpg", imgCount);
                }
                else 
                {
                    sprintf(imgName, "00%i.jpg", imgCount);
                }
                FILE *jpg = fopen(imgName, "w");
            }
            else 
            {
                b = 1;
            }
            imgCount++;
        }
        if (b == 1)
        {
            fwrite(buffer, BLOCK_SIZE, 1, jpg);
        }
    }
    fclose(file);
    fclose(jpg);
}