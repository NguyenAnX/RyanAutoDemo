#include "StrHelper.h"
#include <msclr/marshal_cppstd.h>

std::string StrHelper::ToStdStr(System::String^ managedStr)
{
    return msclr::interop::marshal_as<std::string>(managedStr);
}

System::String^ StrHelper::ToSysStr(const std::string& nativeStr)
{
    return msclr::interop::marshal_as<System::String^>(nativeStr);
}

System::String^ StrHelper::ToSysStr(const char* cStr)
{
    return msclr::interop::marshal_as<System::String^>(cStr);
}
