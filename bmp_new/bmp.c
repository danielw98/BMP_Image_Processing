#include "bmp.h"
#include "commons.h"
#include "checks.h"
#include "lowlevel.h"
#include "bmpstruct.h"



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
    BMP_Image *cropped;
    int i;

    if(image == NULL)
    {
        fprintf(stderr,"BMP_Crop: NULL image input\n");
        return NULL;
    }
    if(y+new_w > image->width || x+new_h > image->height)
    {
        fprintf(stderr,"BMP_Crop: out of bounds\n");
        return NULL;
    }

    cropped = BMP_New(new_w,new_h);
    for(i = 0; i < new_h; i++)
        memcpy(cropped->pixels[i],y+image->pixels[x+i],new_w*sizeof(Pixel));
    
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


void BMP_BWFunc(Pixel *pixel)
{
    int sum = pixel->red + pixel->green + pixel->blue;
    sum /= 3;
    pixel->red = pixel->green = pixel->blue = sum;
}

void BMP_ForEachPixel(BMP_Image *image, void (*pixfunc)(Pixel*))
{
    int i, j;
    for(i = 0; i < image->height; i++)
        for(j = 0; j < image->width; j++)
            pixfunc(&image->pixels[i][j]);
}

void BMP_BlackWhite(BMP_Image *image)
{
    BMP_ForEachPixel(image,BMP_BWFunc);
}

int convolution(BMP_Image *image, int kernel[3][3], int row, int col) {

    
	int i, j, sum = 0;
	for (i = 0; i < 3; i++) 
		for (j = 0; j < 3; j++)
        {
            uint8_t pix = image->pixels[i+row][j+col].red;
			sum += pix * kernel[i][j];
        }
	return sum;
}

void BMP_DetectEdges(BMP_Image *image, Byte cutoff)
{
    
	int edges_X[3][3] = {{-1,  0,  1},{-1, 0, 1},{-1, 0, 1}};
	int edges_Y[3][3] = {{-1, -1, -1},{ 0, 0, 0},{ 1, 1, 1}};
	int i, j, gx, gy;
	for (i = 1; i < image->height - 2; i++) {
		for (j = 1; j < image->width; j++){
            gx = convolution(image, edges_X, i, j);
			gy = convolution(image, edges_Y, i, j);
			image->pixels[i][j].red = 
            image->pixels[i][j].green =
            image->pixels[i][j].blue = 
            (gx+gy > cutoff ? 255 : 0);
		}
	}
}

BMP_Image* BMP_half_tone(BMP_Image *in, int threshold, int one, int zero)
{
    BMP_Image *out;
    BMP_Image *in_copy;
    float **eg, **ep;
    float c[2][3], sum_p, t;
    int i, j, m, n, xx, yy;
    int rows, cols;

    rows = in->height; 
    cols = in->width;
    
    in_copy = BMP_Copy(in);
    BMP_BlackWhite(in);
    out = BMP_New(cols,rows);
    
    c[0][0] = 0.0; c[0][1] = 0.2; c[0][2] = 0.0;
    c[1][0] = 0.6; c[1][1] = 0.1; c[1][2] = 0.1;
    
    eg = malloc(rows * sizeof(float*));
    for(i = 0; i < rows; i++)
        eg[i] = malloc(cols * sizeof(float));
 
    ep = malloc(rows * sizeof(float*));
    for(i = 0; i < rows; i++)
        ep[i] = malloc(cols * sizeof(float ));
    
    for(i = 0; i < in->height; i++)
    {
        for(j = 0; j < in->width; j++)
        {
            eg[i][j] = 0.0;
            ep[i][j] = 0.0;
        }
    }

    for(m = 0; m < rows; m++)
    {
        for(n = 0; n < cols; n++)
        {
            sum_p = 0.0;
            for(i = 0; i < 2; i++)
            {
                for(j = 0; j < 3; j++)
                {
                    xx = m-i+1;
                    yy = n-j+1;
                    if(xx < 0) 
                        xx = 0;
                    if(xx >= rows) 
                        xx = rows-1;
                    if(yy < 0) 
                        yy = 0;
                    if(yy >= cols) 
                        yy = cols-1;
                    sum_p = sum_p + c[i][j] * eg[xx][yy];
                }
            }
    
            ep[m][n] = sum_p;
            t = in->pixels[m][n].red + ep[m][n];
   
            if(t > threshold)
            {
                eg[m][n] = t - threshold*2;
                out->pixels[m][n].red = out->pixels[m][n].green = out->pixels[m][n].blue = one;
                // out->pixels[m][n].red = in_copy->pixels[m][n].red;
                // out->pixels[m][n].green = in_copy->pixels[m][n].green;
                // out->pixels[m][n].blue = in_copy->pixels[m][n].blue;
            }
   
            else
            {
                eg[m][n] = t;
                out->pixels[m][n].red = out->pixels[m][n].green = out->pixels[m][n].blue = zero;
            }
        }
    }

    for(i = 0; i < rows; i++)
    {
        free(eg[i]);
        free(ep[i]);
    }

    return out;
}

Pixel BMP_GetPixel(BMP_Image *image, int i, int j)
{
    return image->pixels[i][j];
}

void BMP_SetPixel(BMP_Image *image, int i, int j, Pixel pixel)
{
    image->pixels[i][j] = pixel;
}