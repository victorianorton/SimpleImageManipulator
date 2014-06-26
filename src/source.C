#include <stdio.h>
#include "image.h"
#include "source.h"

Image * source::GetOutput()
{
	return &img;
}

void source::Update()
{
	Execute();
}

source::source()
{
	img.SetSource(this);
};