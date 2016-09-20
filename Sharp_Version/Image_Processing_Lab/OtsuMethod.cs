using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.ComponentModel;
using System.Threading;

namespace Image_Processing_Lab
{
    class OtsuMethod : ImageProcessing
    {
        private int[] intensityArray;
        private int[] histogram;

        public OtsuMethod(Bitmap image) : base(image)
        {
            CalculateIntensity();
        }

        protected override Color CalculateNewPixelColor(int x, int y)
        {
            int grayGrad = intensityArray[(y + 1) * sourceImage.Width + x];
            Color color = Color.FromArgb(grayGrad, grayGrad, grayGrad);
            // TODO : write method
            return color;
        }

        private void CalculateIntensity()
        {
            int sizeOfArray = sourceImage.Height * sourceImage.Width;
            intensityArray = new int[sizeOfArray];
            for (int i = 0; i < sourceImage.Height; i++)
                for (int j = 0; j < sourceImage.Width; j++)
                    intensityArray[i * sourceImage.Width + j] = (int)(0.2126 * sourceImage.GetPixel(j, i).R + 0.7152 * sourceImage.GetPixel(j, i).G + 0.0722 * sourceImage.GetPixel(j, i).B);
        }

        private void CalculateHistogram()
        {
            histogram = new int[256];
            for (int i = 0; i < 256; i++)
                histogram[i] = 0;
            for (int i = 0; i < sourceImage.Height; i++)
                for (int j = 0; j < sourceImage.Width; j++)
                {
                    int index = (int)(0.2126 * sourceImage.GetPixel(j, i).R + 0.7152 * sourceImage.GetPixel(j, i).G + 0.0722 * sourceImage.GetPixel(j, i).B);
                    histogram[index]++;
                }
        }

        public int MakeBinarized(int thereshold, int value)
        {
            if (thereshold > value)
                return 0;
            else
                return 255;
        }

    }
}
