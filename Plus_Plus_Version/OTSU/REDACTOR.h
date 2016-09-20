#pragma once

#include "ImageProcessing.h"
#include "OtsuMethod.h"

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
		Bitmap^ image;

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
	private: System::Windows::Forms::ToolStripMenuItem^  çàãğóçèòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ñîõğàíèòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ìåòîäûToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  áèíîğèçàöèÿToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ìåòîäÎòñóToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;


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
			this->çàãğóçèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõğàíèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ìåòîäûToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->áèíîğèçàöèÿToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ìåòîäÎòñóToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
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
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->çàãğóçèòüToolStripMenuItem, 
				this->ñîõğàíèòüToolStripMenuItem});
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			this->ôàéëToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->ôàéëToolStripMenuItem->Text = L"File";
			// 
			// çàãğóçèòüToolStripMenuItem
			// 
			this->çàãğóçèòüToolStripMenuItem->Name = L"çàãğóçèòüToolStripMenuItem";
			this->çàãğóçèòüToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->çàãğóçèòüToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->çàãğóçèòüToolStripMenuItem->Text = L"Open File...";
			this->çàãğóçèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::çàãğóçèòüToolStripMenuItem_Click);
			// 
			// ñîõğàíèòüToolStripMenuItem
			// 
			this->ñîõğàíèòüToolStripMenuItem->Name = L"ñîõğàíèòüToolStripMenuItem";
			this->ñîõğàíèòüToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->ñîõğàíèòüToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->ñîõğàíèòüToolStripMenuItem->Text = L"Save As...";
			this->ñîõğàíèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::ñîõğàíèòüToolStripMenuItem_Click);
			// 
			// ìåòîäûToolStripMenuItem
			// 
			this->ìåòîäûToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->áèíîğèçàöèÿToolStripMenuItem});
			this->ìåòîäûToolStripMenuItem->Name = L"ìåòîäûToolStripMenuItem";
			this->ìåòîäûToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->ìåòîäûToolStripMenuItem->Text = L"Methods";
			// 
			// áèíîğèçàöèÿToolStripMenuItem
			// 
			this->áèíîğèçàöèÿToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ìåòîäÎòñóToolStripMenuItem});
			this->áèíîğèçàöèÿToolStripMenuItem->Name = L"áèíîğèçàöèÿToolStripMenuItem";
			this->áèíîğèçàöèÿToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->áèíîğèçàöèÿToolStripMenuItem->Text = L"Segmentation";
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
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Location = System::Drawing::Point(0, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(872, 1);
			this->label1->TabIndex = 3;
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

	private: System::Void çàãğóçèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 OpenFileDialog^ dialog = gcnew OpenFileDialog();
				 dialog -> Filter = "Image Files | *.bmp; *.jpg; *.png; All Files | (*.*) | *.*";

				 if(dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 image = gcnew Bitmap(dialog->FileName);
					 SetWindowSize();
					 PCTB_Central_image->Image = gcnew Bitmap(image);
					 PCTB_Central_image->Refresh();
				 }
			 }

	private: System::Void ìåòîäÎòñóToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 ImageProcessing* Filter = new GrayScaleFilter();
				 image = Filter->ProcessImage(image);
				 PCTB_Central_image->Image = gcnew Bitmap(image);
				 delete Filter;
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
private: System::Void ñîõğàíèòüToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
};
}
