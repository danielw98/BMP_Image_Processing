#include "bmp.h"


int main()
{

    BMP_Image *im = BMP_Open("saved.bmp");

    BMP_Image *red = BMP_Crop(im,0,0,im->width/2,im->height/2);
    BMP_Save(red,"saved_red.bmp");
    BMP_Image *blue = BMP_Crop(im,0,im->width/2,im->width/2,im->height/2);
    BMP_Save(blue,"saved_blue.bmp");
    BMP_Image *green = BMP_Crop(im,im->height/2,0,im->width/2,im->height/2);
    BMP_Save(green,"saved_green.bmp");
    BMP_Image *white = BMP_Crop(im,im->height/2,im->width/2,im->width/2,im->height/2);
    BMP_Save(white,"saved_white.bmp");
    /*
    if(i < h/2  && j  < w/2)
        image->pixels[i][j] = COLOR_RED;
    if(i < h/2  && j >= w/2)
        image->pixels[i][j] = COLOR_BLUE;
    if(i >= h/2 && j  < w/2)
        image->pixels[i][j] = COLOR_GREEN;
    if(i >= h/2 && j >= w/2)
        image->pixels[i][j] = COLOR_WHITE;
    */
}