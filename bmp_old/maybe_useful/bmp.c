#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define BMP_OK  0
#define BMP_ERR -1

#define BITMAP_OFFSET   0x0A
#define BITMAP_WIDTH    0x12
#define BITMAP_HEIGHT   0x16
#define BITMAP_BPP      0x1C
#define BITMAP_SIZE_RAW 0x22
typedef uint8_t byte;
typedef struct _my_bitmap
{
    uint32_t width;
    uint32_t height;
    uint32_t *array;
    uint32_t size;
}Bitmap_Arr;

typedef struct _BitmapHeader
{
    uint16_t magic;
    uint32_t header;
    uint32_t _unused;
    uint32_t offset;

    // DIB header
    uint32_t dib_num_bytes;
    int32_t width;
    int32_t height;

}BitmapHeader;

int check_file_type(FILE *fp)
{
    uint16_t magic;
    fread(&magic,sizeof(magic),1,fp);

    uint16_t magic_bytes = (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) ? 0x4D42 : 0x424D;
    if(magic != magic_bytes)
    {
        printf("Not a bitmap (magic bytes don't match)... %x\n",magic);
        return BMP_ERR;
    }
    return BMP_OK;
}

void read_bitmap(BitmapHeader *bitmap, FILE *fp)
{

    
    fseek(fp,0,SEEK_END);
    int length = ftell(fp);
    fseek(fp,0,SEEK_SET);

    memset(bitmap,0,sizeof(BitmapHeader));

    fread(&bitmap->magic, sizeof(bitmap->magic), 1, fp);
    fread(&bitmap->header,sizeof(bitmap->header),1, fp);
    fread(&bitmap->_unused,sizeof(bitmap->_unused),1,fp);
    fread(&bitmap->offset,sizeof(bitmap->offset),1,fp);

    fread(&bitmap->dib_num_bytes,sizeof(bitmap->dib_num_bytes),1,fp);
    fread(&bitmap->width,sizeof(bitmap->width),1,fp);
    fread(&bitmap->height,sizeof(bitmap->height),1,fp);

    printf("w,h : %d %d\n",bitmap->width,bitmap->height);

    int bitmap_size;
    bitmap_size = bitmap->header - 14;

    

    fseek(fp,bitmap->offset,SEEK_SET);
}

void read_bmp_arr(Bitmap_Arr *bmpArr, int offset, FILE *fp)
{
    fseek(fp,offset,SEEK_SET);
    fread(bmpArr->array,bmpArr->size,1,fp);
}

#if 0
void color_at_position(int x, int y,  Bitmap_Arr *bmpArr, FILE *fp)
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    uint32_t size = bmpArr->size;

    uint32_t num_bytes = bmpArr->width * bmpArr->height * 3;

    uint32_t padding = size - num_bytes;
    padding /= bmpArr->width;

    int row_size = bmpArr->width + padding;
    int col_size = bmpArr->height;
    int index;

    index = x * row_size + col_size;
    printf("%2d %2d: ", x+1, y+1);

    if(index % 4 == 0)
    {
        int c_index = index/4;
        red     = (bmpArr->array[c_index] >> 24) & 0xFF;
        green   = (bmpArr->array[c_index] >> 16) & 0xFF;
        blue    = (bmpArr->array[c_index] >>  8) & 0xFF;
    }
    else
    {   //  R  G  B  R  G  B  P  P
        // AA BB CC DD 00 AA BB 00
        int c_index = index/4;
        int diff = 24 - (index % 4) * 8;
        
        red = (bmpArr->array[c_index] >> diff) & 0xFF;
        diff -= 8;

        if(diff < 0)
        {
            diff = 24;
            c_index++;
        }
        green = (bmpArr->array[c_index] >> diff) & 0xFF;
        diff -= 8;
        if(diff < 0)
        {
            diff = 24;
            c_index++;
        }

        blue = (bmpArr->array[c_index] >> diff) & 0xFF;

    }
    
    printf("#%02x%02x%02x\n",red,green,blue);
}
#endif


void color_at_position(int x, int y, FILE *fp)
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    int relative_offset = compute_offset(x,y,)
    fseek(fp,BITMAP_OFFSET,SEEK_SET);
    fseek(fp,)
    fread(&red,sizeof(uint8_t),1,fp);
    fread(&green,sizeof(uint8_t),1,fp);
    fread(&blue,sizeof(uint8_t),1,fp);
    printf("#%02x%02x%02x\n",red,green,blue);
}
Bitmap_Arr *bmp_open(const char *path)
{
    int length;
    length = strlen(path);
    if(strcmp(path+length-4,".bmp"))
    {
        printf("Not a bitmap (at least not the extension)...\n");
        return NULL;
    }

    FILE *fp = fopen(path,"rb");
    if(check_file_type(fp) == BMP_ERR)
    {
        
        return NULL;
    }
    
    BitmapHeader bitmapHeader;
    read_bitmap(&bitmapHeader, fp);

    Bitmap_Arr *bmp_arr = malloc(sizeof(Bitmap_Arr));
    memset(bmp_arr,0,sizeof(Bitmap_Arr));

    bmp_arr->width  = bitmapHeader.width;
    bmp_arr->height = bitmapHeader.height;
    fseek(fp,0x22,SEEK_SET);
    fread(&bmp_arr->size,sizeof(bmp_arr->size),1,fp);
    bmp_arr->array  = malloc(bmp_arr->size);
    printf("size: %d, offset: %x\n", bmp_arr->size,bitmapHeader.offset);
    read_bmp_arr(bmp_arr,bitmapHeader.offset,fp);

    int i, j;
    for(i = 0; i < bmp_arr->width; i++)
        for(j = 0; j < bmp_arr->height; j++)
            color_at_position(i,j,bitmapHeader,fp);
    return bmp_arr;
}

int main()
{
    Bitmap_Arr *picture = bmp_open("cats/ex.bmp");

    if(picture == NULL)
    {
        printf("Invalid picture. Exiting\n");
        exit(1);
    }

    return 0;
}