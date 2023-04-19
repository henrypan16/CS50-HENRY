#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        return 1;
    }
    int count = 1;
    FILE *file = fopen(argv[1], "r");
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        char name[9];
        sprintf(name, "%00i.jpg", count);
        FILE *pic = fopen(name, "w");
        fwrite(buffer, 1, BLOCK_SIZE, pic);
        fclose(pic);
        count++;
    }

    fclose(file);

    return 0;
}