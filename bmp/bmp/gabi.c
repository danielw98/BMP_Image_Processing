#include "bmp.h"
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
int convolution(BMP_Image *image, int kernel[3][3], int row, int col) {

    
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) 
		for (j = 0; j < 3; j++)
        {
            uint8_t pix = image->pixels[i+row][j+col].red;
			sum += pix * kernel[i][j];
        }
	return sum;
}
void BMP_DetectEdges(BMP_Image *image, uint8_t cutoff)
{
    
	int edges_X[3][3] = {{-1,  0,  1},{-1, 0, 1},{-1, 0, 1}};
	int edges_Y[3][3] = {{-1, -1, -1},{ 0, 0, 0},{ 1, 1, 1}};
	int i, j, gx, gy;
	for (i = 1; i < image->height - 2; i++) {
		for (j = 1; j < image->width; j++){
            gx = convolution(image, edges_X, i, j);
			gy = convolution(image, edges_Y, i, j);
			image->pixels[i][j].red = 
            image->pixels[i][j].green =
            image->pixels[i][j].blue = 
            (gx+gy > cutoff ? 255 : 0);
		}
	}
}
int main(int argc, char **argv)
{
    char picture[256];
    char output_prefix[249];
    uint8_t cutoff;
    if(argc == 1){
        strcpy(picture,"gabi.bmp");
        cutoff = 95;
    }
    if(argc == 2){
        strcpy(picture,argv[1]);
        cutoff = 95;
    }
    if(argc == 3){
        strcpy(picture,argv[1]);
        cutoff = atoi(argv[2]);
    }

    BMP_Image *image = BMP_Open(picture);
    strncpy(output_prefix,picture,strlen(picture)-4);
    if(image == NULL)
        return 1;
    BMP_BlackWhite(image);
    BMP_DetectEdges(image,cutoff);

    sprintf(picture,"%s_bw.bmp",output_prefix);
    BMP_Save(image,picture);
    return 0;
}