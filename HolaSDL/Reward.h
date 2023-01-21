#pragma once 
//hereda de MovingObject
#include "MovingObject.h"


class PlayGameState;//como ball y game se llaman mutuamente no te permiten hacer llamadas ciclicas y da error 

class Reward : public MovingObject
{
	public:
		Reward() {};
		//constructora normal niveles
		Reward(int fil, int col, int rewardTypes, SDL_Rect blockRect,Texture* text, int w, int h, Vector2D direccion, double velocidadReward, PlayGameState* playGameState);
		//constructora load levels
		Reward( Texture* text, int w, int h, Vector2D direccion, double velocidadReward, PlayGameState* playGameState);
		virtual ~Reward() {};
		SDL_Rect getDestRect();
		//sobreescriben metodos en clase base
		void update();
		void render();
		
		void SaveToFile(ofstream& archivo);
		void loadFromFile(ifstream& lectura);
		PlayGameState* playGameState;

	private:
		Vector2D pos,dir;
		double velocidadBajada=0;
		Texture* texture;
		int width=0, height=0;
		SDL_Rect destRect;
		int rewardType;
		int fils=0, cols=0;

};
