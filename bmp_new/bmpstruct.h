#ifndef __BMP_STRUCT__H_
#define __BMP_STRUCT__H_

#include "bmppixel.h"
typedef struct _BMP_Image
{
    int sign;
    int width;
    int height;
    Pixel **pixels;
} BMP_Image;

#endif // __BMP_STRUCT__H_