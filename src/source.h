#include "image.h"

#ifndef SOURCE_H
#define SOURCE_H

class source
{
	protected:
	    Image img;
	    virtual void Execute() = 0;

	public:
		virtual void Update();
	    Image * GetOutput();
	    void SetSource();
	    source();
};

#endif