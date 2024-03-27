#ifndef __BMP_COMMONS__H_
#define __BMP_COMMONS__H_

#define BMP_OK  0
#define BMP_ERR -1
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define  read_16(x)     ntohs(x) 
#define write_16(x)     htons(x)
#define  read_32(x)     ntohl(x)
#define write_32(x)     htonl(x)

#define BITMAP_MAGIC    0x00
#define BITMAP_SIZE     0x02
#define BITMAP_OFFSET   0x0A
#define BITMAP_WIDTH    0x12
#define BITMAP_HEIGHT   0x16
#define BITMAP_BPP      0x1C
#define BITMAP_SIZE_RAW 0x22

typedef uint8_t Byte;

typedef struct _Pixel
{
    Byte red;
    Byte green;
    Byte blue;
}Pixel;

typedef struct _Image
{
    int sign;
    int width;
    int height;
    Pixel **pixels;
} BMP_Image;

#endif /* __BMP_COMMONS__H_ */