#pragma once
//hereda de ArkanoidError
#include "ArkanoidError.h"

class FileFormatError : public ArkanoidError
{
public:
	FileFormatError(const char* what_arg);
	FileFormatError(const string& what_arg);
};
