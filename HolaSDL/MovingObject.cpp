//aparte de incluirse a sí mismo
#include "MovingObject.h"


MovingObject::MovingObject()
{
}

void MovingObject::resetState()
{
}

void MovingObject::loadFromFile(ifstream& lectura)
{
	ArkanoidObject::loadFromFile( lectura);
}

void MovingObject::SaveToFile(ofstream& archivo)
{
	ArkanoidObject::SaveToFile(archivo);
}


