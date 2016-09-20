using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Image_Processing_Lab
{
    public partial class Form1 : Form
    {
        Bitmap image;
        public Form1()
        {
            InitializeComponent();
            Width = 872;
            Height = 608;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cancelButton.Enabled = false;
        }

        private void SetWindowSize()
        {
            if (image == null)
                return;
            if (image.Width <= 1920 - 42) // changing size of window depending on size of loaded image
            {
                Width = image.Width + 42;
                pictureBox1.Width = image.Width;
            }
            else
            {
                Width = 1920;
                pictureBox1.Width = 1920 - 42;
            }
            if (image.Height <= 1080 - 128)
            {
                Height = image.Height + 128;
                pictureBox1.Height = image.Height;
            }
            else
            {
                Height = 1080;
                pictureBox1.Height = 1080 - 128;
            }
            cancelButton.Location = new Point(Width - 118, Height - 74);
            progressBar1.Location = new Point(12, Height - 74);
            progressBar1.Size = new Size(new Point(Width - 136, 23));
            label1.Width = Width;
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image Files | *.png; *.jpg; *.bmp; | All Files (*.*) | *.* ";
            dialog.Title = "Open File...";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                image = new Bitmap(dialog.FileName);
                SetWindowSize();
                pictureBox1.Image = image;
                pictureBox1.Refresh();
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "JPEG Image | *.jpg | PNG Image | *.png | Bitmap Image | *.bmp";
            saveFileDialog1.Title = "Save As...";
            saveFileDialog1.ShowDialog();
            if (saveFileDialog1.FileName != "")
            {
                System.IO.FileStream fs = (System.IO.FileStream)saveFileDialog1.OpenFile();
                switch (saveFileDialog1.FilterIndex)
                {
                    case 1:
                        this.pictureBox1.Image.Save(fs, System.Drawing.Imaging.ImageFormat.Jpeg);
                        break;
                    case 2:
                        this.pictureBox1.Image.Save(fs, System.Drawing.Imaging.ImageFormat.Png);
                        break;
                    case 3:
                        this.pictureBox1.Image.Save(fs, System.Drawing.Imaging.ImageFormat.Bmp);
                        break;
                }
                fs.Close();
            };
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            image = ((ImageProcessing)e.Argument).ImageProcess(backgroundWorker1);
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            cancelButton.Enabled = true;
            progressBar1.Value = e.ProgressPercentage;
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            cancelButton.Enabled = false;
            pictureBox1.Image = image;
            pictureBox1.Refresh();
            progressBar1.Value = 0;
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            cancelButton.Enabled = false;
            backgroundWorker1.CancelAsync();
        }

        private void otsuMethodToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ImageProcessing otsuMethod = new OtsuMethod(image);
            backgroundWorker1.RunWorkerAsync(otsuMethod);
        }

    }
}
