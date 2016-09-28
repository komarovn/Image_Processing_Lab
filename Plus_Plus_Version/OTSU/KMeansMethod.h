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
	gcroot <Bitmap^> outputImage;
	//cv::Mat outputImage;
public:
	Color CalculateNewPixelColor(int x, int y)
        {
			Color color = outputImage->GetPixel(x, y);
			//Color color = outputImage.;
			//cv::Vec3b color = outputImage.at<cv::Vec3b>(cv::Point(x, y));
			//Color col = color.channels;
            return color;
        }

	string SystemToStl(String ^s) // ������� ���� String ^ � ��� string
	{
		using namespace Runtime::InteropServices;
		const char* ptr = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		return string(ptr);
	};

	KMeansMethod(Bitmap ^image, String ^filename) : ImageProcessing(image)
	{
		//BitmapData ^bmpData = sourceImage->LockBits(Rectangle(0, 0, sourceImage->Width, sourceImage->Height), Imaging::ImageLockMode::ReadWrite, sourceImage->PixelFormat);
		//cv::Mat src = cv::Mat::Mat(sourceImage->Height, sourceImage->Width, CV_8UC3, (void*)bmpData->Scan0, CV_AUTO_STEP);
		cv::Mat src = cv::imread(SystemToStl(filename));		// �������� �����������
		cv::Mat dest;											// �������� �����������
		try {
			cv::medianBlur(src, dest, 2);						// ��������� ������ ��� �������� ����, ������� ������ �� ����� k-�������
		}
		catch (System::Runtime::InteropServices::SEHException ^ex) {
			;
		}
		k = 2;													// ����� ��������� (�������� ������������� � ��������� ���� ��� ������ ������)
		//int sizeOfImage = src.size;
		int sizeOfImage = sourceImage->Height * sourceImage->Width;			// ������ �����������
		imageGrid = new int[sizeOfImage];						// �����, �������������� ����� �����������
		centresOfClusters = new int[k];							// ������ k ���������
		for(int i = 0; i < k; i++)								// ������� k ����� �� ����� ��������� �������
		{
			int randomCell = rand() % (sizeOfImage);			// ����� ��������� ������ �����
			centresOfClusters[i] = imageGrid[randomCell];		// ����� ��������
		}

		//sourceImage->UnlockBits(bmpData);
		outputImage = gcnew Bitmap(dest.cols, dest.rows, dest.step, sourceImage->PixelFormat, (IntPtr)dest.data); // �������� �����������
		//outputImage = dest;
	}

	~KMeansMethod() 
	{
		delete [] imageGrid;
		delete [] centresOfClusters;
	}
};