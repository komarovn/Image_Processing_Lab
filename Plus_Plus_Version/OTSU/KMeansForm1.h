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
			this->SuspendLayout();
			// 
			// inputKTextBox
			// 
			this->inputKTextBox->Location = System::Drawing::Point(12, 30);
			this->inputKTextBox->Name = L"inputKTextBox";
			this->inputKTextBox->Size = System::Drawing::Size(124, 20);
			this->inputKTextBox->TabIndex = 0;
			this->inputKTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &KMeansForm::inputKTextBox_KeyDown);
			// 
			// inputKButton
			// 
			this->inputKButton->Location = System::Drawing::Point(142, 28);
			this->inputKButton->Name = L"inputKButton";
			this->inputKButton->Size = System::Drawing::Size(75, 23);
			this->inputKButton->TabIndex = 1;
			this->inputKButton->Text = L"Input";
			this->inputKButton->UseVisualStyleBackColor = true;
			this->inputKButton->Click += gcnew System::EventHandler(this, &KMeansForm::inputKButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(224, 28);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 2;
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
			// KMeansForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(311, 62);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->inputKButton);
			this->Controls->Add(this->inputKTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"KMeansForm";
			this->Text = L"Parameters";
			this->Load += gcnew System::EventHandler(this, &KMeansForm::KMeansForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void inputKButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(inputKTextBox->Text != "") 
					 k = Convert::ToInt32(inputKTextBox->Text);
				 Close();
			 }
	private: System::Void KMeansForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 k = 0;
				 inputKTextBox->Text = "";
			 }
	private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 Close();
			 }
private: System::Void inputKTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if(e->KeyCode == Keys::Enter) 
			 {
				 if(inputKTextBox->Text != "")
					 k = Convert::ToInt32(inputKTextBox->Text);
				 Close();
			 }
		 }
};
}
