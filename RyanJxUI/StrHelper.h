#pragma once
#include <string>
ref class StrHelper
{
public:
	static std::string ToStdStr(System::String^ managedStr);
	static System::String^ ToSysStr(const std::string& nativeStr);
	static System::String^ StrHelper::ToSysStr(const char* cStr);
};

