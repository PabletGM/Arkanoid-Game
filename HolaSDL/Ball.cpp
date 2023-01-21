//aparte de incluirse a el mismo y PlayGameState
#include "Ball.h"
#include "PlayGameState.h"
#include <iostream>
using namespace std;
	
//constructora de ball
Ball::Ball(Vector2D position, int h, int w, Vector2D initVel, Texture* text, PlayGameState* playGameStateref,double velocBall)
{
	//los argumentos de la funcion los igualamos a nuestro texture,height y width
	texture = text;
	height = h/4; width = w/4;
	playGameState = playGameStateref;
	//ponemos la posicion inicial de la bola o cambiamos su posicion a traves del argumento que demos
	pos = position;
	direccionArkanoid = initVel;
	//la posicion de la bola la cogeremos de la pos que tenga
	destRect.x = pos.getX(); 
	destRect.y = pos.getY(); 
	//su tamaño lo cogemos de los argumentos, como es muy grande por defecto
	destRect.w = width; 
	destRect.h = height;
	velocityBall = velocBall;

	//guardas los valores iniciales en otras variables que no se modifican
	direccionIni = direccionArkanoid;
	posicionIni = pos;
	//valores protected de movingObject
	posicionArkanoid = pos;
	destRectArkanoid = destRect;

}

//renderiza en posicion la textura
void Ball::render()
{
	//posicion de destino irá cambiando por eso actualizamos posicion en cada render
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	texture->render(destRect);
}

//actualiza posicion y cambia direccion si colisiona la bola
void Ball::update() 
{
	//creas un vector 2D que será la futura posicion del objeto con el que chocará la pelota
	Vector2D colVector;
	//en caso de cumplirse este choque , esto es si ball ha chocado con algo y collide
	if (playGameState->CollideBall(destRect, colVector)) {
		//formula del rebote para ver la direccion que debe coger la bola tras el rebote
		direccionArkanoid = direccionArkanoid - colVector * (2 * (direccionArkanoid* colVector));
	}
	//se le suma a la posicion esa nueva direccion 
	pos = pos + (direccionArkanoid*velocityBall);
}
//devuelve destRect
SDL_Rect Ball::getDestRect()
{
	return destRect;
}
//devuelve altura de bola
int Ball::checkPos() { return destRect.y; }

void Ball::resetState()
{
	 direccionArkanoid=direccionIni;
	 pos=posicionIni ;
}

void Ball::loadFromFile(ifstream& lectura)
{
	//le queremos dar posicion y direccion actual
	double posX, posY, dirX, dirY;
	//leemos posicion
	lectura >> posX;
	lectura >> posY;
	//leemos direccion
	lectura >> dirX;
	lectura >> dirY;
	//lo asociamos
	pos.setX(posX);
	pos.setY(posY);
	direccionArkanoid.setX(dirX);
	direccionArkanoid.setY(dirY);
}

//en ball no te interesa guardar la posicion inicial que conoce el arkanodObject sino la mas reciente
void Ball::SaveToFile(ofstream& archivo)
{
	archivo << pos.getX() << " " << pos.getY() << " " << direccionArkanoid.getX() << " " << direccionArkanoid.getY();
	archivo << endl;
}


