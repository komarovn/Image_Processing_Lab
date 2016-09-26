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
		k = 2;													// ����� ��������� (�������� ������������� � ��������� ���� ��� ������ ������)
		int sizeOfImage = image->Height * image->Width;			// ������ �����������
		imageGrid = new int[sizeOfImage];						// �����, �������������� ����� �����������
		centresOfClusters = new int[k];							// ������ k ���������
		for(int i = 0; i < k; i++)								// ������� k ����� �� ����� ��������� �������
		{
			int randomCell = rand() % (sizeOfImage);			// ����� ��������� ������ �����
			centresOfClusters[i] = imageGrid[randomCell];		// ����� ��������
		}

	}

	~KMeansMethod() 
	{
		delete [] imageGrid;
		delete [] centresOfClusters;
	}
};