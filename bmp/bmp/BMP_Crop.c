#include "bmp.h"

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;

    BMP_Image *image = BMP_Open(argv[1]);

    BMP_Image *new_image = BMP_Crop(image,140,595,449,449);

    BMP_Save(new_image,"new.bmp");
    return 0;
}