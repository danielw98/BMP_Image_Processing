#include "bmp.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
typedef struct _cat
{
    int         type;
    BMP_Image   *image;
    char        *name;
}Cat;

typedef struct _catGrid
{
    int dim;
    int matrix[5][5];
}CatGrid;

enum colors
{
    YELLOW,
    RED
};
void print_cat(Cat *cat)
{
    printf("path: %s\n", cat->name);
}



Cat* load_cats()
{
    char *dirname = "assets";
    Cat **cats = malloc(5*sizeof(Cat*));
    DIR *dir = opendir(dirname);
    if(dir == NULL)
    {
        perror(dirname);
        exit(1);
    }
    chdir(dirname);
    printf("current: %s\n",getcwd(NULL,0));
    struct dirent *entry;
    struct stat filestat;
    int num_cats = 0;
    while(entry = readdir(dir))
    {
        if(!strcmp(entry->d_name,"..") || !strcmp(entry->d_name,"."))
            continue;
        Cat *my_cat     = malloc(sizeof(Cat));
        my_cat->image   = BMP_Open(entry->d_name);
        my_cat->type    = 1;
        my_cat->name    = strdup(entry->d_name);

        cats[num_cats++] = my_cat;
    }

    for(int i = 0; i < num_cats; i++)
    {
        print_cat(cats[i]);
    }
}

int compare_cats(BMP_Image *a, BMP_Image *b)
{
    if(a->width != b->width || a->height != b->height)
    {
        printf("w/h not match\n");
        return -1;
    }
        
    int i, j;
    int same = 1;
    for(i = 0; i < a->width; i++)
        for(j = 0 ; j < a->height; j++)
            if(a->pixels[i][j].red != b->pixels[i][j].red)
                same = 0;
    return same;

}
void read_matrix(BMP_Image *image, CatGrid *catGrid)
{
    printf("reading matrix\n");

    int width = image->width;
    int height = image->height;

    printf("%d %d\n",width,height);

    

    BMP_Image *cat_yellow = BMP_Open("assets/01_F_yellow.bmp");


    BMP_Image *test = BMP_Crop(image,0,0,90,90);
    BMP_Save(test,"test.bmp");
    return;
    /* new code */
    catGrid->dim = 5;
    int i, j;
    BMP_Image *current;
    int cut[] = {0,91,182,272,363};
    for(i = 0; i < catGrid->dim; i++)
        for(j = 0; j < catGrid->dim; j++)
        {
            current = BMP_Crop(image,cut[i],cut[j],80,80);
            if(compare_cats(current,cat_yellow) == 1)
            {
                catGrid->matrix[i][j] = YELLOW;
            }
            else
            {
                catGrid->matrix[i][j] = RED;
            }
            char name[50];
            sprintf(name,"assets/cat_%02d_%02d.bmp",i,j);
            BMP_Save(current,name);
            BMP_Free(current);
        }

    for(i = 0; i < catGrid->dim; i++)
    {
        for(j = 0; j < catGrid->dim; j++)
        {
            printf("%s\t", catGrid->matrix[i][j]==RED ? "DIFF" : "SAME");
        }
        printf("\n");
    }
        
    return;
}
void load_screenshot(const char *path)
{
    BMP_Image *image = BMP_Open(path);

    CatGrid catGrid;

    read_matrix(image,&catGrid);

}
int main(int argc, char **argv)
{
    
    load_screenshot("assets/level01_cropped.bmp");
    return 0;
}