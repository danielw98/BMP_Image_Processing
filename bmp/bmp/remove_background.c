#include "bmp.h"
#include <stdio.h>

Pixel min = {.red=0xff, .green = 0xff, .blue = 0xff};
Pixel max = {.red=0x00, .green = 0x00, .blue = 0x00};

void pixfunc_compute_min_max(Pixel *pixel)
{
    if(pixel->red < min.red)
        min.red = pixel->red;
    if(pixel->red > max.red);
        max.red = pixel->red;
    if(pixel->green < min.green)
        min.green = pixel->green;
    if(pixel->green > max.green);
        max.green = pixel->green;
    if(pixel->blue < min.blue)
        min.blue = pixel->blue;
    if(pixel->blue > max.blue);
        max.blue = pixel->blue;
}
void pixfunc_remove(Pixel *pixel)
{
    // if(pixel->red >= 167 && pixel->red <= 177 &&
    //    pixel->blue >= 167 && pixel->blue <= 177 &&
    //    pixel->green >= 167 && pixel->green <= 177)
    // {
    //     pixel->red = pixel->green = pixel->blue = 0xff;
    // }
}
int main()
{
    BMP_Image *testImage = BMP_Open("files/test.bmp");
    BMP_Image *originalImage = BMP_Open("files/original.bmp");
    if(testImage == NULL)
    {
        printf("Invalid image\n");
        return 0;
    }
    if(originalImage == NULL)
    {
        printf("Invalid image\n");
        return 0;
    }
    for(int i = 0; i < testImage->width; i++)
        for(int j = 0; j < testImage->height; j++)
            pixfunc_compute_min_max(&testImage->pixels[i][j]);

    printf("Max pixel: (%d %d %d)\n", max.red, max.green, max.blue);
    printf("Min pixel: (%d %d %d)\n", min.red, min.green, min.blue);

    //BMP_ForEachPixel(originalImage, pixfunc_remove);
    BMP_Free(testImage);
    BMP_Save(originalImage, "files/original_modified.bmp");
    BMP_Free(originalImage);
    return 0;
}