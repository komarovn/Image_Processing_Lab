#pragma once

#include "ImageProcessing.h"
#include "iostream"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/mat.hpp>
#include <string>

#include <opencv\cv.h>
using namespace std;

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
	cv::Mat dest;
public:
	Color CalculateNewPixelColor(int x, int y)
        {
			Color color = outputImage->GetPixel(x, y);
			//Color color = outputImage.;
			//cv::Vec3b color = outputImage.at<cv::Vec3b>(cv::Point(x, y));
			//Color col = color.channels;
            return color;
        }

	string SystemToStl(String ^s) // Перевод типа String ^ в тип string
	{
		using namespace Runtime::InteropServices;
		const char* ptr = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		return string(ptr);
	};

	KMeansMethod(Bitmap ^image, String ^filename) : ImageProcessing(image)
	{
		//BitmapData ^bmpData = sourceImage->LockBits(Rectangle(0, 0, sourceImage->Width, sourceImage->Height), Imaging::ImageLockMode::ReadWrite, sourceImage->PixelFormat);
		//cv::Mat src = cv::Mat::Mat(sourceImage->Height, sourceImage->Width, CV_8UC3, (void*)bmpData->Scan0, CV_AUTO_STEP);
		cv::Mat src = cv::imread(SystemToStl(filename), CV_LOAD_IMAGE_COLOR);		// исходное изображение
		//cv::Mat dest;											// выходное изображение
		try {
			cv::medianBlur(src, dest, 3);						// медианный фильтр для убирания шума, который влияет на метод k-средних
		}
		catch (System::Runtime::InteropServices::SEHException ^ex) {
			;
		}
		k = 2;													// число кластеров (задается пользователем в отдельном окне при вызове метода)
		//int sizeOfImage = src.size;
		int sizeOfImage = sourceImage->Height * sourceImage->Width;			// размер изображения
		imageGrid = new int[sizeOfImage];						// сетка, представляющая собой изображение
		centresOfClusters = new int[k];							// центры k кластеров
		int *prevCentresOfClusters = new int[k];				// центры кластеров на предыдущем шаге
		for(int i = 0; i < k; i++)								// бросаем k точек на сетку случайным образом
		{
			int randomCell = rand() % (sizeOfImage);			// номер случайной клетки сетки
			centresOfClusters[i] = imageGrid[randomCell];		// центр кластера
			prevCentresOfClusters[i] = centresOfClusters[i];
		}
		for(int i = 0; i < k; i++)
		{
			while(prevCentresOfClusters[i] != centresOfClusters[i]) // делаем алгоритм, пока центры кластеров не перестанут двигаться
			{
				;
			}
		}

		//sourceImage->UnlockBits(bmpData);
		//outputImage = gcnew Bitmap(dest.cols, dest.rows, dest.step, sourceImage->PixelFormat, (IntPtr)dest.data); // выходное изображение
		//outputImage = dest;
		outputImage = CreateOutputImage();
		delete [] prevCentresOfClusters;
	}

	Bitmap ^CreateOutputImage() {
		Bitmap ^image = gcnew Bitmap(sourceImage->Width, sourceImage->Height);
		int red;
		int green;
		int blue;
		Color color;
		for(int i = 0; i < sourceImage->Width; i++)
			for(int j = 0; j < sourceImage->Height; j++)
			{
				red = dest.at<cv::Vec3b>(j, i)[2];
				green = dest.at<cv::Vec3b>(j, i)[1];
				blue = dest.at<cv::Vec3b>(j, i)[0];
				color = Color::FromArgb(red, green, blue);
				image->SetPixel(i, j, color);
			}
		return image;
	}

	~KMeansMethod() 
	{
		delete [] imageGrid;
		delete [] centresOfClusters;
	}
};