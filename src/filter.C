#include "filter.h"

void filter::Update()
{	
	if(image1 != NULL)
	{
		image1->Update();
	}
	if(image2 != NULL)
	{
		image2->Update();
	}	
	
	Execute();
}