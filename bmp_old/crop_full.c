#include "bmp.h"

/*
    de rezolvat... (j,i) -> (i,j) si ordinea inversa..
*/


#define COLOR_RED       (Pixel){.red = 255, .green =   0, .blue=   0}
#define COLOR_GREEN     (Pixel){.red =   0, .green = 255, .blue=   0}
#define COLOR_BLUE      (Pixel){.red =   0, .green =   0, .blue= 255}
#define COLOR_WHITE     (Pixel){.red = 255, .green = 255, .blue= 255}

Pixel color[2][2];


void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void BMP_SetPixel(BMP_Image *image, int w_pos, int h_pos, Pixel p)
{
    swap(&w_pos,&h_pos);
    image->pixels[image->height-1-h_pos][w_pos] = p;
}

Pixel BMP_GetPixel(BMP_Image *image, int w_pos, int h_pos)
{
    return image->pixels[h_pos][w_pos];
}
int main(int argc, char **argv)
{
/*
    if(argc != 2)
    {
        fprintf(stderr,"Utilizare: %s <bmp image>\n",argv[0]);
        exit(1);
    }

    BMP_Image *image = BMP_Open(argv[1]);

    //BMP_New()*/
    int w, h;
    w=h=2;
    BMP_Image *new_image = BMP_New(w,h);

    color[0][0] = COLOR_RED;
    color[0][1] = COLOR_GREEN;
    color[1][0] = COLOR_BLUE;
    color[1][1] = COLOR_WHITE;
    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
            BMP_SetPixel(new_image,i,j,color[i][j]);


    BMP_Save(new_image,"saved.bmp");
    return 0;
}