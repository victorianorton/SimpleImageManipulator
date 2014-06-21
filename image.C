#include <string.h>
#include <stdlib.h>

#include "image.h"

Image::Image()
{
    int width = 0;
    int height = 0;
    unsigned char *buffer = NULL;
}

Image::Image(Image &img)
{
    width = img.width;
    height = img.height;
    buffer = new unsigned char[3 * width * height];
    memcpy(buffer, img.buffer, 3 * width * height * sizeof(unsigned char));
}

Image::Image(int w, int h)
{
    width = w;
    height = h;
    buffer = new unsigned char[3 * width * height];
}

void Image::ResetSize(int w, int h)
{
    width = w;
    height = h;
    buffer = new unsigned char[3 * width * height];
}

int Image::GetWidth() 
{
    return width;
}

int Image::GetHeight()
{
    return height;
}

unsigned char * Image::GetBuffer()
 {
    return buffer;
}