#pragma once

#include "KMeansMethod.h"

class Downsampling 
{
private:
	int newWidth;
	int newHeight;
public:
	Downsampling(int width, int height)
	{
		newWidth = width;
		newHeight = height;
	}

};