#pragma once

#include "KMeansMethod.h"

class Downsampling 
{
private:
	int newWidth;
	int newHeight;
	int oldWidth;
	int oldHeight;
	string filename;
	cv::Mat image;
public:
	Downsampling(int width, int height, string filename)
	{
		newWidth = width;
		newHeight = height;
		image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
		oldWidth = image.cols;
		oldHeight = image.rows;
		gaussianBlur();
		subsample();
	}

	void gaussianBlur() 
	{
		cv::Mat dest = image;
		double sigma = getSigmaForGaussianBlur();

		int widthOfKernel = oldWidth / newWidth;
		int heightOfKernel = oldHeight / newHeight;
		if(widthOfKernel % 2 == 0)
			widthOfKernel += 1;
		if(heightOfKernel % 2 == 0)
			heightOfKernel += 1;

		cv::GaussianBlur(image, dest, cv::Size(widthOfKernel, heightOfKernel), sigma, sigma);
		image = dest;
	}

	void subsample()
	{
		cv::Mat dest = cv::Mat(newHeight, newWidth, CV_8UC3);
		float aspectCoeffW = (float)oldWidth  / newWidth;
		float aspectCoeffH = (float)oldHeight / newHeight;
		for(int i = 1; i < newWidth; i++)
		{
			for(int j = 1; j < newHeight; j++)
			{
				int y = j * aspectCoeffH - 1;				
				int x = i * aspectCoeffW- 1;				
				dest.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(y, x);
			}
		}
		image = dest;
	}

	double getSigmaForGaussianBlur()
	{
		int intensity[256];

		for (int i = 0; i < 256; i++)
			intensity[i] = 0;

		for (int i = 0; i < image.cols; i++)
		{
			for (int j = 0; j < image.rows; j++)
			{
				int red = image.at<cv::Vec3b>(j, i)[2];
				int green = image.at<cv::Vec3b>(j, i)[1];
				int blue = image.at<cv::Vec3b>(j, i)[0];
				int ints = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
				intensity[ints]++;
			}
		}

		double mExp = 0;
		int num = 0;
		for (int i = 0; i < 256; i++)
		{
			mExp += i * intensity[i];
			num += intensity[i];
		}
		mExp = mExp / num;

		double disp = 0;
		for (int i = 0; i < 256; i++)
			disp += intensity[i] * (i - mExp) * (i - mExp);
		disp = disp / num;
		double sigma = sqrt(disp * ((double)num / (double)(num - 1)));
		return sigma;
	}

	Bitmap ^getImage()
	{
		Bitmap ^outputImage = gcnew Bitmap(image.cols, image.rows);
		int red;
		int green;
		int blue;
		Color c;
		for(int i = 0; i < image.cols; i++)
		{
			for(int j = 0; j < image.rows; j++)
			{
				red = image.at<cv::Vec3b>(j, i)[2];
				green = image.at<cv::Vec3b>(j, i)[1];
				blue = image.at<cv::Vec3b>(j, i)[0];
				c = Color::FromArgb(red, green, blue);
				outputImage->SetPixel(i, j, c);
			}
		}
		return outputImage;
	}
};