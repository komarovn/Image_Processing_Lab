#pragma once

#include "ImageProcessing.h"

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
	private: System::Windows::Forms::ToolStripMenuItem^  ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  �����������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ���������ToolStripMenuItem;


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
			this->PCTB_Central_image = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PCTB_Central_image))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PCTB_Central_image
			// 
			this->PCTB_Central_image->Location = System::Drawing::Point(12, 21);
			this->PCTB_Central_image->Name = L"PCTB_Central_image";
			this->PCTB_Central_image->Size = System::Drawing::Size(444, 352);
			this->PCTB_Central_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->PCTB_Central_image->TabIndex = 1;
			this->PCTB_Central_image->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->����ToolStripMenuItem, 
				this->������ToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(624, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->���������ToolStripMenuItem, 
				this->���������ToolStripMenuItem});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// ���������ToolStripMenuItem
			// 
			this->���������ToolStripMenuItem->Name = L"���������ToolStripMenuItem";
			this->���������ToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->���������ToolStripMenuItem->Text = L"���������";
			this->���������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::���������ToolStripMenuItem_Click);
			// 
			// ���������ToolStripMenuItem
			// 
			this->���������ToolStripMenuItem->Name = L"���������ToolStripMenuItem";
			this->���������ToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->���������ToolStripMenuItem->Text = L"���������";
			// 
			// ������ToolStripMenuItem
			// 
			this->������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->�����������ToolStripMenuItem});
			this->������ToolStripMenuItem->Name = L"������ToolStripMenuItem";
			this->������ToolStripMenuItem->Size = System::Drawing::Size(63, 20);
			this->������ToolStripMenuItem->Text = L"������";
			// 
			// �����������ToolStripMenuItem
			// 
			this->�����������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->���������ToolStripMenuItem});
			this->�����������ToolStripMenuItem->Name = L"�����������ToolStripMenuItem";
			this->�����������ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->�����������ToolStripMenuItem->Text = L"�����������";
			// 
			// ���������ToolStripMenuItem
			// 
			this->���������ToolStripMenuItem->Name = L"���������ToolStripMenuItem";
			this->���������ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->���������ToolStripMenuItem->Text = L"����� ����";
			this->���������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &REDACTOR::���������ToolStripMenuItem_Click);
			// 
			// REDACTOR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 385);
			this->Controls->Add(this->PCTB_Central_image);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"REDACTOR";
			this->Text = L"REDACTOR";
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

	private: System::Void ���������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 OpenFileDialog^ dialog = gcnew OpenFileDialog();
				 dialog -> Filter = "Image Files | *.bmp; *.jpg; *.png; All Files | (*.*) | *.*";

				 if(dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 image = gcnew Bitmap(dialog->FileName);
				 }

				 PCTB_Central_image -> Image = gcnew Bitmap(image);
				 PCTB_Central_image -> Refresh();
			 }

	private: System::Void ���������ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 ImageProcessing* Filter = new GrayScaleFilter();
				 image = Filter->ProcessImage(image);
				 PCTB_Central_image->Image = gcnew Bitmap(image);
				 delete Filter;
			 }
};
}
