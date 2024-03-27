
#ifndef __BMP_CHECKS__H_
#define __BMP_CHECKS__H_
#include "commons.h"
#include "lowlevel.h"
int check_file_type(FILE *fp);
int check_bmp_magic(FILE *fp);
int check_bmp_extension(const char *path);
#endif /* __BMP_CHECKS__H_ */
