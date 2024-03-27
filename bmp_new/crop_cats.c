#include "bmp.h"

enum CatColor
{
    RED,
    YELLOW
};

int Compare_Row(Pixel *a, Pixel *b, int num)
{
    int i;
    for(i = 0; i < num; i++)
    {
        int abs_diff = 0;
        abs_diff += abs(a[i].red-b[i].red);
        abs_diff += abs(a[i].green-b[i].green);
        abs_diff += abs(a[i].blue-b[i].blue);

        if(abs_diff > 200)
            return 1;
    }
    return 0;
}
int BMP_CompareImage(BMP_Image *a, BMP_Image *b)
{
    static int num = 0;
    if(a->width != b->width || a->height != b->height)
    {
        fprintf(stderr,"Out of bounds");
        return -1;
    }

    int i,j;
    int same = 1;
    int num_errs = 10;
    for(i = 0; i < a->height; i++)
    {
        if(Compare_Row(a->pixels[i],b->pixels[i],b->width) == 1)
        {
            if(--num_errs == 0){
                same = 0;
                break;
            }
        }
    }

    return same;
}
enum CatColor CC_GetColor(BMP_Image *image)
{
    BMP_Image *yellow  = BMP_Open("assets/01_F_yellow.bmp");
    BMP_Image *red     = BMP_Open("assets/01_F_red.bmp");
    enum CatColor cc;
    if(BMP_CompareImage(image,yellow)==1)
        cc = YELLOW;
    else if(BMP_CompareImage(image,red)==1)
        cc = RED;
    else
    {
        printf("Neither Red nor yellow!\n");
        BMP_Free(yellow); BMP_Free(red);
        return -1;
    }
    BMP_Free(yellow); BMP_Free(red);
    return cc;
}
void CC_GetMatrix(const char *path, int matrix[5][5])
{
    BMP_Image *new_image = BMP_Open(path);
    /*
    BMP_Save(image,"assets/saved.bmp");
    BMP_Free(image);

    image = BMP_Open("assets/saved.bmp");
    BMP_Image *new_image = BMP_Crop(image,140,595,449,449);


    BMP_Save(new_image,"assets/crop_full.bmp");
    */
    int i, j;
    int offset[5] = {0, 91, 182, 272, 363};
    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
        {
            BMP_Image *cat_i_j = BMP_Crop(new_image,offset[i],offset[j],86,86);
            matrix[i][j] = CC_GetColor(cat_i_j);
            char savepath[50];
            sprintf(savepath,"assets/crops/cat_%02d_%02d.bmp",i,j);
            BMP_Free(cat_i_j);
        }
    //BMP_Free(image); 
    BMP_Free(new_image);

    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++)
            printf("%d  ", matrix[i][j]);
        printf("\n");
    }

}

Move try_max_move(int matrix[5][5], int i, int j)
{
    Move move;
    move.start[0] = i; move.start[1] = j;
    for(; i < 5; i++)
        for(; j < 5; j++)
}
typedef struct _move
{
    int start[2];
    int end[2];
    int score;
}Move;

void MaxMove(int matrix[5][5])
{
    int i, j;
    
    Move max_move;
    max_move.score = 0;
    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
        {
            Move move = try_max_move(matrix,i,j);
            if(move.score > max_move.score){
                max_move = move;
            }
        }
}
int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;
    int matrix[5][5];
    CC_GetMatrix(argv[1],matrix);

    return 0;
}