#include "imgproc.h"

void BMP_BWFunc(Pixel *pixel)
{
    int sum = pixel->red + pixel->green + pixel->blue;
    sum /= 3;
    pixel->red = pixel->green = pixel->blue = sum;
}
void BMP_ForEachPixel(BMP_Image *image, void (*pixfunc)(Pixel*))
{
    int i, j;
    for(i = 0; i < image->height; i++)
        for(j = 0; j < image->width; j++)
            pixfunc(&image->pixels[i][j]);
}

void BMP_BlackWhite(BMP_Image *image)
{
    BMP_ForEachPixel(image,BMP_BWFunc);
}
int convolution(BMP_Image *image, int kernel[3][3], int row, int col) 
{
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) 
		for (j = 0; j < 3; j++)
			sum += image->pixels[i+row][j+col].red * kernel[i][j];
	return sum;
}

void BMP_SetBWPixel(BMP_Image *image, int i, int j, uint8_t val)
{
    image->pixels[i][j].red = 
    image->pixels[i][j].green =
    image->pixels[i][j].blue = val;
}
void BMP_DetectEdges(BMP_Image *image, float threshold)
{
    
	int edges_X[3][3] = {{-1, 0, 1},
                         {-1, 0, 1},
                         {-1, 0, 1}};
	int edges_Y[3][3] = {{-1, -1, -1},
                         { 0, 0, 0},
                         { 1, 1, 1}};
	int i, j, gx, gy;

    int **matrix = (int**) malloc(image->height*sizeof(int*));
    for(i = 0; i < image->height; i++)
        matrix[i] = (int*) malloc(image->width*sizeof(int));

    int average = 0;
	for (i = 1; i < image->height - 2; i++) {
		for (j = 1; j < image->width; j++){
            gx = convolution(image, edges_X, i, j);
			gy = convolution(image, edges_Y, i, j);
            matrix[i][j] = gx + gy;
            average += matrix[i][j];
		}
	}
    average /= image->width * image->height;
    for (i = 1; i < image->height - 2; i++) {
		for (j = 1; j < image->width; j++){
            if(matrix[i][j] <  average)
                BMP_SetBWPixel(image,i,j,0);
            else
                BMP_SetBWPixel(image,i,j,255);

		}
	}
}

int main()
{
    BMP_Image *image = BMP_Open("programs/gabi.bmp");
    BMP_DetectEdges(image,0);
    BMP_Save(image,"gabi_edges.bmp");

}