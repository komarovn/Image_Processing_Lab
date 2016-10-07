#pragma once

#include "iostream"
#include <time.h>
#include <limits.h>
#include <vcclr.h>
#include <string>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include "specialFacilities.h"
#include <stdlib.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace std;

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
	}

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
		for(int i = 0; i < numClusters; i++)
			distances[i] = (a.distances)[i];
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
		if((red == a.red) && (blue == a.blue) && (green == a.green))
			return true;
		else
			return false;
	}

	bool operator!=(PixelOfImage const & a)
	{
		if((red == a.red) && (blue == a.blue) && (green == a.green))
			return false;
		else
			return true;
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
			distances[i] = (elem.distances)[i];
		return *this;
	}
};

class KMeansMethod
{
private:
	int k;								// k - ����� ��������� (�������� ������������� � ��������� ���� ��� ������ ������)
	PixelOfImage* centresOfClusters;	// ������ k ���������
	cv::Mat dest;						
	PixelOfImage *pixels;				// ������� �����������
	gcroot <Bitmap^> outputImage;		// �������� �����������
	int sizeOfImage;					// ������ �����������
public:
	KMeansMethod(String ^filename, int kInput)
	{
		
		cv::Mat src = cv::imread(SystemToStl(filename), CV_LOAD_IMAGE_COLOR);	// �������� �����������
		cv::medianBlur(src, dest, 3);											// ��������� ������ ��� �������� ����, ������� ������ �� ����� k-�������

		gcroot <Bitmap^> tmp_img = gcnew Bitmap(filename);
		int *histogram = new int[256];

		for (int i = 0; i < 256; i++) { histogram[i] = 0; }			

		if (kInput == -2)
		{
			for (int i = 0; i < tmp_img->Width; i++)
				for (int j = 0; j < tmp_img->Height; j++)
				{
					int intensity = (int)(
						0.2126 * tmp_img->GetPixel(i, j).R +
						0.7152 * tmp_img->GetPixel(i, j).G +
						0.0722 * tmp_img->GetPixel(i, j).B);
					histogram[intensity]++;
				}

			int delta = 10; k = 1;
			for (int i = delta; i < 256 - delta; i++)
				if ((histogram[i - delta] < histogram[i]) &&
					(histogram[i + delta] < histogram[i]))
				{
					k++; i = i + delta;
				}

		}
		else
			k = kInput;
		
		
		sizeOfImage = dest.cols * dest.rows;
		pixels = new PixelOfImage[sizeOfImage]; 

		//--------------------------------------------------------------//
		// ������������ ��� RGB, ����������� ������������ ��������
		//--------------------------------------------------------------//
		for(int i = 0; i < dest.cols; i++)
			for(int j = 0; j < dest.rows; j++)
			{
				pixels[j * dest.cols + i] = PixelOfImage(dest.at<cv::Vec3b>(j, i), i, j, k);
			}
		
		centresOfClusters = new PixelOfImage[k];
		
		//--------------------------------------------------------------//
		// �������� ������ ��� ��������� ������
		//--------------------------------------------------------------//	
		double* averageRed		  = new double[k];
		double* averageGreen	  = new double[k];		
		double* averageBlue		  = new double[k];
		double* minDist			  = new double[k];
		double* Dist			  = new double[k];
		long int* sumClusterRed   = new long int[k];					 // ����� Red ������ � ������ ��������
		long int* sumClusterGreen = new long int[k];					 // ����� Green ������ � ������ ��������
		long int* sumClusterBlue  = new long int[k];					 // ����� Blue ������ � ������ ��������
		long int* numElemCluster  = new long int[k];					 // ���������� ��������� � ������ ��������
		PixelOfImage* prevCentresOfClusters = new PixelOfImage[k];		 // ������ ��������� �� ���������� ����
		PixelOfImage* TMP;

		for(int i = 0; i < k; i++)										 // ������� k ����� �� ����������� ��������� �������
		{
			centresOfClusters[i] = pixels[rand() % sizeOfImage];		 // ����� ��������
		}
		
		TMP = prevCentresOfClusters; 
		prevCentresOfClusters = centresOfClusters;
		centresOfClusters = TMP;

		//--------------------------------------------------------------//
		// ������ ��������, ���� ������ ��������� �� ���������� ���������
		//--------------------------------------------------------------//
		while(true)		
		{
			//--------------------------------------------------------------// 
			// �������� ���������� �� ������� �� ������� ������ �������� � RGB �������
			//--------------------------------------------------------------//
			for (int i = 0; i < k; i++)
			{
				for (int j = 0; j < sizeOfImage; j++)
					pixels[j].SetDistance(i, sqrt(
						(pixels[j].GetR() - prevCentresOfClusters[i].GetR()) * (pixels[j].GetR() - prevCentresOfClusters[i].GetR()) +
						(pixels[j].GetG() - prevCentresOfClusters[i].GetG()) * (pixels[j].GetG() - prevCentresOfClusters[i].GetG()) +
						(pixels[j].GetB() - prevCentresOfClusters[i].GetB()) * (pixels[j].GetB() - prevCentresOfClusters[i].GetB()) ));
			}	

			//--------------------------------------------------------------// 
			// ������������� �������� �� ���������
			//--------------------------------------------------------------//
			for (int i = 0; i < sizeOfImage; i++)
			{
				double minDist = INT_MAX; int minCluster = 0;     // ����������� ���������� �� �������� � ����� ����� ��������

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
			for (int i = 0; i < k; i++)
			{
				sumClusterRed[i]   = 0; 
				sumClusterGreen[i] = 0;
				sumClusterBlue[i]  = 0; 
				numElemCluster[i]  = 0;
			}

			for (int j = 0; j < sizeOfImage; j++)
			{
				int NumberOfCluster = pixels[j].GetNumberOfCluster();
				sumClusterRed[NumberOfCluster]   += pixels[j].GetR();
				sumClusterGreen[NumberOfCluster] += pixels[j].GetG();
				sumClusterBlue[NumberOfCluster]  += pixels[j].GetB();
				numElemCluster[NumberOfCluster]++;
			}
			for (int i = 0; i < k; i++)
			{
				averageRed[i]   = (double)(sumClusterRed[i]  ) / (double)(numElemCluster[i]);		// ������� Red ������ � ��������   i
				averageGreen[i] = (double)(sumClusterGreen[i]) / (double)(numElemCluster[i]);	    // ������� Green ������ � �������� i
				averageBlue[i]  = (double)(sumClusterBlue[i] ) / (double)(numElemCluster[i]);		// ������� Blue ������ � ��������  i
				minDist[i]      = INT_MAX;
			}

			for (int j = 0; j < sizeOfImage; j++)
			{
				int NumberOfCluster = pixels[j].GetNumberOfCluster();
				Dist[NumberOfCluster] = sqrt(
					(pixels[j].GetR() - averageRed[NumberOfCluster]  ) * (pixels[j].GetR() - averageRed[NumberOfCluster]  ) +
					(pixels[j].GetG() - averageGreen[NumberOfCluster]) * (pixels[j].GetG() - averageGreen[NumberOfCluster]) +
					(pixels[j].GetB() - averageBlue[NumberOfCluster] ) * (pixels[j].GetB() - averageBlue[NumberOfCluster] ) );

				if (minDist[NumberOfCluster] > Dist[NumberOfCluster])
				{
					minDist[NumberOfCluster] = Dist[NumberOfCluster];
					centresOfClusters[NumberOfCluster] = pixels[j];
				}
			}	

    
			//--------------------------------------------------------------// 
			// ����� �� ������� �����, ���� ������ ��������� �� ��������
			//--------------------------------------------------------------//			
			bool flag = true;

			for (int i = 0; i < k; i++)
			{
				if (centresOfClusters[i] != prevCentresOfClusters[i]) 
				{
					flag = false;
					break;
				}
			}

			if(flag) break;
		
			TMP = prevCentresOfClusters;
			prevCentresOfClusters = centresOfClusters;
			centresOfClusters = TMP;
		}

		//--------------------------------------------------------------// 
		// ��������� ������ ���������
		//--------------------------------------------------------------//	
		delete[] averageRed				;   
		delete[] averageGreen			; 	
		delete[] averageBlue			; 
		delete[] minDist				;		 
		delete[] Dist					;    
		delete[] prevCentresOfClusters	;
		delete[] sumClusterRed			;  				
		delete[] sumClusterGreen		; 					
		delete[] sumClusterBlue			; 					
		delete[] numElemCluster			;  

		outputImage = CreateOutputImage();
	}

	Bitmap^ CreateOutputImage() 
	{
		if(pixels == NULL) return gcnew Bitmap(1, 1);

		Bitmap ^image = gcnew Bitmap(dest.cols, dest.rows);
		Color color;

		long int* ClasterRedPart   = new long int[k];
		long int* ClasterBluePart  = new long int[k];
		long int* ClasterGreenPart = new long int[k];
		long int* pixelsInClasters = new long int[k];

		for(int j = 0; j < k; j++)
		{
			ClasterRedPart[j]   = 0;
			ClasterGreenPart[j] = 0;
			ClasterBluePart[j]  = 0;
			pixelsInClasters[j] = 0;
		}

		for(int i = 0; i < sizeOfImage; i++)
		{
			int NumberOfCluster = pixels[i].GetNumberOfCluster();
			
			ClasterRedPart[NumberOfCluster]   += pixels[i].GetR();
			ClasterGreenPart[NumberOfCluster] += pixels[i].GetG();
			ClasterBluePart[NumberOfCluster]  += pixels[i].GetB();
			pixelsInClasters[NumberOfCluster] ++;
		}

		for(int j = 0; j < k; j++)
		{
			if(pixelsInClasters[j]!=0)
			{
				ClasterRedPart[j]   = ClasterRedPart[j]   / pixelsInClasters[j];
				ClasterGreenPart[j] = ClasterGreenPart[j] / pixelsInClasters[j];
				ClasterBluePart[j]  = ClasterBluePart[j]  / pixelsInClasters[j];
			}
		}

		for(int i = 0; i < dest.cols; i++)
			for(int j = 0; j < dest.rows; j++)
			{
				int NumberOfCluster = pixels[i + j * dest.cols].GetNumberOfCluster();

				color = Color::FromArgb(ClasterRedPart[NumberOfCluster],
										ClasterGreenPart[NumberOfCluster],
										ClasterBluePart[NumberOfCluster]);

				image->SetPixel(i, j, color);
			}

		delete[] ClasterRedPart;
		delete[] ClasterBluePart;
		delete[] ClasterGreenPart;
		delete[] pixelsInClasters;

		return image;
	}

	Bitmap ^OutputImage() 
	{
		return outputImage;
	}

	~KMeansMethod() 
	{
		delete [] centresOfClusters;
	}
};