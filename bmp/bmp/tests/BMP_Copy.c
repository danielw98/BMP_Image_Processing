#include "../bmp.h"
int main(int argc, char **argv)
{
    BMP_Image *image = BMP_Open("saved.bmp");
    BMP_Image *new_image = BMP_Copy(image);
    BMP_Save(new_image,"saved2.bmp");    
    
    return 0;
}