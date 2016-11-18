#pragma once

#include "KMeansMethod.h"
#include "FourierImage.h"
#include <complex>
#include <vector>
#include <cmath>

#define PI 3.1415926535

class Fourier
{
private:
	cv::Mat sourceImage;
	cv::Mat outputImage;
	int height;
	int width;
	vector<complex<double>> *intesnsityMatrix;
	int *magnitudes;
	int *phases;
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
		for (int i = 0, j = 0; i < n; i += 2, ++j) {
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
		int k = width * height;
		int deg = static_cast<int>(log(width * height) / log(2.0)) + 1;
		int leng = Math::Pow(2, deg);
		intesnsityMatrix = new vector<complex<double>>(leng);

		/* Задаем матрицу интенсивностей */
		СalculateIntensityMatrix(leng);	
	
		/* Применяем быстрое преобразование Фурье */
		fft(*intesnsityMatrix, false);

		/* Формируем изображение образа преобразования */
		Bitmap ^outputFourierImage = gcnew Bitmap(width, height);

		/* Рассчитываем матрицы магнитуд и фаз */
		magnitudes = new int[k];
		phases = new int[k];
		float indexCoeff = leng / (float)k;
		for (int i = 0; i < k; i++) 
		{
			magnitudes[i] = static_cast<int>((*intesnsityMatrix)[indexCoeff * i].real());
			phases[i] = static_cast<int>((*intesnsityMatrix)[i].imag());
		}

		/* Ищем максимум и минимум у матрицы магнитуд */
		int max = 0;
		int min = INT_MAX;
		for (int i = 0; i < k; i++) 
		{
			if (max < magnitudes[i])
				max = magnitudes[i];
			if (min > magnitudes[i])
				min = magnitudes[i];
		}

		/*int max = static_cast<int>(Math::Sqrt(Math::Pow((*intesnsityMatrix)[0].real(), 2) +
			Math::Pow((*intesnsityMatrix)[0].imag(), 2)));
		int min = max;
		int sqrtOfComplexNumber = 0;
		for (int i = 0; i < k; i++) 
		{
			sqrtOfComplexNumber = static_cast<int>(Math::Sqrt(Math::Pow((*intesnsityMatrix)[i].real(), 2) +
				Math::Pow((*intesnsityMatrix)[i].imag(), 2)));
			if (max < sqrtOfComplexNumber)
				max = sqrtOfComplexNumber;
			if (min > sqrtOfComplexNumber)
				min = sqrtOfComplexNumber;
		}*/

		/* Считаем градацию серого и записываем цвет пикселя для изображения образа */
		int grad;
		Color color;
		int halfWidth = width / 2;
		int halfHeight = height / 2;
		int m = 0;
		int l = 0;
		float coeff = 255 / (float)log(1 + max);
		for (int i = 1; i < width; i++)
		{
			for (int j = 1; j < height; j++)
			{
				//grad = static_cast<int>((Math::Sqrt(Math::Pow((*intesnsityMatrix)[j * width + i].real(), 2) +
				//	Math::Pow((*intesnsityMatrix)[j * width + i].imag(), 2)) - min) / (double)(max - min) * 255);
				grad = coeff * (float)log(abs(magnitudes[j * width + i]) + 1);
				color = Color::FromArgb(grad, grad, grad);
				if(i + halfWidth <= width)
					m = i + halfWidth - 1;
				else
					m = i - halfWidth;
				if(j + halfHeight <= height)
					l = j + halfHeight - 1;
				else
					l = j - halfHeight;
				outputFourierImage->SetPixel(m, l, color);
			}
		}

		return outputFourierImage;
	}

	void InverseFourierTransform()
	{
		fft(*intesnsityMatrix, true);
		for(int i = 0; i < width; i++)
			for(int j = 0; j < height; j++)
			{
				int value = (*intesnsityMatrix)[j * width + i].real();
				outputImage.at<cv::Vec3b>(cv::Point(i, j))[0] = value;
				outputImage.at<cv::Vec3b>(cv::Point(i, j))[1] = value;
				outputImage.at<cv::Vec3b>(cv::Point(i, j))[2] = value;
			}
	}

	void СalculateIntensityMatrix(int leng)
	{
		double intensity;

		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
			{
				intensity =
					0.2126 * sourceImage.at<cv::Vec3b>(y, x)[2] +
					0.7152 * sourceImage.at<cv::Vec3b>(y, x)[1] +
					0.0722 * sourceImage.at<cv::Vec3b>(y, x)[0];
				(*intesnsityMatrix)[y * width + x] = complex<double>(intensity, 0);
			}

		/* Обнуляем оставшиеся элементы матрицы интенсивностей */
			for (int i = width * height; i < leng; i++)
			(*intesnsityMatrix)[i] = complex<double>(0, 0);
	}

	Bitmap^ getImage()
	{
		Bitmap ^outputBitmap = gcnew Bitmap(width, height);
		int red;
		int green;
		int blue;
		Color c;
		for (int i = 1; i < width; i++)
		{
			for (int j = 1; j < height; j++)
			{
				red = outputImage.at<cv::Vec3b>(j, i)[2];
				green = outputImage.at<cv::Vec3b>(j, i)[1];
				blue = outputImage.at<cv::Vec3b>(j, i)[0];
				c = Color::FromArgb(red, green, blue);
				outputBitmap->SetPixel(i, j, c);
			}
		}
		return outputBitmap;
	}

	~Fourier() { }

	/*void DFT()
	{
		complex<double> I = sqrt(-1);
		complex<double> value;
		complex<double> coeff;
		for(int k = 0; k < width; k++)
		{
			for(int l = 0; l < height; l++)
			{
				for(int i = 0; i < width; i++)
				{
					for(int j = 0; j < height; j++)
					{
						coeff = (-2 * PI * (k * i / width + l * j / height) * I);
						value = intensityMatrixComplex[j * width + i] * coeff;
					}
				}
				dftMatrix[l * width + k] = value;
			}
		}
	} */
};