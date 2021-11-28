#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int FILENAMELENGTH =30;
int MAXROW = 512;
int MAXCOL = 512;

int main(int argc,char *argv[]){

typedef struct
{
   int row;
   int col;
}COORDI;

COORDI org;


char source[MAXROW][MAXCOL];
char dest[MAXROW][MAXCOL];


float Theta = 1.5708; /* 90 degrees en radian*/



    char original_image;
    char rotate_image;


    FILE* fp;
    int i, j;

    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("File cannot open\n");
        exit(-1);
    }


    for (i = 0; i < MAXROW; i++)
    {
        for (j = 0; j < MAXCOL; j++)
            fread(&source[i][j], sizeof(unsigned char), 1, fp);
    }

    printf("image read completed !\n");
  

void RotatePixel(float Theta, COORDI org, COORDI before, COORDI* after)
{
    int x, y;
    x = before.col - org.col;
    y = before.row - org.row;

    after->col = (int)(x* cos(Theta) - y*sin(Theta)) + org.col; 
    after->row = (int)(x* sin(Theta) + y*cos(Theta)) + org.row; 
}


  
    COORDI locn;
    COORDI* after = (COORDI*)malloc(sizeof(COORDI));

    fp = fopen("rotated_image.bmp", "w+");
    if (fp == NULL)
    {
        printf("File cannot open\n");
        exit(-1);
    }

 for (i = 0; i < MAXROW; i++)
    {
        for (j = 0; j < MAXCOL; j++)
        {
            locn.row = i;
            locn.col = j;
            RotatePixel(Theta, org, locn, after);

            if (after->col < 0) continue;
            if (after->row < 0) continue;
            if (after->col >= MAXCOL) continue;
            if (after->row >= MAXROW) continue;

            dest[after->row][after->col] = source[i][j];
            putc(dest[after->row][after->col], fp);
        }
    }



 
    fclose(fp);

 



 return(0);
}
