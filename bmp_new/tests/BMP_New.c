#include "bmp.h"


#define COLOR_RED       (Pixel){.red = 255, .green =   0, .blue=   0}
#define COLOR_GREEN     (Pixel){.red =   0, .green = 255, .blue=   0}
#define COLOR_BLUE      (Pixel){.red =   0, .green =   0, .blue= 255}
#define COLOR_WHITE     (Pixel){.red = 255, .green = 255, .blue= 255}

#define RGB(x,y,z)      (Pixel){.red = x, .green = y, .blue= z}
Pixel color[2][2];
void init_pixels()
{
    color[0][0] = COLOR_RED;    color[0][1] = COLOR_GREEN;
    color[1][0] = COLOR_BLUE;   color[1][1] = COLOR_WHITE;
}


int main()
{
    init_pixels();
    int w = 200, h = 400;
    BMP_Image *image = BMP_New(w,h);
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(i < h/2  && j  < w/2)
                image->pixels[i][j] = COLOR_RED;
            if(i < h/2  && j >= w/2)
                image->pixels[i][j] = COLOR_BLUE;
            if(i >= h/2 && j  < w/2)
                image->pixels[i][j] = COLOR_GREEN;
            if(i >= h/2 && j >= w/2)
                image->pixels[i][j] = COLOR_WHITE;
        }
    }
    
    BMP_Save(image,"saved.bmp");
    return 0;
}