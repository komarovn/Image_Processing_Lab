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
		gaussianBlur();
	}

	void gaussianBlur() 
	{
		cv::Mat dest = image;
		cv::GaussianBlur(image, dest, cv::Size(13, 13), 0, 0);
		image = dest;
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