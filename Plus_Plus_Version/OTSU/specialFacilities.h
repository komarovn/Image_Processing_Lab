#pragma once

string SystemToStl(String ^s) // ������� ���� String ^ � ��� string
	{
		using namespace Runtime::InteropServices;
		const char* ptr = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		return string(ptr);
	};