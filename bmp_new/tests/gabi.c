#include "bmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    //BMP_DetectEdges(image,cutoff);

    sprintf(picture,"%s_bw.bmp",output_prefix);
    BMP_Save(image,picture);
    return 0;
}