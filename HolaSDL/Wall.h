#pragma once
#include "Vector2D.h"
#include "Texture.h"


//hereda de ArkanoidObject
#include "ArkanoidObject.h"

class Wall: public ArkanoidObject
{
	private:
		SDL_Rect destRect;
		//referencias a script para acceder a sus variables
		Vector2D pos;
		//vector para ver su colision
		Vector2D colVector;
		unsigned int height = 0;
		unsigned int width=0;
		Texture* texture;

	public:
		//constructora normal que guarda valores del vector 2D pos  y el height y width son campos privados y el texture tambien
		Wall(Vector2D position, unsigned int h, unsigned int w, Texture* text, Vector2D Vector);
		//Destructora
		virtual ~Wall() {};
		//renderiza el wall llamando al Render de texture para que lo pinte en fila y columna
		void render();
		//collide
		bool Collides(SDL_Rect ballRect, Vector2D& colVector);
		SDL_Rect getDestRect();

		

};
