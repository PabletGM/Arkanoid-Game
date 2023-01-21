//aparte de heredar de sí misma
#include "Wall.h"
#include <iostream>

using namespace std;
//constructora wall
Wall::Wall(Vector2D position,unsigned int h,unsigned int w,Texture* text,Vector2D myVector) 
{ //Constructora de los muros
	width = w; 
	height = h;
	pos = position;
	texture = text;
	destRect.x = pos.getX(); 
	destRect.y = pos.getY(); 
	destRect.w = width; 
	destRect.h = height;
	colVector = myVector;
	//atributos protected de arkanoid
	posicionArkanoid = pos;
	destRectArkanoid = destRect;
}

////destructora
//Wall::~Wall()
//{
//	//mismo que destructora de texture
//	/*texture->~Texture();*/
//}

//render
void Wall::render()
{
	getDestRect();
	texture->render(destRect);
}

//colision
bool Wall::Collides(SDL_Rect ballRect, Vector2D& colisionVector) 
{
	colisionVector = colVector;
	return SDL_HasIntersection(&ballRect, &destRect);
}
//getRect
SDL_Rect Wall::getDestRect()
{
	SDL_Rect  destRect;
	destRect.x = (int)pos.getX();
	destRect.y = (int)pos.getY();
	destRect.h = height;
	destRect.w = width;

	return destRect;
}
