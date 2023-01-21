#include "FileNotFoundError.h"

//escribes el mensaje y heredas el what de arkanoidError
FileNotFoundError::FileNotFoundError(const char* what_arg) : ArkanoidError(what_arg)
{
}