#include "REDACTOR.h"
#include "KMeansForm1.h"

using namespace System;
using namespace System::Windows::Forms;

using namespace OTSU;

[STAThread]

void main(/*array <String^>^args*/)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	OTSU::REDACTOR form;
	Application::Run(%form);
}