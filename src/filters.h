#include "filter.h"
#include <stdio.h>

#ifndef FILTERS_H
#define FILTERS_H

class Filters: public Filter
{

};

class Shrinker: public Filters
{
	public:
		const char * FilterName();
	    void Execute();
};

class LRConcat: public Filters
{
	public:
		const char * FilterName();
	    void Execute();
};

class TBConcat: public Filters
{
	public:
		const char * FilterName();
		void Execute();
};

class Blender: public Filters
{
	protected:
	    float factor;
	    
	public:
		const char * FilterName();
	    void SetFactor(float factor);
	    void Execute();
};

#endif