#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    FILE *fIn = fopen(argv[1], "rb");
    FILE *fOut = fopen("Blanc&Noir.bmp", "w+");
    if (!fIn || !fOut)
    {
        printf("File error.\n");
        return 0;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fOut);

    int width = *(int*)&header[18];
    int height = abs(*(int*)&header[22]);
    int stride = (width * 3 + 3) & ~3;
    int padding = stride - width * 3;

    printf("Largeur: %d\n", width);
    printf("Hauteur: %d\n", height);
    printf("Pas (hauteur*3): %d\n", stride);
  

    unsigned char pixel[3];
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            fread(pixel, 3, 1, fIn);
                /*.......................... Grey = 70% Vert 10% Bleu et 20% Rouge.................. */
                
            unsigned char gray = pixel[0] * 0.2 + pixel[1] * 0.7 + pixel[2] * 0.1;
            memset(pixel, gray, sizeof(pixel));
            fwrite(&pixel, 3, 1, fOut);
        }
        fread(pixel, padding, 1, fIn);
        fwrite(pixel, padding, 1, fOut);
    }
    fclose(fOut);
    fclose(fIn);
    return 0;
}
