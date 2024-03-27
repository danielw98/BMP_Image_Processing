
#include "lowlevel.h"

BMP_Image* BMP_Image_init_alloc(int width, int height)
{
    BMP_Image *image = malloc(sizeof(BMP_Image));
    memset(image,0,sizeof(BMP_Image));
    image->width    = width;
    image->height   = height;
    image->pixels   = malloc(width*sizeof(Pixel*));

    int i;
    for(i = 0; i < width; i++)
        image->pixels[i] = malloc(height*sizeof(Pixel));

    return image;
}


int BMP_Internal_WriteImage(BMP_Image *image, FILE *fp)
{
    if(image == NULL)
        return BMP_ERR;
    _WriteImage_BMHeader(image,fp);
    _WriteImage_DIBHeader(image,fp);
    _WriteImage_Array(image,fp);
    return BMP_OK;
}

void BMP_RawRead(uint32_t where, void *ptr, size_t size, size_t num, FILE *fp)
{
    fseek(fp,where,SEEK_SET);
    fread(ptr,size,num,fp);
}
uint32_t BMP_RawSize(int bpp, int w, int h)
{
    uint32_t RowSize = ((bpp*w+31)/32)*4;
    return RowSize * h;
}

void _WriteImage_BMHeader_to_file(BMHeader *bmHeader, FILE *fp)
{
    fseek(fp,0,SEEK_SET);
    fwrite(&bmHeader->file_type,sizeof(bmHeader->file_type),1,fp);
    fwrite(&bmHeader->file_size,sizeof(bmHeader->file_size),1,fp);
    fwrite(&bmHeader->unused1,sizeof(bmHeader->unused1),1,fp);
    fwrite(&bmHeader->unused2,sizeof(bmHeader->unused2),1,fp);
    fwrite(&bmHeader->bitmap_offset,sizeof(bmHeader->bitmap_offset),1,fp);
}
void _WriteImage_BMHeader(BMP_Image *image, FILE *fp)
{
    BMHeader bmHeader;
    bmHeader.file_type      = ntohs(0x424d);
    bmHeader.bitmap_offset  = 0x36;
    bmHeader.file_size      = 0x36 + BMP_RawSize(24,image->width,image->height);
    bmHeader.unused1        = 0;
    bmHeader.unused2        = 0;
    _WriteImage_BMHeader_to_file(&bmHeader,fp);
}

void _WriteImage_DIBHeader_to_file(DIBHeader *dibHeader, FILE *fp)
{
    fseek(fp,0x0E,SEEK_SET);
    fwrite(&dibHeader->size,sizeof(dibHeader->size),1,fp);
    fwrite(&dibHeader->width,sizeof(dibHeader->width),1,fp);
    fwrite(&dibHeader->height,sizeof(dibHeader->height),1,fp);
    fwrite(&dibHeader->planes,sizeof(dibHeader->planes),1,fp);
    fwrite(&dibHeader->bpp,sizeof(dibHeader->bpp),1,fp);
    fwrite(&dibHeader->compression,sizeof(dibHeader->compression),1,fp);
    fwrite(&dibHeader->raw_size,sizeof(dibHeader->raw_size),1,fp);
    fwrite(&dibHeader->horizontalRes,sizeof(dibHeader->horizontalRes),1,fp);
    fwrite(&dibHeader->verticalRes,sizeof(dibHeader->verticalRes),1,fp);
    fwrite(&dibHeader->paletteColors,sizeof(dibHeader->paletteColors),1,fp);
    fwrite(&dibHeader->importantColors,sizeof(dibHeader->importantColors),1,fp);
}

void _WriteImage_DIBHeader(BMP_Image *image, FILE *fp)
{
    DIBHeader dibHeader;
    memset(&dibHeader,0,sizeof(DIBHeader));
    dibHeader.size   = 0x28;
    dibHeader.width  = image->width;
    dibHeader.height = image->height;
    dibHeader.planes = 0x01;
    dibHeader.bpp    = 0x18;
    dibHeader.compression = 0;
    dibHeader.raw_size = BMP_RawSize(24,image->width,image->height);
    _WriteImage_DIBHeader_to_file(&dibHeader,fp);
}


void write_pixel(BMP_Image *image, int i, int j, FILE *fp)
{
    fwrite(&image->pixels[i][j].blue,1,1,fp);
    fwrite(&image->pixels[i][j].green,1,1,fp);
    fwrite(&image->pixels[i][j].red,1,1,fp);
    if(j == image->width - 1)
    {
        int padding_bytes = image->width % 4;
        Byte padding[4];
        memset(padding,0,sizeof(padding));
        fwrite(padding,padding_bytes,1,fp);
    }
}

void read_pixel(BMP_Image *image, int i, int j, FILE *fp)
{
    fread(&image->pixels[i][j].blue,1,1,fp);
    fread(&image->pixels[i][j].green,1,1,fp);
    fread(&image->pixels[i][j].red,1,1,fp);

    if(j == image->width - 1)
    {
        int padding_bytes = image->width % 4;
        Byte padding[4];
        fread(padding,padding_bytes,1,fp);
    }
}

void _WriteImage_Array(BMP_Image *image, FILE *fp)
{
    fseek(fp,0x36,SEEK_SET);
    int i, j;
    for(i = 0; i < image->height; i++)
        for(j = 0; j < image->width; j++)
            write_pixel(image,i,j,fp);
    
}


void BMP_Image_seek_startpos(FILE *fp)
{
    uint32_t offset;
    BMP_RawRead(BITMAP_OFFSET,&offset,4,1,fp);
    fseek(fp,offset,SEEK_SET);
}

void BMP_Image_init_read(BMP_Image *image, FILE *fp)
{
    int i, j;
    BMP_Image_seek_startpos(fp);
    for(i = 0; i < image->height; i++)
        for(j = 0; j < image->width; j++)
            read_pixel(image,i,j,fp);
}

BMP_Image* BMP_Image_init(FILE *fp)
{
    uint32_t width;
    uint32_t height;

    BMP_RawRead(BITMAP_WIDTH,&width,4,1,fp);
    BMP_RawRead(BITMAP_HEIGHT,&height,4,1,fp);

    BMP_Image *image = BMP_Image_init_alloc(width,height);
    BMP_Image_init_read(image,fp);
    return image;
}


