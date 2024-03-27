

BMP_Image*  BMP_Open  (const char *path)
    Open the image given by the path and return a handle.
    Returns NULL if the given image couldn't be loaded.

BMP_Image*  BMP_New   (int width, int height)
    Create empty image with fixed width and height and return a handle.
    Returns NULL if the allocation fails.

BMP_Image*  BMP_Copy  (BMP_Image *src)
    Create a copy of the source image and return a handle. 
    Returns NULL if the copy fails.

void        BMP_Free  (BMP_Image *image)
    Free the given image

void        BMP_Print (BMP_Image *image)
    Hexprint the image. For debugging purposes maybe?

int         BMP_Save  (BMP_Image *image, const char *savepath)
    Save the image to the path indicated.
    Returns -1 on failure.

BMP_Image*  BMP_Crop  (BMP_Image *image, int x, int y, int new_w, int new_h)
    Crop the image starting from (x,y) to a new width and height.
    Returns NULL on failure.






TODO:
    tests for all the functions
    properly make it so that the images can be addressed with 
        for(i = 0; i < width; i++)
            for(j = 0; j < height; j++)
                // image->pixels[i][j]
    eventually delete utils.c merging it with other files
    make lowlevel.c more readable and less error-prone