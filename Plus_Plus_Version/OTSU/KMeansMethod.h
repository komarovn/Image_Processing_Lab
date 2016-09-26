#pragma once

#include "ImageProcessing.h"

#include <opencv\cv.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class KMeansMethod : public ImageProcessing
{
public:
	Color CalculateNewPixelColor(int x, int y)
        {
            Color color = Color::Coral;
            return color;
        }
	KMeansMethod(Bitmap ^image) : ImageProcessing(image)
	{
		// TODO: write here something
	}
};