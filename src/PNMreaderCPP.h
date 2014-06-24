#include <stdio.h>
#include "source.h"

#ifndef PNMREADERCPP_H
#define PNMREADERC_H

class PNMreaderCPP: public source
{
	protected:
	    char *filename;
	    
	public:
	    virtual void Execute();
	    PNMreaderCPP(char *filename);
};

#endif