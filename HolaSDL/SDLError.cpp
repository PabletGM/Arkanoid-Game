#include "SDLError.h"

//escribes el mensaje y heredas el what de arkanoidError
SDLError::SDLError(const char* what_arg) : ArkanoidError(what_arg)
{
}
