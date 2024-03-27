#include "bmp.h"

/*
    de rezolvat... (j,i) -> (i,j) si ordinea inversa..
*/


#define COLOR_RED       (Pixel){.red = 255, .green =   0, .blue=   0}
#define COLOR_GREEN     (Pixel){.red =   0, .green = 255, .blue=   0}
#define COLOR_BLUE      (Pixel){.red =   0, .green =   0, .blue= 255}
#define COLOR_WHITE     (Pixel){.red = 255, .green = 255, .blue= 255}

Pixel color[2][2];


void BMP_SetPixel(BMP_Image *image, int w_pos, int h_pos, Pixel p)
{
    image->pixels[image->height-1-w_pos][h_pos] = p;
}

Pixel BMP_GetPixel(BMP_Image *image, int w_pos, int h_pos)
{
    return image->pixels[image->height-1-w_pos][h_pos];
}

void init_pixels()
{
    color[0][0] = COLOR_RED;
    color[0][1] = COLOR_GREEN;
    color[1][0] = COLOR_BLUE;
    color[1][1] = COLOR_WHITE;
}
int main()
{
    init_pixels();
    // MERGE OK LA MATRICI PATRATICE DAR ALTFEL NU. TREBUIE SA VAD
    BMP_Image *image = BMP_New(2,2);
    int ok = 1;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            BMP_SetPixel(image,i,j,color[i][j%2]);
        }
    }
    
    BMP_Save(image,"saved.bmp");
    return 0;
}