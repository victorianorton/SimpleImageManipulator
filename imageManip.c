#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    /* data members go here */
    int  w, h, m;                                   /* Initialize width, height, and maxvalue */
    unsigned char *buffer;                          /* Initialize the 1D array as buffer */

} Image;

Image * ReadImage(char *filename)
{
    FILE *f = fopen(filename, "rb");                /*Initialize variable and open the file to read from it*/
    Image *img = NULL;
    char magicNum[128];
    int  width, height, maxval;

    if(f == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return NULL;
    }

    fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
/*
    printf("Magic num = %s width = %d, height = %d, maxval = %d\n",
            magicNum, width, height, maxval);
 */

    if(strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
        return NULL;
    }

    img = malloc(sizeof(Image));                    /* Allocate memory for the Image */
    img->buffer = malloc((3*width*height));         /* img is pointed to by buffer, which has allocated memory for the 3 types of pixles */
    
    img->w = width;                                 /* Width and height are pointed to by img */
    img->h = height;
    img->m = maxval;
    
    fread(img->buffer, 3, width*height, f);         /* Read the elements of the array to f */

    return img;                                     /* Return the image */

    fclose(f);                                      /* Close the file*/
 }


void WriteImage(Image *img, char *filename)
{
    FILE *f = fopen(filename, "w");                 /*Initialize variable and open the file to write from it*/
    int  width, height, maxval;
 
    width = img->w;                                 /* Width, height, and maxval are pointed to by img */
    height = img->h;
    maxval = img->m;

    fprintf(f, "%s\n %d\n %d\n %d\n", "P6", width, height, maxval);
/*
    printf("Magic num = %s width = %d, height = %d, maxval = %d\n",
            magicNum, width, height, maxval);
 */

    fwrite(img->buffer, 3, img->w*img->h, f);       /* Write the elements of the array to f */
    
    fclose(f);                                      /* Close the file*/
}

Image * YellowDiagonal(Image *input)
{
    unsigned char *pixel;                            /* Initialize the pixal variable */
    int i;

    Image *img;                                     /* Initialize the struct image */
    img = malloc(sizeof(Image));                    /* Allocate memory for the Image */
    img->buffer = malloc((3*input->w*input->h));    /* img is pointed to by buffer, which has allocated memory for the 3 types of pixles */
       
    img->w = input->w;
    img->h = input->h;
    img->m = input->m;

    memcpy(img->buffer, input->buffer, 3*input->w*input->h);  /* Copy the image memory and create a new one*/
    
    for(i = 0; i < input->h; i++)                   /* For loop to set the pixel color down the diagonal */
    {
        pixel = img->buffer + (i*img->w+i)*3;
        *pixel = (255, 255, 0);
    }
    
    return img;
}

int main(int argc, char *argv[])
{

   /* Read an image, apply yellow diagonal to it, then write */
    if(argc != 3)
    {
        printf("Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);                       /*Good practice to have exit failure*/
    }

    Image *img = ReadImage(argv[1]);
    Image *im = YellowDiagonal(img);
    WriteImage(im, argv[2]);

    return 0;
}