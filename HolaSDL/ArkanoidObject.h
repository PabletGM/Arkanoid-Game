#pragma once

//Esta clase hereda de GameObject
#include "GameObject.h "


class ArkanoidObject: public GameObject
{
	public:
		//constructora
		ArkanoidObject() {};	
		ArkanoidObject(Vector2D posicion, int ancho, int alto, Texture* texture, SDL_Rect destRect,Vector2D direccion);
		//destructora virtual
		virtual ~ArkanoidObject() {};
		//metodos
		virtual SDL_Rect getRect();
		virtual void loadFromFile(ifstream & lectura);
		virtual void SaveToFile(ofstream& archivo);

		//metodos para sobreescribir
		virtual void update();
		virtual void render();
		virtual void handleEvents(bool& exit, SDL_Event event);
	private:
	//acceso de hijos solo con atributos
	protected:
		//atributos
		int width;
		int height;
		Texture* text;
		SDL_Rect destRectArkanoid;
		Vector2D posicionArkanoid;
		Vector2D direccionArkanoid;

		
		


};
