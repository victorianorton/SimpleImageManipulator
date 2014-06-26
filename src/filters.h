#include "filter.h"
#include <stdio.h>

#ifndef FILTERS_H
#define FILTERS_H

class filters: public filter
{

};

class Shrinker: public filters
{
	public:
	    void Execute();
};

class LRConcat: public filters
{
	public:
	    void Execute();
};

class TBConcat: public filters
{
	public:
	    void Execute();
};

class Blender: public filters
{
	protected:
	    float factor;
	    
	public:
	    void SetFactor(float factor);
	    void Execute();
};

#endif