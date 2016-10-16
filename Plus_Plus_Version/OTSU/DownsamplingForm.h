#pragma once

namespace OTSU {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DownsamplingForm
	/// </summary>
	public ref class DownsamplingForm : public System::Windows::Forms::Form
	{
	public:
		int width;
		int height;
		int originWidth;
		int originHeight;
	private: System::Windows::Forms::CheckBox^  aspectRatioCheckBox;
	public: 
		float aspectCoeff;

		DownsamplingForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DownsamplingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	private: System::Windows::Forms::TextBox^  widthTextBox;
	private: System::Windows::Forms::TextBox^  heightTextBox;
	private: System::Windows::Forms::Button^  inputButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::Label^  origWidthLabel;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->widthTextBox = (gcnew System::Windows::Forms::TextBox());
			this->heightTextBox = (gcnew System::Windows::Forms::TextBox());
			this->inputButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->origWidthLabel = (gcnew System::Windows::Forms::Label());
			this->aspectRatioCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(38, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Width:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 70);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Height:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Original Size:";
			// 
			// widthTextBox
			// 
			this->widthTextBox->Location = System::Drawing::Point(59, 41);
			this->widthTextBox->Name = L"widthTextBox";
			this->widthTextBox->Size = System::Drawing::Size(95, 20);
			this->widthTextBox->TabIndex = 3;
			this->widthTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &DownsamplingForm::widthTextBox_KeyDown);
			this->widthTextBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &DownsamplingForm::widthTextBox_KeyUp);
			// 
			// heightTextBox
			// 
			this->heightTextBox->Location = System::Drawing::Point(59, 67);
			this->heightTextBox->Name = L"heightTextBox";
			this->heightTextBox->Size = System::Drawing::Size(95, 20);
			this->heightTextBox->TabIndex = 4;
			this->heightTextBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &DownsamplingForm::heightTextBox_KeyUp);
			// 
			// inputButton
			// 
			this->inputButton->Location = System::Drawing::Point(12, 127);
			this->inputButton->Name = L"inputButton";
			this->inputButton->Size = System::Drawing::Size(75, 23);
			this->inputButton->TabIndex = 5;
			this->inputButton->Text = L"Input";
			this->inputButton->UseVisualStyleBackColor = true;
			this->inputButton->Click += gcnew System::EventHandler(this, &DownsamplingForm::inputButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(93, 127);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 6;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &DownsamplingForm::cancelButton_Click);
			// 
			// origWidthLabel
			// 
			this->origWidthLabel->AutoSize = true;
			this->origWidthLabel->Location = System::Drawing::Point(83, 9);
			this->origWidthLabel->Name = L"origWidthLabel";
			this->origWidthLabel->Size = System::Drawing::Size(30, 13);
			this->origWidthLabel->TabIndex = 7;
			this->origWidthLabel->Text = L"0 x 0";
			// 
			// aspectRatioCheckBox
			// 
			this->aspectRatioCheckBox->AutoSize = true;
			this->aspectRatioCheckBox->Location = System::Drawing::Point(12, 93);
			this->aspectRatioCheckBox->Name = L"aspectRatioCheckBox";
			this->aspectRatioCheckBox->Size = System::Drawing::Size(134, 17);
			this->aspectRatioCheckBox->TabIndex = 8;
			this->aspectRatioCheckBox->Text = L"Constrain Aspect Ratio";
			this->aspectRatioCheckBox->UseVisualStyleBackColor = true;
			this->aspectRatioCheckBox->CheckedChanged += gcnew System::EventHandler(this, &DownsamplingForm::aspectRatioCheckBox_CheckedChanged);
			// 
			// DownsamplingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(180, 162);
			this->Controls->Add(this->aspectRatioCheckBox);
			this->Controls->Add(this->origWidthLabel);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->inputButton);
			this->Controls->Add(this->heightTextBox);
			this->Controls->Add(this->widthTextBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"DownsamplingForm";
			this->Text = L"Properties";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &DownsamplingForm::DownsamplingForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &DownsamplingForm::DownsamplingForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void inputButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(widthTextBox->Text != "" && heightTextBox->Text != "") 
				 {
					width = Convert::ToInt32(widthTextBox->Text);
					height = Convert::ToInt32(heightTextBox->Text);
					Close();
				 }
			 }
private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 width = -1;
			 height = -1;
			 Close();
		 }
private: System::Void DownsamplingForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 widthTextBox->Text = Convert::ToString(originWidth);
			 heightTextBox->Text = Convert::ToString(originHeight);
			 origWidthLabel->Text = Convert::ToString(originWidth) + " x " + Convert::ToString(originHeight);
			 aspectCoeff = originWidth / (float)originHeight;
		 }
private: System::Void aspectRatioCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(aspectRatioCheckBox->Checked)
			 {
				 if(widthTextBox->Text != "")
				 {
					 heightTextBox->Text = Convert::ToString((int)(Convert::ToInt32(widthTextBox->Text) / aspectCoeff));
				 }
				 else
					 if(heightTextBox->Text != "")
					 {
						 widthTextBox->Text = Convert::ToString((int)(Convert::ToInt32(heightTextBox->Text) * aspectCoeff));
					 }
			 }
		 }
private: System::Void widthTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		 }
private: System::Void widthTextBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(aspectRatioCheckBox->Checked)
			 {
				 if(widthTextBox->Text != "")
					 heightTextBox->Text = Convert::ToString((int)(Convert::ToInt32(widthTextBox->Text) / aspectCoeff));
			 }
		 }
private: System::Void heightTextBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(aspectRatioCheckBox->Checked)
			 {
				 if(heightTextBox->Text != "")
					 widthTextBox->Text = Convert::ToString((int)(Convert::ToInt32(heightTextBox->Text) * aspectCoeff));
			 }
		 }
private: System::Void DownsamplingForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 width = -1;
			 height = -1;
		 }
};
}
