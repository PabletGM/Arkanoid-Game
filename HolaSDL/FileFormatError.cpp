#include "FileFormatError.h"

//escribes el mensaje y heredas el what de arkanoidError
FileFormatError::FileFormatError(const char* what_arg) : ArkanoidError(what_arg)
{
}
FileFormatError::FileFormatError(const string& what_arg) : ArkanoidError(what_arg)
{
}