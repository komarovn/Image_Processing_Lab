#pragma once

#include "ImageProcessing.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class OtsuMethod : public ImageProcessing
    {
	private:
		//int* intensityArray;
        int* histogram;

		/*void CalculateIntensity()
        {
            int sizeOfArray = sourceImage->Height * sourceImage->Width;
            intensityArray = new int[sizeOfArray];
            for (int i = 0; i < sourceImage->Height; i++)
                for (int j = 0; j < sourceImage->Width; j++)
                    intensityArray[i * sourceImage->Width + j] = (int)(0.2126 * sourceImage->GetPixel(j, i).R + 0.7152 * sourceImage->GetPixel(j, i).G + 0.0722 * sourceImage->GetPixel(j, i).B);
        }*/
	protected:
		Color CalculateNewPixelColor(int x, int y)
        {
            //int grayGrad = intensityArray[(y + 1) * sourceImage->Width + x];
			int grayGrad = 45;
            Color color = Color::FromArgb(grayGrad, grayGrad, grayGrad);
            // TODO : write method
            return color;
        }

	public:
		OtsuMethod(Bitmap ^image) : ImageProcessing(image)
        {
            //CalculateIntensity();
			CalculateHistogram();
        }

		~OtsuMethod()
		{
			//delete[] intensityArray;
			delete[] histogram;
		}

	private:
		void CalculateHistogram()
        {
            histogram = new int[256];
            for (int i = 0; i < 256; i++)
                histogram[i] = 0;
            for (int i = 0; i < sourceImage->Height; i++)
                for (int j = 0; j < sourceImage->Width; j++)
                {
                    int index = (int)(0.2126 * sourceImage->GetPixel(j, i).R + 0.7152 * sourceImage->GetPixel(j, i).G + 0.0722 * sourceImage->GetPixel(j, i).B);
                    histogram[index]++;
                }
        }

	public:
		int MakeBinarized(int thereshold, int value)
        {
            if (thereshold > value)
                return 0;
            else
                return 255;
        }

    };