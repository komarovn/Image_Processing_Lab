#include "REDACTOR.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

void main(array <String^>^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OTSU::REDACTOR form;
	Application::Run(%form);
}