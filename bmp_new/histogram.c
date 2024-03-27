#include "bmp.h"
#include "bmpstruct.h"
#include <string.h>
#include <stdlib.h>

#define PRINT_WIDTH 80
#define FORMFEED ’\014’
#define GRAY_LEVELS 255

static void zero_histogram(unsigned long histogram[], int gray_levels)
{
    memset(histogram,0,gray_levels*sizeof(unsigned long));
} 

void calculate_histogram(BMP_Image *image, unsigned long histogram[])
{
    long i,j;
    Pixel pixel;
    int width, height;
    
    width = image->width;
    height = image->height;

    BMP_BlackWhite(image);
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            pixel = image->pixels[i][j];
            histogram[pixel.red]++;
        }
    }
}


void smooth_histogram(unsigned long histogram[], int gray_levels)
{
    int i;
    unsigned long new_hist[GRAY_LEVELS+1];
    zero_histogram(new_hist, gray_levels);
    new_hist[0] = (histogram[0] + histogram[1])/2;
    new_hist[gray_levels] = (histogram[gray_levels] + histogram[gray_levels-1])/2;
    for(i = 1; i < gray_levels-1; i++)
    {
        new_hist[i] = (histogram[i-1] + histogram[i] + histogram[i+1])/3;
    }
    for(i = 0; i < gray_levels; i++)
        histogram[i] = new_hist[i];
}

void perform_histogram_equalization(BMP_Image *image, unsigned long histogram[], int gray_levels, int new_grays)
{
    int i, j, k;
    unsigned long sum, sum_of_h[GRAY_LEVELS+1];
    int width = image->width;
    int height = image->height;
    double constant;

    sum = 0;
    for(i = 0; i < gray_levels; i++)
    {
        sum = sum + histogram[i];
        sum_of_h[i] = sum;
    }
    
    constant = (float)(new_grays)/(float)(height*width);
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            k = image->pixels[i][j].red;
            image->pixels[i][j].red = 
            image->pixels[i][j].green = 
            image->pixels[i][j].blue = 
            sum_of_h[k] * constant;
        }
    }
}


static void hist_long_clear_buffer(char string[])
{
    int i;
    for(i = 0; i < 300; i++)
        string[i] = '\0';
}
