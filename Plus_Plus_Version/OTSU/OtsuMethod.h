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
        int* histogram;
		int dawn;
	protected:
		Color CalculateNewPixelColor(int x, int y)
        {
			int intens = (int)(0.2126 * sourceImage->GetPixel(x, y).R + 0.7152 * sourceImage->GetPixel(x, y).G + 0.0722 * sourceImage->GetPixel(x, y).B);
			int grayGrad = MakeBinarized(dawn, intens);
            Color color = Color::FromArgb(grayGrad, grayGrad, grayGrad);
            return color;
        }

	public:
		OtsuMethod(Bitmap ^image) : ImageProcessing(image)
        {
			CalculateHistogram();

			int disp = 0; // мат. ожидание 
			int summ = 0; // сумма высот

			for (int i = 0; i < 256; i++)
			{
				disp += i * histogram[i];
				summ += histogram[i];
			}

			float maxSigma = -1;
			dawn = 0; //порог

			int alpha1 = 0; // сумма высот 1-ого класса
			int beta1 = 0; //мат. ожидание 1-ого класса

			for (int i = 0; i < 256; i++)
			{
				alpha1 += i * histogram[i];
				beta1 += histogram[i];

				// —читаем веро€тность 1-ого класса.
				float probability_1 = (float)beta1 / summ;
				float a = (float)alpha1 / beta1 - (float)(disp - alpha1) / (summ - beta1);

				float sigma = probability_1 * (1 - probability_1) * a * a;

				if (sigma > maxSigma)
				{
					maxSigma = sigma;
					dawn = i;
				}
			}


        }

		~OtsuMethod()
		{
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