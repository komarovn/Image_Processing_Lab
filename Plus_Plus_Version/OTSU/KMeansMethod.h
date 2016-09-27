#pragma once

#include "ImageProcessing.h"
#include <iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/mat.hpp>

#include <opencv\cv.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

class KMeansMethod : public ImageProcessing
{
private:
	int k;
	int* imageGrid;
	int* centresOfClusters;
public:
	Color CalculateNewPixelColor(int x, int y)
        {
            Color color = Color::Coral;
            return color;
        }

	KMeansMethod(Bitmap ^image) : ImageProcessing(image)
	{
		BitmapData ^bmpData = sourceImage->LockBits(Rectangle(0, 0, sourceImage->Width, sourceImage->Height), Imaging::ImageLockMode::ReadWrite, sourceImage->PixelFormat);
		cv::Mat src = cv::Mat::Mat(sourceImage->Height, sourceImage->Width, CV_8UC3, (void*)bmpData->Scan0, CV_AUTO_STEP);
		cv::Mat dest = src;
		
		try {
			cv::medianBlur(src, dest, 2);							// медианный фильтр для убирания шума, который влияет на метод k-средних
		}
		catch (System::Runtime::InteropServices::SEHException ^ex) {
			;
		}
		k = 2;													// число кластеров (задается пользователем в отдельном окне при вызове метода)
		int sizeOfImage = sourceImage->Height * sourceImage->Width;			// размер изображения
		imageGrid = new int[sizeOfImage];						// сетка, представляющая собой изображение
		centresOfClusters = new int[k];							// центры k кластеров
		for(int i = 0; i < k; i++)								// бросаем k точек на сетку случайным образом
		{
			int randomCell = rand() % (sizeOfImage);			// номер случайной клетки сетки
			centresOfClusters[i] = imageGrid[randomCell];		// центр кластера
		}

		sourceImage->UnlockBits(bmpData);
		Bitmap ^outputImage = gcnew Bitmap(dest.cols, dest.rows, 1, sourceImage->PixelFormat, (IntPtr)dest.data); // выходное изображение
	}

	~KMeansMethod() 
	{
		delete [] imageGrid;
		delete [] centresOfClusters;
	}
};