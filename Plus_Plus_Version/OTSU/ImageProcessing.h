#pragma once

#include <vcclr.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


class ImageProcessing abstract 
{
protected: 
	gcroot <Bitmap> sourceImage;
	virtual Color CalculateNewPixelColor(int x, int y) = 0;

public:
	int Clamp(int value, int max, int min) 
	{
		if(value > max) return max;
		if(value < min) return min;
		return value;
	}

public:
	ImageProcessing(Bitmap ^image)
        {
            sourceImage = image;
        }

public:
	Bitmap^ ProcessImage()
	{
		Bitmap^ resultImage = gcnew Bitmap(sourseImage->Width, sourseImage->Height);
		for (int i = 0; i < sourseImage->Width; i++)
		{
			for (int j = 0; j < sourseImage->Height; j++)
			{
				resultImage->SetPixel(i, j, CalculateNewPixelColor(i, j));
			}
		}
		return resultImage;
	}
};


// ��� �� ���� �� ����� ������ 
class GrayScaleFilter: protected ImageProcessing 
{
	Color calculateNewPixelColor(int x, int y) 
	{
		Color^ sourseColor = sourseImage->GetPixel(x, y);
		int Intensity = (int)(0.36 * sourseColor->R + 0.53 * sourseColor->G + 0.11 * sourseColor->B);
		Color resulteColor = Color().FromArgb(Intensity, Intensity, Intensity);
		return resulteColor;
	}
};