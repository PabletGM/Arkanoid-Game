#pragma once 
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"

//hereda de ArkanoidObject
#include "ArkanoidObject.h"

class Block: public ArkanoidObject
{
	public:
		//Constructora
		Block(int color, Texture* pointer, int x, int y, int w, int h);
		//desructora
		virtual ~Block() {};
		//render
		void render();
		//para sacar la info
		int ColorPosicion();
		bool collides(SDL_Rect ballRect, int& caso,Vector2D& colision);
		SDL_Rect getDestRect();
	private:
		bool hasReward = false;
		SDL_Rect destRect;
		Texture* texture;
		int blockType;
		Vector2D pos;
		int x, y, width, height;
};
