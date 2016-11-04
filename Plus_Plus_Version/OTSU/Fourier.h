#pragma once

#include "KMeansMethod.h"

class Fourier
{
private:
	cv::Mat sourceImage;
	cv::Mat outputImage;
	int height;
	int width;
public:
	Fourier(string filename)
	{
		sourceImage = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
		height = sourceImage.rows;
		width = sourceImage.cols;
		sourceImage.copyTo(outputImage);
	}

	void FourierTransform()
	{
		
	}

	void InverseFourierTransform()
	{
		
	}

	Bitmap ^getImage()
	{
		Bitmap ^outputImage = gcnew Bitmap(width, height);
		int red;
		int green;
		int blue;
		Color c;
		for (int i = 1; i < width; i++)
		{
			for (int j = 1; j < height; j++)
			{
				red = sourceImage.at<cv::Vec3b>(j, i)[2];
				green = sourceImage.at<cv::Vec3b>(j, i)[1];
				blue = sourceImage.at<cv::Vec3b>(j, i)[0];
				c = Color::FromArgb(red, green, blue);
				outputImage->SetPixel(i, j, c);
			}
		}
		return outputImage;
	}
};