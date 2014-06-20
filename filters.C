#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

void ReadImage(char *filename, Image &img)
{
    FILE *f = fopen(filename, "rb");                /*Initialize variable and open the file to read from it*/
    char magicNum[128];
    int  width, height, maxval;

    if(f == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
    }

    fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
/*
    printf("Magic num = %s width = %d, height = %d", magicNum, width, height);
 */

    if(strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
    }

    img.ResetSize(width, height);
    fread(img.GetBuffer(), sizeof(char), 3*width*height, f);         /* Read the elements of the array to f */
 }


void WriteImage(char *filename, Image &img)
{
    FILE *f = fopen(filename, "w");                 /*Initialize variable and open the file to write from it*/
    int  width, height;
 
    width = img.GetWidth();                                 /* Width, height, and maxval are pointed to by img */
    height = img.GetHeight();

    fprintf(f, "%s\n%d %d\n%d\n", "P6", width, height, 255);
/*
    printf("Magic num = %s width = %d, height = %d/n", magicNum, width, height);
 */

    fwrite(img.GetBuffer(), sizeof(char), 3*img.GetWidth()*img.GetHeight(), f);       /* Write the elements of the array to f */
    
    fclose(f);                                      /* Close the file*/
}

void YellowDiagonal(Image &input, Image &output)
{
    unsigned char *pixel;                            // Initialize the pixal variable 
    int  width, height;
    int i;

    width = input.GetWidth();
    height = input.GetHeight();

    output.ResetSize(width, height);

    memcpy(output.GetBuffer(), input.GetBuffer(), 3*input.GetWidth()*input.GetHeight());  // Copy the image memory and create a new one

    for(i = 0; i < height; i++)                   // For loop to set the pixel color down the diagonal 
    {
        pixel = output.GetBuffer() + (i*output.GetWidth()+i)*3;
        pixel[0] = 255;
        pixel[1] = 255;
        pixel[2] = 0;
    }
}

void HalveInSize(Image &input, Image &output)
{ 
    int i, j;                                                       // Initialize i & j variables
    
    output.ResetSize(input.GetWidth()/2, input.GetHeight()/2);
    
    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {
            output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = input.GetBuffer()[3*(2*i*input.GetWidth()+2*j)+0];
            output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = input.GetBuffer()[3*(2*i*input.GetWidth()+2*j)+1];
            output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = input.GetBuffer()[3*(2*i*input.GetWidth()+2*j)+2];
        }
    }
}

void LeftRightConcatenate(Image &leftInput, Image &rightInput, Image &output)
{
    int i, j;                                                   // Initialize the i & j  variables 
    int width, height;

    width = leftInput.GetWidth() + rightInput.GetWidth();

    if(leftInput.GetHeight() > rightInput.GetHeight())          // Find the max height of the two images 
    {
        height = leftInput.GetWidth();
    }
    else
    {
        height = rightInput.GetHeight();
    }

    output.ResetSize(width, height);

    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {           
           if(j < leftInput.GetWidth())
           {
                output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = leftInput.GetBuffer()[3*(i*leftInput.GetWidth()+j)+0];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = leftInput.GetBuffer()[3*(i*leftInput.GetWidth()+j)+1];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = leftInput.GetBuffer()[3*(i*leftInput.GetWidth()+j)+2];
           }
           else
           {
                output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = rightInput.GetBuffer()[3*(i*rightInput.GetWidth()+j)+0];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = rightInput.GetBuffer()[3*(i*rightInput.GetWidth()+j)+1];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = rightInput.GetBuffer()[3*(i*rightInput.GetWidth()+j)+2];
           }
        }
    }

}

void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output)
{
    int i, j;                                                   // Initialize the i & j  variables 
    int width, height;

    height = topInput.GetHeight() + bottomInput.GetHeight();

    if(topInput.GetWidth() > bottomInput.GetWidth())            // Find the max width of the two images
    {
        width = topInput.GetWidth();
    }
    else
    {
        width = bottomInput.GetWidth();
    }

    output.ResetSize(width, height);


    for(i = 0; i < topInput.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {   
            output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = topInput.GetBuffer()[3*(i*topInput.GetWidth()+j)+0];
            output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = topInput.GetBuffer()[3*(i*topInput.GetWidth()+j)+1];
            output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = topInput.GetBuffer()[3*(i*topInput.GetWidth()+j)+2];  
        }
    }

     for(i = 0; i < bottomInput.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {
            output.GetBuffer()[3*((i+topInput.GetHeight())*output.GetWidth()+j)+0] = bottomInput.GetBuffer()[3*(i*bottomInput.GetWidth()+j)+0];
            output.GetBuffer()[3*((i+topInput.GetHeight())*output.GetWidth()+j)+1] = bottomInput.GetBuffer()[3*(i*bottomInput.GetWidth()+j)+1];
            output.GetBuffer()[3*((i+topInput.GetHeight())*output.GetWidth()+j)+2] = bottomInput.GetBuffer()[3*(i*bottomInput.GetWidth()+j)+2];
        }
    }
}

void Blend(Image &input1, Image &input2, float factor, Image &output)
{
    unsigned char *pixel;                                                                           // Initialize the pixal variable 
    int i, j;
    
    output.ResetSize(input1.GetWidth(), input1.GetHeight());

    memcpy(output.GetBuffer(), input1.GetBuffer(), 3*input1.GetWidth()*input1.GetHeight());         // Copy the image memory and create a new one

    for(i = 0; i < output.GetHeight(); i++)                                                         // For loop to set the pixel color down the diagonal 
    {
        for(j = 0; j < output.GetWidth(); j++)
        {                  
            output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = (input1.GetBuffer()[3*(i*input1.GetWidth()+j)+0]*factor) + (input2.GetBuffer()[3*(i*input2.GetWidth()+j)+0]*(1-factor));
            output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = (input1.GetBuffer()[3*(i*input1.GetWidth()+j)+1]*factor) + (input2.GetBuffer()[3*(i*input2.GetWidth()+j)+1]*(1-factor));
            output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = (input1.GetBuffer()[3*(i*input1.GetWidth()+j)+2]*factor) + (input2.GetBuffer()[3*(i*input2.GetWidth()+j)+2]*(1-factor));
        }
    }
}