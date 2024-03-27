#include "bmp.h"

BMP_Image* BMP_Copy(BMP_Image *src)
{
    BMP_Image *dest = BMP_New(src->width,src->height);
    for(int i = 0; i < src->height; i++)
        memcpy(dest->pixels[i],src->pixels[i],src->width*sizeof(Pixel));
    dest->sign = src->sign;
    return dest;
}

BMP_Image* BMP_Crop(BMP_Image *image, int x, int y, int new_w, int new_h)
{
    if(y+new_w > image->width || x+new_h > image->height)
    {
        fprintf(stderr,"BMP_Crop: out of bounds\n");
        return NULL;
    }
    BMP_Image *cropped = BMP_New(new_w,new_h);
    int i, j;
    for(i = 0; i < new_h; i++)
        memcpy(cropped->pixels[i],y+image->pixels[x+i],new_w*sizeof(Pixel));
    
    /*for(i = 0; i < new_h; i++)
        memcpy(&cropped->pixels[i],&image->pixels[x+i],new_w * sizeof(int));
    */
    
    return cropped;
}

BMP_Image* BMP_New(int width, int height)
{
    return BMP_Image_init_alloc(width,height);
}
int BMP_Save(BMP_Image *image, const char *savepath)
{
    FILE *fp = fopen(savepath, "w");
    int status = BMP_OK;
    if(fp == NULL)
    {
        fprintf(stderr,"BMP_Save: %s - cannot create file\n",savepath);
        status = BMP_ERR;
        return status;
    }
    
    if(BMP_Internal_WriteImage(image, fp) == BMP_ERR)
    {
        fprintf(stderr,"BMP_Save: cannot save image %s\n",savepath);
        status = BMP_ERR;
    }
    fclose(fp);
    return status;
}

void BMP_Free(BMP_Image *image)
{
    int i;
    for(i = 0; i < image->height; i++)
        free(image->pixels[i]);
    free(image->pixels);
    free(image);
}

BMP_Image* BMP_Open(const char *path)
{
    FILE *fp; 
    if(check_bmp_extension(path) == BMP_ERR)
        return NULL;

    fp = fopen(path,"rb");
    if(check_bmp_magic(fp) == BMP_ERR)
        return NULL;

    return BMP_Image_init(fp);
}


void BMP_Print(BMP_Image *image)
{
    int i, j;
    for(i = 0; i < image->height; i++)
    {
        for(j = 0; j < image->width; j++)
        {
            Pixel pixel = image->pixels[i][j];
            printf("#%02x%02x%02x\n",pixel.red, pixel.green, pixel.blue);
        }
    }   
}