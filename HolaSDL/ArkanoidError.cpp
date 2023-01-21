#include "ArkanoidError.h"

ArkanoidError::ArkanoidError(const char* what_arg) :logic_error(what_arg) {} 

ArkanoidError::ArkanoidError(const string& what_arg) : logic_error(what_arg) {}

