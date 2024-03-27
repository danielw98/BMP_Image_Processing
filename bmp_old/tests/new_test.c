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
    image->pixels[image->height-1-h_pos][w_pos] = p;
}

Pixel BMP_GetPixel(BMP_Image *image, int w_pos, int h_pos)
{
    return image->pixels[h_pos][w_pos];
}
int main(int argc, char **argv)
{
    BMP_Image *image = BMP_Open("saved.bmp");
    BMP_Image *new_image = BMP_Copy(image);
    BMP_Save(new_image,"saved2.bmp");    
    
    return 0;
}