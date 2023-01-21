#pragma once
#include "Texture.h"
#include "Vector2D.h"
//hereda de MovingObject
#include "MovingObject.h"
class PlayGameState;//como ball y game se llaman mutuamente no te permiten hacer llamadas ciclicas y da error 


class Ball : public MovingObject
{
	private:
		Vector2D pos;
		int height, width;
		double velocityBall;
		Texture* texture;
		SDL_Rect destRect;
		PlayGameState* playGameState;
	public:
		//clase constructora textura con width y height, direccion inicial , textura e instancia de juego
		Ball(Vector2D position, int h, int w, Vector2D initVel, Texture* text, PlayGameState* playGameState,double velocitBall);
		virtual ~Ball() {};
		//sobreescriben metodos en clase base
		void render();
		void update();
		SDL_Rect getDestRect();
		int checkPos();
		void resetState();
	    void loadFromFile(ifstream& lectura);
	    void SaveToFile(ofstream& archivo);
};
