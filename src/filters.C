#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filters.h"
#include "logging.h"

void Shrinker::Execute()
{
    int i, j;                                                       // Initialize i & j variables
    
    img.ResetSize(image1->GetWidth()/2, image1->GetHeight()/2);
    
    for(i = 0; i < img.GetHeight(); i++)
    {
        for(j = 0; j < img.GetWidth(); j++)
        {
            img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+0];
            img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+1];
            img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+2];
        }
    }
}

const char * Shrinker::FilterName()
{
    return "Shrinker";
}

void LRConcat::Execute()
{
    int i, j;                                                        // Initialize the i & j  variables 
    int width, height;

    width = image1->GetWidth() + image2->GetWidth();

    if(image1->GetHeight() > image2->GetHeight())                   // Find the max height of the two images 
    {
        height = image1->GetWidth();
    }
    else
    {
        height = image2->GetHeight();
    }

    img.ResetSize(width, height);

    for(i = 0; i < img.GetHeight(); i++)
    {
        for(j = 0; j < img.GetWidth(); j++)
        {           
            if(j < image1->GetWidth())
            {
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2];
           
            }           
            else
            {
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2];
            }
        }
    }
}

const char * LRConcat::FilterName()
{
    return "LRConcat";
}

void TBConcat::Execute()
{
    int i, j;                                                   // Initialize the i & j  variables 
    int width, height;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(image1->GetWidth() != image2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(), image1->GetWidth(), image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
        height = image1->GetHeight() + image2->GetHeight();

        if(image1->GetWidth() > image2->GetWidth())            // Find the max width of the two images
        {
            width = image1->GetWidth();
        }
        else
        {
            width = image2->GetWidth();
        }

        img.ResetSize(width, height);

        for(i = 0; i < image1->GetHeight(); i++)
        {
            for(j = 0; j < img.GetWidth(); j++)
            {   
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2];  
            }
        }

        for(i = 0; i < image2->GetHeight(); i++)
        {
            for(j = 0; j < img.GetWidth(); j++)
            {
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+0] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0];
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+1] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1];
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+2] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2];
            }
        }
    }
}

const char * TBConcat::FilterName()
{
    return "TBConcat";
}

void Blender::SetFactor(float factor)
{
    this->factor = factor;
}

void Blender::Execute()
{
    unsigned char *pixel;                                                                           // Initialize the pixal variable 
    int i, j;

    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(factor < 0 || factor > 1)
    {
        char msg[1024];
        sprintf(msg, "%s: factor does not work: %f\n", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
        img.ResetSize(image1->GetWidth(), image1->GetHeight());

        memcpy(img.GetBuffer(), image1->GetBuffer(), 3*image1->GetWidth()*image1->GetHeight());         // Copy the image memory and create a new one

        for(i = 0; i < img.GetHeight(); i++)                                                         // For loop to set the pixel color down the diagonal 
        {
            for(j = 0; j < img.GetWidth(); j++)
            {                  
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0]*(1-factor));
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1]*(1-factor));
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2]*(1-factor));
            }
        }
    }
}

const char * Blender::FilterName()
{
    return "Blender";
}