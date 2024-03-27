#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GRAY_LEVELS 256
#define MAX_NAME_LENGTH 255
int main(int argc, char **argv)
{
    char in_name[MAX_NAME_LENGTH];
    char out_name[MAX_NAME_LENGTH];
    char response[MAX_NAME_LENGTH];
    int i;
    long height, width;
    BMP_Image *in_image, *out_image;
    unsigned long histogram[GRAY_LEVELS+1];

    if(argc < 3)
    {
        fprintf(stderr,"usage: %s input-image output-image\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    strcpy(in_name, argv[1]);
    strcpy(out_name, argv[2]);

    in_image = BMP_Open(in_name);
    if(in_image == NULL)
    {
        fprintf(stderr, "ERROR input file %s does not exist\n", in_name);
        fprintf(stderr, "usage: %s input-image output-image\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    out_image = BMP_Copy(in_image);
    for(i = 0; i < GRAY_LEVELS+1; i++) 
        histogram[i] = 0;
    calculate_histogram(out_image, histogram);
    perform_histogram_equalization(out_image, histogram, 256, 250);
    BMP_Save(out_image,out_name);
    BMP_Free(in_image);
    BMP_Free(out_image);

    return 0;
} 