#include <stdio.h>
#include "source.h"

#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader: public source
{
	protected:
	    char *filename;
	    
	public:
	    virtual void Execute();
	    PNMreader(char *filename);
};

#endif