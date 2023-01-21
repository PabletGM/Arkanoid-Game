//aparte de incluirse a sí mismo
#include "Reward.h"
#include "PlayGameState.h"
//constructora normal
Reward::Reward(int fil,int col,int rewardTypes,SDL_Rect blockRect,Texture* text, int w, int h, Vector2D direccion, double velocidadPal, PlayGameState* playGameStateref)
{
	texture = text;
	width = w;
	height = h;
	dir = direccion;
	velocidadBajada=velocidadPal;
	playGameState = playGameStateref;
	//aqui ya tenemos en cuenta que la posicion del reward es la del bloque
	destRect = blockRect;
	//la posicion inicial del reward
	pos.setX(destRect.x);
	pos.setY(destRect.y);
	//asociamos tamaño a destino de la imagen 
	destRect.w = width;
	destRect.h = height;
	//asociamos posicion al destino de la imagen
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	//el tipo de premio es el que pasa como parametro
	rewardType = rewardTypes;
	fils = fil;
	cols = col;
	//valores protected de movingObject
	direccionArkanoid= dir;
	posicionArkanoid = pos;
	destRectArkanoid = destRect;


}

//constructora loadLevel
Reward::Reward(Texture* text, int w, int h, Vector2D direccion, double velocidadPal, PlayGameState* playGameStateref)
{
	texture = text;
	width = w;
	height = h;
	dir = direccion;
	velocidadBajada = velocidadPal;
	playGameState = playGameStateref;
	//la posicion inicial del reward
	pos.setX(destRect.x);
	pos.setY(destRect.y);
	//asociamos tamaño a destino de la imagen 
	destRect.w = width;
	destRect.h = height;
	//valores protected de movingObject
	direccionArkanoid = dir;
	posicionArkanoid = pos;
	destRectArkanoid = destRect;
}


//actualiza posicion para que vaya siempre para abajo
void Reward::update()
{
	if (playGameState->CollideReward(destRect,rewardType)|| destRect.y > playGameState->alturaPantalla() + 50)
	{
		//destruyes reward , haces llamada a su efecto
		playGameState->DestruirReward(this);
	}
	//sino hay choque update normal
	else
	{
		//Actualizamos posicion con la direccion constante (0,-1)
		pos = pos + dir;
		destRect.y = pos.getY();
	}
	
	
}

//render con animacion
void Reward::render()
{
	int y =  int((SDL_GetTicks() / 100) % 8);
	switch (rewardType)
	{
		//pasar de nivel L, esta en fila 0
		case 0:texture->renderFrame(destRect, 0, y); break;

		//E,//alargar plataforma E, se reestablece en siguiente nivel
		case 1:texture->renderFrame(destRect, 1, y); break;

		//C
		case 2:texture->renderFrame(destRect, 2, y); break;

		//acortar plataforma S, se reestablece en siguiente nivel
		case 3:texture->renderFrame(destRect, 3, y); break;

		//vida extra R ,  esta en fila 4
		case 4:texture->renderFrame(destRect, 4, y); break;

		//M
		case 5:texture->renderFrame(destRect, 5, y); break;

		//D
		case 6:texture->renderFrame(destRect, 6, y); break;

		//B
		case 7:texture->renderFrame(destRect, 7, y); break;

		//T
		case 8:texture->renderFrame(destRect, 8, y); break;

		//P
		case 9:texture->renderFrame(destRect, 9, y); break;

		default:
			break;
	}
		
}

void Reward::SaveToFile(ofstream& archivo)
{
	archivo << posicionArkanoid.getX() <<" "<< posicionArkanoid.getY() << " " << direccionArkanoid.getX() << " " << direccionArkanoid.getY()<<" "<< rewardType;
	archivo << endl;
}

void Reward::loadFromFile(ifstream& lectura)
{
	double posX,posY, direccionX,dirY, rewardtipo;
	//lectura de archivos
	lectura >> posX;
	lectura >> posY;
	lectura >> direccionX;
	lectura >> dirY;
	lectura >> rewardtipo;
	//establecer valores
	posicionArkanoid.setX(posX);
	posicionArkanoid.setY(posY);
	direccionArkanoid.setX(direccionX);
	direccionArkanoid.setY(dirY);
	rewardType = rewardtipo;
	destRect.x = posX;
	destRect.y = posY;
	pos.setX(destRect.x);
	pos.setY(destRect.y);
	
}

//destRect
SDL_Rect Reward::getDestRect()
{
	return destRect;
}
