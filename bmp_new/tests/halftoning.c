#include "../bmp.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    BMP_Image *image;
    
    if(argc >= 2)
        image = BMP_Open(argv[1]);
    else
        image = BMP_Open("puiul.bmp");
    int threshold = 128;

    if(image == NULL){
        printf("not okay - NULL image :-(\n");
        exit(EXIT_FAILURE);
    }
    
    if(argc == 3)
        threshold = atoi(argv[2]);
    BMP_Image *halftoned = BMP_half_tone(image,threshold,200,0);

    BMP_Save(halftoned,"puiul_halftoned.bmp");
    return 0;
}