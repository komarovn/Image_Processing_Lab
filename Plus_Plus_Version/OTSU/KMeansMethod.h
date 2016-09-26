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
		k = 2;													// число кластеров (задается пользователем в отдельном окне при вызове метода)
		int sizeOfImage = image->Height * image->Width;			// размер изображения
		imageGrid = new int[sizeOfImage];						// сетка, представляющая собой изображение
		centresOfClusters = new int[k];							// центры k кластеров
		for(int i = 0; i < k; i++)								// бросаем k точек на сетку случайным образом
		{
			int randomCell = rand() % (sizeOfImage);			// номер случайной клетки сетки
			centresOfClusters[i] = imageGrid[randomCell];		// центр кластера
		}

	}

	~KMeansMethod() 
	{
		delete [] imageGrid;
		delete [] centresOfClusters;
	}
};