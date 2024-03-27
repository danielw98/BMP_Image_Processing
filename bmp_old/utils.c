#include "utils.h"

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
    for(i = 0; i < image->width; i++)
        for(j = 0; j < image->height; j++)
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

void read_pixel(BMP_Image *image, int i, int j, FILE *fp)
{
    fread(&image->pixels[i][j].red,1,1,fp);
    fread(&image->pixels[i][j].green,1,1,fp);
    fread(&image->pixels[i][j].blue,1,1,fp);

    if(i+1 == image->width)
    {
        int padding_bytes = image->width % 4;
        Byte padding[4];
        fread(padding,padding_bytes,1,fp);
    }
}



