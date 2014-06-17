#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

// Default constructor
Image::Image()
{
    width = 0;
    height = 0;
    buffer = NULL;
}

// Copy constructor
Image::Image(Image &img)
{
    width = img.width;
    height = img.height;
    //buffer = (unsigned char*) malloc((3*width*height));         /* img is pointed to by buffer, which has allocated memory for the 3 types of pixles */
    buffer = new unsigned char [3*width*height];
    memcpy(buffer, img.buffer, 3*width*height);
}

// Parametertized constructor
Image::Image(int w, int h)
{
    width = w;
    height = h;
}

// Get height method
int Image::GetHeight()
{
    return height;
}

// Get width method
int Image::GetWidth()
{
    return width;
}

// Get buffer method
unsigned char* Image::GetBuffer()
{
    return buffer;
}

// Reset size method
void Image::ResetSize(int w, int h)
{
    width = w;
    height = h;
   // buffer = (unsigned char*) malloc((3*width*height));         /* img is pointed to by buffer, which has allocated memory for the 3 types of pixles */
    buffer = new unsigned char[3*width*height];
}