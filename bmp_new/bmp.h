#ifndef __BMP__H_
#define __BMP__H_
#include <stdint.h>
#include "bmppixel.h"
#include "histogram.h"

#ifndef __BMP__STRUCT_DEFINITION
typedef struct _BMP_Image BMP_Image;
#endif // __BMP__STRUCT_DEFINITION

BMP_Image*  BMP_Copy  (BMP_Image *src);
BMP_Image*  BMP_Open  (const char *path);
BMP_Image*  BMP_New   (int width, int height);
void        BMP_Free  (BMP_Image *image);
void        BMP_Print (BMP_Image *image);
int         BMP_Save  (BMP_Image *image, const char *savepath);
BMP_Image*  BMP_Crop  (BMP_Image *image, int x, int y, int new_w, int new_h);

void        BMP_BlackWhite(BMP_Image *image);
void        BMP_DetectEdges(BMP_Image *image, Byte cutoff);
void        BMP_ForEachPixel(BMP_Image *image, void (*pixfunc)(Pixel*));

BMP_Image*  BMP_half_tone(BMP_Image *in, int threshold, int one, int zero);
#endif /*__BMP__H_*/