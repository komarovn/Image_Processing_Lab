#pragma once

#include "KMeansMethod.h"
#include "FourierImage.h"
#include <complex>
#include <vector>

class Fourier
{
private:
	cv::Mat sourceImage;
	cv::Mat outputImage;
	int height;
	int width;
	vector<complex<double>> *intesnsityMatrix;
	const double PI = 3.14159265;

public:
	Fourier(string filename)
	{
		sourceImage = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
		height = sourceImage.rows;
		width = sourceImage.cols;
		sourceImage.copyTo(outputImage);
	}

	void fft(vector<complex<double>> &a, bool invert) {
		int n = (int)a.size();
		if (n == 1)  return;

		vector<complex<double>> a0(n / 2), a1(n / 2);
		for (int i = 0, j = 0; i<n; i += 2, ++j) {
			a0[j] = a[i];
			a1[j] = a[i + 1];
		}
		fft(a0, invert);
		fft(a1, invert);

		double ang = 2 * PI / n * (invert ? -1 : 1);
		complex<double> w(1), wn(cos(ang), sin(ang));
		for (int i = 0; i<n / 2; ++i) {
			a[i] = a0[i] + w * a1[i];
			a[i + n / 2] = a0[i] - w * a1[i];
			if (invert)
				a[i] /= 2, a[i + n / 2] /= 2;
			w *= wn;
		}
	}

	Bitmap^ FourierTransform()
	{
		double intensity;
		int deg = static_cast<int>(log(width * height) / log(2.0)) + 1;
		int leng = pow(2, deg);
		intesnsityMatrix = new vector<complex<double>>(leng);

		for (int i = 0; i < leng; i++) (*intesnsityMatrix)[i] = 0;

		int k = 0;
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
			{
				intensity =
					0.2126 * sourceImage.at<cv::Vec3b>(y, x)[2] +
					0.7152 * sourceImage.at<cv::Vec3b>(y, x)[1] +
					0.0722 * sourceImage.at<cv::Vec3b>(y, x)[0];
				(*intesnsityMatrix)[k] = intensity;
				k++;
			}

		fft(*intesnsityMatrix, false);

		Bitmap ^FI = gcnew Bitmap(width, height);
		int col;
		Color c;

		int max = static_cast<int>((*intesnsityMatrix)[0].real());
		for (int i = 0; i < k; i++)
			if (max < (*intesnsityMatrix)[i].real()) max = (*intesnsityMatrix)[i].real();

		k = 0;
		for (int i = 1; i < width; i++)
		{
			for (int j = 1; j < height; j++)
			{
				col = static_cast<int>((*intesnsityMatrix)[k].real());
				if (col > 255) c = Color::FromArgb(255, 255, 255);
				else if (col < 0) c = Color::FromArgb(0, 0, 0);
				else c = Color::FromArgb(col, col, col);
				FI->SetPixel(i, j, c);
				k++;
			}
		}

		return FI;
	}

	void InverseFourierTransform()
	{
		//fft(*intesnsityMatrix, true);
	}

	Bitmap^ getImage()
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

	~Fourier()
	{
	}
};