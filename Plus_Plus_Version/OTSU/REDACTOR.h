#pragma once

#include "ImageProcessing.h"
#include "OtsuMethod.h"
#include "KMeansMethod.h"
#include "Downsampling.h"

#include "KMeansForm1.h"
#include "DownsamplingForm.h"

namespace OTSU{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for REDACTOR
	/// </summary>
	public ref class REDACTOR : public System::Windows::Forms::Form
	{
	public:
		Bitmap ^image;
		String ^filename;
	private: System::Windows::Forms::ToolStripMenuItem^  resamplingToolStripMenuItem;
	public: 
	private: System::Windows::Forms::ToolStripMenuItem^  downsamplingToolStripMenuItem;
			 static KMeansForm ^kMeansDialogBox = gcnew KMeansForm(); 
			 static DownsamplingForm ^downsamplingDialogBox = gcnew DownsamplingForm();

	public:
		REDACTOR(void)
		{
			InitializeComponent();
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~REDACTOR()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^  PCTB_Central_image;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ôàéëToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  çàãðóçèòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ñîõðàíèòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ìåòîäûToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  áèíîðèçàöèÿToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ìåòîäÎòñóToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  segmentationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeansMethodToolStripMenuItem;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(REDACTOR::typeid));
			this->PCTB_Central_image = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->çàãðóçèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõðàíèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ìåòîäûToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->áèíîðèçàöèÿToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ìåòîäÎòñóToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->segmentationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansMethodToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->resamplingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->downsamplingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PCTB_Central_image))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PCTB_Central_image
			// 
			this->PCTB_Central_image->Location = System::Drawing::Point(12, 38);
			this->PCTB_Central_image->Name = L"PCTB_Central_image";
			this->PCTB_Central_image->Size = System::Drawing::Size(832, 519);
			this->PCTB_Central_image->TabIndex = 1;
			this->PCTB_Central_image->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->ôàéëToolStripMenuItem, 
				this->ìåòîäûToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(856, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ôàéëToolStripMenuItem
			// 
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->çàãðóçèòüToolStripMenuItem, 
				this->ñîõðàíèòüToolStripMenuItem});
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			this->ôàéëToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->ôàéëToolStripMenuItem->Text = L"File";
			// 
			// çàãðóçèòüToolStripMenuItem
			// 
			this->çàãðóçèòüToolStripMenuItem->Name = L"çàãðóçèòüToolStripMenuItem";
			this->çàãðóçèòüToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->çàãðóçèòüToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->çàãðóçèòüToolStripMenuItem->Text = L"Open File...";
			this->çàãðóçèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::çàãðóçèòüToolStripMenuItem_Click);
			// 
			// ñîõðàíèòüToolStripMenuItem
			// 
			this->ñîõðàíèòüToolStripMenuItem->Name = L"ñîõðàíèòüToolStripMenuItem";
			this->ñîõðàíèòüToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->ñîõðàíèòüToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->ñîõðàíèòüToolStripMenuItem->Text = L"Save As...";
			this->ñîõðàíèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::ñîõðàíèòüToolStripMenuItem_Click);
			// 
			// ìåòîäûToolStripMenuItem
			// 
			this->ìåòîäûToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->áèíîðèçàöèÿToolStripMenuItem, 
				this->segmentationToolStripMenuItem, this->resamplingToolStripMenuItem});
			this->ìåòîäûToolStripMenuItem->Name = L"ìåòîäûToolStripMenuItem";
			this->ìåòîäûToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->ìåòîäûToolStripMenuItem->Text = L"Methods";
			// 
			// áèíîðèçàöèÿToolStripMenuItem
			// 
			this->áèíîðèçàöèÿToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ìåòîäÎòñóToolStripMenuItem});
			this->áèíîðèçàöèÿToolStripMenuItem->Name = L"áèíîðèçàöèÿToolStripMenuItem";
			this->áèíîðèçàöèÿToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->áèíîðèçàöèÿToolStripMenuItem->Text = L"Binarization";
			// 
			// ìåòîäÎòñóToolStripMenuItem
			// 
			this->ìåòîäÎòñóToolStripMenuItem->Name = L"ìåòîäÎòñóToolStripMenuItem";
			this->ìåòîäÎòñóToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift) 
				| System::Windows::Forms::Keys::O));
			this->ìåòîäÎòñóToolStripMenuItem->Size = System::Drawing::Size(219, 22);
			this->ìåòîäÎòñóToolStripMenuItem->Text = L"Otsu Method";
			this->ìåòîäÎòñóToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::ìåòîäÎòñóToolStripMenuItem_Click);
			// 
			// segmentationToolStripMenuItem
			// 
			this->segmentationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->kMeansMethodToolStripMenuItem});
			this->segmentationToolStripMenuItem->Name = L"segmentationToolStripMenuItem";
			this->segmentationToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->segmentationToolStripMenuItem->Text = L"Segmentation";
			// 
			// kMeansMethodToolStripMenuItem
			// 
			this->kMeansMethodToolStripMenuItem->Name = L"kMeansMethodToolStripMenuItem";
			this->kMeansMethodToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift) 
				| System::Windows::Forms::Keys::K));
			this->kMeansMethodToolStripMenuItem->Size = System::Drawing::Size(238, 22);
			this->kMeansMethodToolStripMenuItem->Text = L"k-Means Method";
			this->kMeansMethodToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::kMeansMethodToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Location = System::Drawing::Point(0, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(872, 1);
			this->label1->TabIndex = 3;
			// 
			// resamplingToolStripMenuItem
			// 
			this->resamplingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->downsamplingToolStripMenuItem});
			this->resamplingToolStripMenuItem->Name = L"resamplingToolStripMenuItem";
			this->resamplingToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->resamplingToolStripMenuItem->Text = L"Resampling";
			// 
			// downsamplingToolStripMenuItem
			// 
			this->downsamplingToolStripMenuItem->Name = L"downsamplingToolStripMenuItem";
			this->downsamplingToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift) 
				| System::Windows::Forms::Keys::D));
			this->downsamplingToolStripMenuItem->Size = System::Drawing::Size(228, 22);
			this->downsamplingToolStripMenuItem->Text = L"Downsampling";
			this->downsamplingToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::downsamplingToolStripMenuItem_Click);
			// 
			// REDACTOR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(856, 569);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->PCTB_Central_image);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"REDACTOR";
			this->Text = L"Image Processing";
			this->Load += gcnew System::EventHandler(this, &REDACTOR::REDACTOR_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PCTB_Central_image))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void REDACTOR_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 image = gcnew Bitmap(1, 1);
				 PCTB_Central_image -> Image = gcnew Bitmap(image);
				 PCTB_Central_image -> Refresh();
			 }

	private: System::Void çàãðóçèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 OpenFileDialog^ dialog = gcnew OpenFileDialog();
				 dialog -> Filter = "Image Files | *.bmp; *.jpg; *.png; All Files | (*.*) | *.*";

				 if(dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 image = gcnew Bitmap(dialog->FileName);
					 filename = dialog->FileName;
					 SetWindowSize();
					 PCTB_Central_image->Image = gcnew Bitmap(image);
					 PCTB_Central_image->Refresh();
				 }
			 }

	private: System::Void ìåòîäÎòñóToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 ImageProcessing* otsuMethod = new OtsuMethod(image);
				 image = otsuMethod->ProcessImage();
				 PCTB_Central_image->Image = gcnew Bitmap(image);
				 delete otsuMethod;
			 }

	private: void SetWindowSize()
        {
            if (image == nullptr)
                return;
            if (image->Width <= 1920 - 42) // changing size of window depending on size of loaded image
            {
                Width = image->Width + 42;
				PCTB_Central_image->Width = image->Width;
            }
            else
            {
                Width = 1920;
				PCTB_Central_image->Width = 1920 - 42;
            }
            if (image->Height <= 1080 - 128)
            {
                Height = image->Height + 128;
				PCTB_Central_image->Height = image->Height;
            }
            else
            {
                Height = 1080;
				PCTB_Central_image->Height = 1080 - 128;
            }
            label1->Width = Width;
        }
private: System::Void ñîõðàíèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			SaveFileDialog ^saveFileDialog1 = gcnew SaveFileDialog();
            saveFileDialog1->Filter = "JPEG Image | *.jpg | PNG Image | *.png | Bitmap Image | *.bmp";
            saveFileDialog1->Title = "Save As...";
            saveFileDialog1->ShowDialog();
            if (saveFileDialog1->FileName != "")
            {
                System::IO::FileStream ^fs = (System::IO::FileStream ^)saveFileDialog1->OpenFile();
                switch (saveFileDialog1->FilterIndex)
                {
                    case 1:
						this->PCTB_Central_image->Image->Save(fs, Imaging::ImageFormat::Jpeg);
                        break;
                    case 2:
                        this->PCTB_Central_image->Image->Save(fs, Imaging::ImageFormat::Png);
                        break;
                    case 3:
                        this->PCTB_Central_image->Image->Save(fs, Imaging::ImageFormat::Bmp);
                        break;
                }
                fs->Close();
            };
		 }
private: System::Void kMeansMethodToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 kMeansDialogBox->ShowDialog();
			 int k = kMeansDialogBox->k;
			 if(k != -1) 
			 {
				 KMeansMethod* kMeansMethod = new KMeansMethod(filename, k);
				 PCTB_Central_image->Image = kMeansMethod->OutputImage();
				 delete kMeansMethod;
			 }
		 }
private: System::Void downsamplingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 downsamplingDialogBox->originWidth = image->Width;
			 downsamplingDialogBox->originHeight = image->Height;
			 downsamplingDialogBox->ShowDialog();
			 int width = downsamplingDialogBox->width;
			 int height = downsamplingDialogBox->height;
			 if(width > 0 && height > 0)
			 {
				 Downsampling* downsampling = new Downsampling(width, height, SystemToStl(filename));
				 PCTB_Central_image->Image = downsampling->getImage();
				 delete downsampling;
			 }
		 }
};
}
