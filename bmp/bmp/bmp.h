#ifndef __BMP__H_
#define __BMP__H_

#include "commons.h"
#include "lowlevel.h"
#include "checks.h"
BMP_Image*  BMP_Copy  (BMP_Image *src);
BMP_Image*  BMP_Open  (const char *path);
BMP_Image*  BMP_New   (int width, int height);
void        BMP_Free  (BMP_Image *image);
void        BMP_Print (BMP_Image *image);
int         BMP_Save  (BMP_Image *image, const char *savepath);
BMP_Image*  BMP_Crop  (BMP_Image *image, int x, int y, int new_w, int new_h);

#endif /*__BMP__H_*/