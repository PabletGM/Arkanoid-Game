#pragma once
//hereda de logic_error
#include <stdexcept>
using namespace std;

class ArkanoidError: public logic_error
{
public:
	ArkanoidError(const char* what_arg);
	ArkanoidError(const string& what_arg);
	//mensaje de error
};
