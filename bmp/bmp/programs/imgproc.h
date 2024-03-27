#include "bmp.h"

BMP_Image* IM_EdgeDetection(BMP_Image *image);
void BMP_BWFunc(Pixel *pixel);
void BMP_ForEachPixel(BMP_Image *image, void (*pixfunc)(Pixel*));
void BMP_BlackWhite(BMP_Image *image);
int convolution(BMP_Image *image, int kernel[3][3], int row, int col);
void BMP_SetBWPixel(BMP_Image *image, int i, int j, uint8_t val);