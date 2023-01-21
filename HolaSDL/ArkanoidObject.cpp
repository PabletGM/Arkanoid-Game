//clase general de la que hereda el resto
//se incluye a si misma
#include "ArkanoidObject.h"
#include <fstream>

//constructora
ArkanoidObject::ArkanoidObject(Vector2D posicion, int ancho, int alto, Texture* texture, SDL_Rect destR,Vector2D direccion)
{
	posicion = posicionArkanoid;
	ancho = width;
	alto = height;
	texture = text;
	//definimos destRect
	destRectArkanoid.x = posicion.getX();
	destRectArkanoid.y = posicion.getY();
	destRectArkanoid.w = width;
	destRectArkanoid.h = height;
	//objetos de arkanoid especificos
	destR = destRectArkanoid;
	direccion = direccionArkanoid;
}

//destRect
SDL_Rect ArkanoidObject::getRect()
{
	return destRectArkanoid;
}

//load virtual
void ArkanoidObject::loadFromFile(ifstream& lectura)
{
}

//save virtual
void ArkanoidObject::SaveToFile(ofstream& archivo)
{
}

//forma general de  render con destRect ya puesto
void ArkanoidObject::render()
{
	text->render(getRect());
}

//update virtual
void ArkanoidObject::update()
{
}

//handleEvents virtual
void ArkanoidObject::handleEvents(bool& exit, SDL_Event event)
{
}
