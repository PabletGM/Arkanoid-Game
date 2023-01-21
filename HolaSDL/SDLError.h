#pragma once
//hereda de ArkanoidError
#include "ArkanoidError.h"
using namespace std;

class SDLError : public ArkanoidError
{

public:
	SDLError(const char* what_arg);
	
};
