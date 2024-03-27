#ifndef __BMP_LOWLEVEL__H__
#define __BMP_LOWLEVEL__H__

#include "commons.h"


typedef struct _BMHeader
{
    uint16_t file_type;
    uint32_t file_size; 
    uint16_t unused1;
    uint16_t unused2;
    uint32_t bitmap_offset;
}BMHeader;

typedef struct _DIBHeader
{
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t raw_size;
    uint32_t verticalRes;
    uint32_t horizontalRes;
    uint32_t paletteColors;
    uint32_t importantColors;
}DIBHeader;


void        BMP_RawRead(uint32_t where, void *ptr, size_t size, size_t num, FILE *fp);
uint32_t    BMP_RawSize(int bpp, int w, int h);


void _WriteImage_BMHeader_to_file (BMHeader   *bmHeader, FILE *fp);
void _WriteImage_DIBHeader_to_file(DIBHeader *dibHeader, FILE *fp);
void _WriteImage_BMHeader   (BMP_Image *image, FILE *fp);
void _WriteImage_DIBHeader  (BMP_Image *image, FILE *fp);
void _WriteImage_Array      (BMP_Image *image, FILE *fp);
int  BMP_Internal_WriteImage(BMP_Image *image, FILE *fp);

void write_pixel(BMP_Image *image, int i, int j, FILE *fp);
void read_pixel (BMP_Image *image, int i, int j, FILE *fp);


BMP_Image* BMP_Image_init(FILE *fp);
BMP_Image* BMP_Image_init_alloc(int width, int height);
void       BMP_Image_init_read(BMP_Image *image, FILE *fp);
void       BMP_Image_seek_startpos(FILE *fp);;

#endif /* __BMP_LOWLEVEL__H__ */