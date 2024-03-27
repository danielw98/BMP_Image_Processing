#ifndef __HISTOGRAM__H_
#define __HISTOGRAM__H_
    

#define __BMP__STRUCT_DEFINITION
typedef struct _BMP_Image BMP_Image;

void calculate_histogram(BMP_Image *image, unsigned long histogram[]);
void smooth_histogram(unsigned long histogram[], int gray_levels);
void perform_histogram_equalization(BMP_Image *image, unsigned long histogram[], int gray_levels, int new_grays);
#endif // __HISTOGRAM__H_