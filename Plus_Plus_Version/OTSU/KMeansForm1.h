#pragma once

namespace OTSU {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for KMeansForm
	/// </summary>
	public ref class KMeansForm : public System::Windows::Forms::Form
	{
	public:
		int k;

		KMeansForm(void)
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
		~KMeansForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  inputKTextBox;
	protected: 
	private: System::Windows::Forms::Button^  inputKButton;
	private: System::Windows::Forms::Button^  cancelButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  autoValueCheckBox;

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
			this->inputKTextBox = (gcnew System::Windows::Forms::TextBox());
			this->inputKButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->autoValueCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// inputKTextBox
			// 
			this->inputKTextBox->Location = System::Drawing::Point(12, 30);
			this->inputKTextBox->Name = L"inputKTextBox";
			this->inputKTextBox->Size = System::Drawing::Size(124, 20);
			this->inputKTextBox->TabIndex = 1;
			this->inputKTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &KMeansForm::inputKTextBox_KeyDown);
			// 
			// inputKButton
			// 
			this->inputKButton->Location = System::Drawing::Point(142, 28);
			this->inputKButton->Name = L"inputKButton";
			this->inputKButton->Size = System::Drawing::Size(75, 23);
			this->inputKButton->TabIndex = 2;
			this->inputKButton->Text = L"Input";
			this->inputKButton->UseVisualStyleBackColor = true;
			this->inputKButton->Click += gcnew System::EventHandler(this, &KMeansForm::inputKButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(224, 28);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 3;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &KMeansForm::cancelButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Input k Value:";
			// 
			// autoValueCheckBox
			// 
			this->autoValueCheckBox->AutoSize = true;
			this->autoValueCheckBox->Location = System::Drawing::Point(12, 56);
			this->autoValueCheckBox->Name = L"autoValueCheckBox";
			this->autoValueCheckBox->Size = System::Drawing::Size(143, 17);
			this->autoValueCheckBox->TabIndex = 4;
			this->autoValueCheckBox->Text = L"Calculate k automatically";
			this->autoValueCheckBox->UseVisualStyleBackColor = true;
			this->autoValueCheckBox->CheckedChanged += gcnew System::EventHandler(this, &KMeansForm::autoValueCheckBox_CheckedChanged);
			// 
			// KMeansForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(311, 83);
			this->Controls->Add(this->autoValueCheckBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->inputKButton);
			this->Controls->Add(this->inputKTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"KMeansForm";
			this->Text = L"Parameters";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &KMeansForm::KMeansForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &KMeansForm::KMeansForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void inputKButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(autoValueCheckBox->Checked)
					 k = -2;
				 else
				 {
					 if(inputKTextBox->Text != "") 
						 k = Convert::ToInt32(inputKTextBox->Text);
				 }
				 Close();
			 }
	private: System::Void KMeansForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 k = 0;
				 inputKTextBox->Text = "";
			 }
	private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 k = -1;
				 Close();
			 }
private: System::Void inputKTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::Enter) 
			 {
				 if(autoValueCheckBox->Checked)
					 k = -2;
				 else
				 {
					 if(inputKTextBox->Text != "")
						 k = Convert::ToInt32(inputKTextBox->Text);
				 }
				 Close();
			 }
		 }
private: System::Void autoValueCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(autoValueCheckBox->Checked)
				 inputKTextBox->ReadOnly = true;
			 else
				 inputKTextBox->ReadOnly = false;
		 }
private: System::Void KMeansForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 k = -1;
		 }
};
}
