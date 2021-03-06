﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.ComponentModel;
using System.Threading;

namespace Image_Processing_Lab
{
    abstract class ImageProcessing
    {
        protected Bitmap sourceImage;

        public ImageProcessing(Bitmap image)
        {
            sourceImage = image;
        }

        public int Clamp(int value, int min, int max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;
            return value;
        }
        
        protected abstract Color CalculateNewPixelColor(int x, int y);

        public Bitmap ImageProcess(BackgroundWorker worker)
        {
            Bitmap resultImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            for (int i = 0; i < sourceImage.Width; i++)
            {
                if (!worker.CancellationPending)
                {
                    worker.ReportProgress((int)((float)i / resultImage.Width * 100));
                    for (int j = 0; j < sourceImage.Height; j++)
                        resultImage.SetPixel(i, j, CalculateNewPixelColor(i, j));
                };
            };
            if (worker.CancellationPending)
                return sourceImage;
            else
                return resultImage;
        }
    }
}
