#include "checks.h"
int check_file_type(FILE *fp)
{
    uint16_t magic;
    fread(&magic,sizeof(magic),1,fp);
    uint16_t magic_bytes = read_16(0x424d);
    if(magic != magic_bytes)
    {
        printf("Not a bitmap (magic bytes don't match)... %x\n",magic);
        return BMP_ERR;
    }
    return BMP_OK;
}

int check_bmp_extension(const char *path)
{
    int length;
    length = strlen(path);
    if(strcmp(path+length-4,".bmp"))
    {
        fprintf(stderr,"Not a bitmap (at least not the extension)...\n");
        return BMP_ERR;
    }
    return BMP_OK;
}

int check_bmp_magic(FILE *fp)
{
    if(fp == NULL)
    {
        fprintf(stderr,"File doesn't exist\n");
        return BMP_ERR;
    }

    uint16_t magic;
    BMP_RawRead(BITMAP_MAGIC,&magic,sizeof(magic),1,fp);

    uint16_t bmp_magic = read_16(0x424d);
    if(bmp_magic != magic)
    {
        fprintf(stderr,"Magic bytes don't match..\n");
        return BMP_ERR;
    }
    return BMP_OK;
}