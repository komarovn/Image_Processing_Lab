#pragma once

#include "ImageProcessing.h"
#include "iostream"

#include <opencv/cv.h>
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

class PixelOfImage			// ������� �������� �����������
{
private:
	int red;
	int green;
	int blue;
	int intensity;			// �������������
	double *distances;		// ������ �� k ���������, i-� ������� - ���������� �� ������� �� i-�� ��������
	int numberOfCluster;	// �������������� �������� � ������� numberOfCluster
	int numClusters;        // ���������� ���������;
	int x, y;               // ���������� �������

public:

	PixelOfImage() 
	{
		red                   = 0;
		green                 = 0;
		blue                  = 0;
		intensity             = 0;
		numberOfCluster       = 0;
		numClusters           = 0;
		distances = new double[1];
	};

	PixelOfImage(const PixelOfImage &a)
	{
		red				= a.red;
		green			= a.green;
		blue			= a.blue;
		intensity		= a.intensity;
		numberOfCluster = a.numberOfCluster;
		numClusters		= a.numClusters;
		x				= a.x;
		y				= a.y;

		delete[] distances;
		distances = new double[numClusters];

		for(int i=0; i<numClusters; i++)
		{
			distances[i] = (a.distances)[i];
		}


	}

	PixelOfImage(cv::Vec3b color, int x0, int y0, int numCl)
	{
		intensity		= 0;
		numberOfCluster = 0;
		red				= color[2];
		green			= color[1];
		blue			= color[0];
		distances		= new double[numCl];
		x				= x0; 
		y				= y0;
		numClusters		= numCl;
	}

	~PixelOfImage() 
	{ 
		delete [] distances; 
	}

	double *GetDistances() 
	{ 
		return distances; 
	}

	double GetDistance(int positionInDistancesArray) 
	{
		if(positionInDistancesArray < 0 || positionInDistancesArray > numClusters)
			return -1;
		return distances[positionInDistancesArray];
	}

	void SetDistance(int positionInDistancesArray, double value)
	{
		if(positionInDistancesArray < 0 || positionInDistancesArray > numClusters)
			return;
		distances[positionInDistancesArray] = value;
	}

	int GetX() { return x; }

	int GetY() { return y; }

	int GetR() { return red; }

	int GetG() { return green; }

	int GetB() { return blue; }

	int GetNumberOfCluster() { return numberOfCluster; }

	void SetNumberOfCluster(int Cluster) { numberOfCluster = Cluster; }

	bool operator==(PixelOfImage const & a)
	{
		bool flag = false;
		if ((x == a.x) && (y == a.y)) flag = true;

		return flag;
	}

	bool operator!=(PixelOfImage const & a)
	{
		bool flag = false;
		if((x != a.x)||(y != a.y)) flag = true;
		
		return flag;
	}

	PixelOfImage& operator=(PixelOfImage &elem) //���������� ��������� ������������
	{
		red = elem.red;
		green = elem.green;
		blue = elem.blue;
		intensity = elem.intensity;
		numberOfCluster = elem.numberOfCluster;
		x = elem.x; 
		y = elem.y;
		numClusters = elem.numClusters;

		delete[] distances;
		distances = new double[numClusters];
		
		for (int i = 0; i < numClusters; i++)
		{
			distances[i] = (elem.distances)[i];
		}

		return *this;
	}
};

class KMeansMethod : public ImageProcessing
{
private:
	int k;								// k - ����� ��������� (�������� ������������� � ��������� ���� ��� ������ ������)
	PixelOfImage* centresOfClusters;	// ������ k ���������
	cv::Mat dest;						// �������� �����������
	PixelOfImage *pixels;				// ������� �����������

public:
	Color CalculateNewPixelColor(int x, int y) // ����� �� �����!
        {
			Color color = outputImage->GetPixel(x, y);
            return color;
        }

	KMeansMethod(Bitmap ^image, String ^filename, int kInput) : ImageProcessing(image)
	{
		k = kInput;
		//BitmapData ^bmpData = sourceImage->LockBits(Rectangle(0, 0, sourceImage->Width, sourceImage->Height), Imaging::ImageLockMode::ReadWrite, sourceImage->PixelFormat);
		//cv::Mat src = cv::Mat::Mat(sourceImage->Height, sourceImage->Width, CV_8UC3, (void*)bmpData->Scan0, CV_AUTO_STEP);
		//sourceImage->UnlockBits(bmpData);
		cv::Mat src = cv::imread(SystemToStl(filename), CV_LOAD_IMAGE_COLOR);	// �������� �����������
		cv::medianBlur(src, dest, 3);									// ��������� ������ ��� �������� ����, ������� ������ �� ����� k-�������
		
		// ������������ ��� �������� ������, ����������� ������������ ��������
		//cv::Mat intensityMat;
		//cv::cvtColor(dest, intensityMat, CV_BGR2GRAY);				// ������� ��������������
		
		int sizeOfImage = dest.cols * dest.rows;						// ������ �����������
		pixels = new PixelOfImage[sizeOfImage]; 
		// ������������ ��� RGB, ����������� ������������ ��������
		for(int i = 0; i < dest.cols; i++)
			for(int j = 0; j < dest.rows; j++)
			{
				pixels[i * dest.rows + j] = PixelOfImage(dest.at<cv::Vec3b>(j, i), i, j, k);
			}
		
		centresOfClusters = new PixelOfImage[k];
		PixelOfImage* prevCentresOfClusters = new PixelOfImage[k];		// ������ ��������� �� ���������� ����

		for(int i = 0; i < k; i++)										// ������� k ����� �� ����������� ��������� �������
		{
			int randomCell = rand() % sizeOfImage;						// ����� ���������� �������
			centresOfClusters[i] = pixels[randomCell];				    // ����� ��������
			prevCentresOfClusters[i] = centresOfClusters[i];
		}


		//--------------------------------------------------------------//
		// ������ ��������, ���� ������ ��������� �� ���������� ���������
		//--------------------------------------------------------------//

		int ggg = 0;
		while(ggg != 50)		
		{
			//--------------------------------------------------------------// 
			// �������� ���������� �� ������� �� ������� ������ �������� � RGB �������
			//--------------------------------------------------------------//
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < sizeOfImage; j++)
					pixels[j].SetDistance(i, sqrt(
						(pixels[j].GetR() - prevCentresOfClusters[i].GetR()) * (pixels[j].GetR() - prevCentresOfClusters[i].GetR()) +
						(pixels[j].GetG() - prevCentresOfClusters[i].GetG()) * (pixels[j].GetR() - prevCentresOfClusters[i].GetG()) +
						(pixels[j].GetB() - prevCentresOfClusters[i].GetB()) * (pixels[j].GetB() - prevCentresOfClusters[i].GetB()) ));
			}	
			//--------------------------------------------------------------// 
			// ������������� �������� �� ���������
			//--------------------------------------------------------------//
			for (int i = 0; i < sizeOfImage; i++)
			{
				double minDist = sizeof(double); int minCluster = 0;     // ����������� ���������� �� �������� � ����� ����� ��������

				for (int j = 0; j < k; j++)
				{
					if ( minDist > pixels[i].GetDistance(j) )
					{
						minDist = pixels[i].GetDistance(j);
						minCluster = j;
					}
				}

				pixels[i].SetNumberOfCluster(minCluster);
			}

			//--------------------------------------------------------------// 
			// �������� ������� ��������� � RGB �������
			//--------------------------------------------------------------//	
			long int* sumClusterRed   = new long int[k];        // ����� Red ������ � ������ ��������
			long int* sumClusterGreen = new long int[k];		// ����� Green ������ � ������ ��������
			long int* sumClusterBlue  = new long int[k];		// ����� Blue ������ � ������ ��������
			long int* numElemCluster  = new long int[k];		// ���������� ��������� � ������ ��������

			for (int i = 0; i < k; i++)
			{
				sumClusterRed[i]   = 0; 
				sumClusterGreen[i] = 0;
				sumClusterBlue[i]  = 0; 
				numElemCluster[i]  = 0;

				for (int j = 0; j < sizeOfImage; j++)
				{
					if (pixels[j].GetNumberOfCluster() == i)
					{
						sumClusterRed[i]   += pixels[j].GetR();
						sumClusterGreen[i] += pixels[j].GetG();
						sumClusterBlue[i]  += pixels[j].GetB();
						numElemCluster[i]++;
					}
				}

				double averageRed   = (double)(sumClusterRed[i]  ) / (double)(numElemCluster[i]);		// ������� Red ������ � ��������   i
				double averageGreen = (double)(sumClusterGreen[i]) / (double)(numElemCluster[i]);	    // ������� Green ������ � �������� i
				double averageBlue  = (double)(sumClusterBlue[i] ) / (double)(numElemCluster[i]);		// ������� Blue ������ � ��������  i

				double minDist = sizeof(double);

				for (int j = 0; j < sizeOfImage; j++)
				{
					if (pixels[j].GetNumberOfCluster() == i)
					{
						double dist = sqrt(
							(pixels[j].GetR() - averageRed  ) * (pixels[j].GetR() - averageRed  ) +
							(pixels[j].GetG() - averageGreen) * (pixels[j].GetR() - averageGreen) +
							(pixels[j].GetB() - averageBlue ) * (pixels[j].GetB() - averageBlue ) );

						if (minDist > dist)
						{
							minDist = dist;
							centresOfClusters[i] = pixels[j];
						}
					}
				}
				
			}
			//--------------------------------------------------------------// 
			// ����� �� ������� �����, ���� ������ ��������� �� ��������
			//--------------------------------------------------------------//
			/*bool flag = true;

			for (int i = 0; i < k; i++)
			{
				if (centresOfClusters[i] != prevCentresOfClusters[i]) 
				{
					flag = false;
					break;
				}
			}

			if (flag) 
				break;

			else
			{
				for (int i = 0; i < k; i++)
				{
					prevCentresOfClusters[i] = centresOfClusters[i];
				}
			}*/
			ggg++;
			//--------------------------------------------------------------//

		}

		outputImage = CreateOutputImage(); // �������� �����������
		delete [] prevCentresOfClusters;
	}

	Bitmap^ CreateOutputImage() {
		if(pixels == NULL)
			return gcnew Bitmap(1, 1);
		Bitmap ^image = gcnew Bitmap(sourceImage->Width, sourceImage->Height);
		int red;
		int green;
		int blue;
		Color color;

		long int* ClasterRedPart   = new long int[k];
		long int* ClasterBluePart  = new long int[k];
		long int* ClasterGreenPart = new long int[k];

		int pixelCount = sourceImage->Width * sourceImage->Height;
		for(int j = 0; j < k; j++)
		{
			ClasterRedPart[j]   = 0;
			ClasterGreenPart[j] = 0;
			ClasterBluePart[j]  = 0;
		}

		for(int i = 0; i < pixelCount; i++)
		{
			int NumberOfCluster = pixels[i].GetNumberOfCluster();
			
			ClasterRedPart[NumberOfCluster]   += pixels[i].GetR();
			ClasterGreenPart[NumberOfCluster] += pixels[i].GetG();
			ClasterBluePart[NumberOfCluster]  += pixels[i].GetB();
		}

		for(int j = 0; j < k; j++)
		{
			ClasterRedPart[j]   = ClasterRedPart[j]   / pixelCount;
			ClasterGreenPart[j] = ClasterGreenPart[j] / pixelCount;
			ClasterBluePart[j]  = ClasterBluePart[j]  / pixelCount;
		}

		for(int i = 0; i < sourceImage->Width; i++)
			for(int j = 0; j < sourceImage->Height; j++)
			{
				int NumberOfCluster = pixels[i + j * sourceImage->Width].GetNumberOfCluster();

				color = Color::FromArgb(ClasterRedPart[NumberOfCluster],
										ClasterGreenPart[NumberOfCluster],
										ClasterBluePart[NumberOfCluster]);
				image->SetPixel(i, j, color);
			}
		return image;
	}

	~KMeansMethod() 
	{
		delete [] centresOfClusters;
	}
};