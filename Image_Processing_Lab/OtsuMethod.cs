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
        // возможно нужно сделать некий конструктор и поля типа Bitmap sourceImage и массива intensity (то, что может понадобиться в разных местах)

        protected override Color CalculateNewPixelColor(Bitmap sourceImage, int x, int y)
        {
            Color color = new Color();
            // TODO : write method
            return color;
        }

        private int[] CalculateIntensity(Bitmap sourceImage)
        {
            int[] intensityArray;
            int sizeOfArray = sourceImage.Height * sourceImage.Width;
            intensityArray = new int[sizeOfArray];
            for (int i = 0; i < sourceImage.Height; i++)
                for (int j = 0; j < sourceImage.Width; j++)
                    intensityArray[(i + 1) * sourceImage.Width + j] = (int)(0.2126 * sourceImage.GetPixel(i, j).R + 0.7152 * sourceImage.GetPixel(i, j).G + 0.0722 * sourceImage.GetPixel(i, j).B);
            return intensityArray;
        }
    }
}
