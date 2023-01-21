#pragma once
//hereda de ArkanoidError
#include "ArkanoidError.h"
using namespace std;

class FileNotFoundError : public ArkanoidError
{
public:
	FileNotFoundError(const char* what_arg);
	
};
