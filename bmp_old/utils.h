#ifndef __BMP_UTILS__H_
#define __BMP_UTILS__H_

#include "commons.h"
#include "lowlevel.h"
BMP_Image* BMP_Image_init_alloc(int width, int height);
BMP_Image* BMP_Image_init(FILE *fp);
void       BMP_Image_init_read(BMP_Image *image, FILE *fp);
void       BMP_Image_seek_startpos(FILE *fp);;



#endif /* __BMP_UTILS__H_ */