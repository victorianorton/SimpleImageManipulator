#include "image.h"

#ifndef SINK_H
#define SINK_H

class sink
{
	protected:
	    const Image *image1;
	   	const Image *image2;
	    
	public:
	    void SetInput( Image *image1);
	    void SetInput2( Image *image2);
	    sink();
};

#endif