#pragma once

#include "ImageProcessing.h"
#include "iostream"

#include <opencv\cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

class PixelOfImage			// пиксель исходого изображения
{
private:
	int red;
	int green;
	int blue;
	int intensity;			// интенсивность
	int *distances;			// массив из k элементов, i-й элемент - расстояние от пикселя до i-го кластера
	int numberOfCluster;	// принадлежность кластеру с номером numberOfCluster
public:
	PixelOfImage() {};

	PixelOfImage(cv::Vec3b color, int k)
	{
		red = color[2];
		green = color[1];
		blue = color[0];
		distances = new int[k];
	}

	~PixelOfImage() { delete [] distances; }

	int *GetDistances() { return distances; }

	int GetNumberOfCluster() { return numberOfCluster; }
};

class KMeansMethod : public ImageProcessing
{
private:
	int k;
	int* imageGrid;
	int* centresOfClusters;
	cv::Mat dest;
	PixelOfImage *pixels;
public:
	Color CalculateNewPixelColor(int x, int y) // метод не нужен!
        {
			Color color = outputImage->GetPixel(x, y);
			//Color color = outputImage.;
			//cv::Vec3b color = outputImage.at<cv::Vec3b>(cv::Point(x, y));
			//Color col = color.channels;
            return color;
        }

	KMeansMethod(Bitmap ^image, String ^filename, int k) : ImageProcessing(image) // k - число кластеров (задается пользователем в отдельном окне при вызове метода)
	{
		//BitmapData ^bmpData = sourceImage->LockBits(Rectangle(0, 0, sourceImage->Width, sourceImage->Height), Imaging::ImageLockMode::ReadWrite, sourceImage->PixelFormat);
		//cv::Mat src = cv::Mat::Mat(sourceImage->Height, sourceImage->Width, CV_8UC3, (void*)bmpData->Scan0, CV_AUTO_STEP);
		//sourceImage->UnlockBits(bmpData);
		cv::Mat src = cv::imread(SystemToStl(filename), CV_LOAD_IMAGE_COLOR);	// исходное изображение
		//cv::Mat dest;													// выходное изображение
		cv::medianBlur(src, dest, 3);									// медианный фильтр для убирания шума, который влияет на метод k-средних
		//int sizeOfImage = src.size;
		
		
		// Используется для оттенков серого, одномерного пространства векторов
		cv::Mat intensityMat;
		cv::cvtColor(dest, intensityMat, CV_BGR2GRAY);					// матрица интенсивностей


		int sizeOfImage = dest.cols * dest.rows;						// размер изображения
		//int **mask = new int*[k];										// массив, представляющий собой k слоев бинарных матриц; если элемент i-го слоя равен 0, то пиксель изображения не принадлежит кластеру i, если 1 - принадлежит; можно считать это неким базисом матриц k-мерного пространства
		//for(int i = 0; i < k; i++)
		//	mask[i] = new int[sizeOfImage];


		pixels = new PixelOfImage[sizeOfImage]; 
		// Используется для RGB, трехмерного пространства векторов
		for(int i = 0; i < dest.cols; i++)
			for(int j = 0; j < dest.rows; j++)
			{
				pixels[i * dest.rows + j] = PixelOfImage(dest.at<cv::Vec3b>(j, i), k);
			}
		
		
		imageGrid = new int[sizeOfImage];								// сетка, представляющая собой изображение
		centresOfClusters = new int[k];									// центры k кластеров
		int *prevCentresOfClusters = new int[k];						// центры кластеров на предыдущем шаге
		for(int i = 0; i < k; i++)										// бросаем k точек на сетку случайным образом
		{
			int randomCell = rand() % (sizeOfImage);					// номер случайной клетки сетки
			centresOfClusters[i] = imageGrid[randomCell];				// центр кластера
			prevCentresOfClusters[i] = centresOfClusters[i];
		}
		for(int i = 0; i < k; i++)
		{
			while(prevCentresOfClusters[i] != centresOfClusters[i])		// делаем алгоритм, пока центры кластеров не перестанут двигаться
			{
				;
			}
		}

		
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