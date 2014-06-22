#include "image.h"

#ifndef SINK_H
#define SINK_H

class sink
{
	protected:
	    Image * image1;
	    Image * image2;
	    
	public:
	    void SetInput(Image *image1);
	    void SetInput2(Image *image2);
	    sink();

};

#endif