#include "source.h"
#include "sink.h"
#include <stdio.h>

#ifndef FILTER_H
#define FILTER_H

class filter: public source, public sink
{
	public:
		virtual void Update();
};

#endif