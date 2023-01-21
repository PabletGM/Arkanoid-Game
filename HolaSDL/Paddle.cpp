//aparte de incluirse a sí mismo y game
#include <iostream>
#include "Paddle.h"
#include "PlayGameState.h"
#include "SDL.h"



using namespace std;
SDL_Renderer* renderer;


void Paddle::loadFromFile(ifstream& lectura)
{
	//le queremos dar posicion y direccion actual
	double posX, posY,dirX,dirY;
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

void Paddle::SaveToFile(ofstream& archivo)
{
	//creamos la pos y la guardamos de cada arkanoid
	archivo << posicionArkanoid.getX() << " " << posicionArkanoid.getY() <<" "<< direccionArkanoid.getX()<<" "<<direccionArkanoid.getY();
	//salto de linea
	archivo << endl;
}

//constructora
Paddle::Paddle(Texture* text, int w, int h,Vector2D direcciones, Vector2D colision,double velocityPala, PlayGameState* playGameStateref )
{
	collisionVect = colision;
	//asocias argumentos con variables
	texture = text;
	width = w / 6; height = h / 8;
	//guardamos estas variables en otras fijas para no poder hacer ekl efecto de un mismo reward 2 veces seguidas
	//width normal guardamos 
	widthNormal = width;
	//widthAlargado lo definimos ya
	widthAlargado = width * 1.5;
	//widthCorto
	widthCorto = width * 0.75;
	//le das valor a X e Y inicialmente
	pos.setX(500); pos.setY(WIN_HEIGHT-50);
	
	//direccion inicial de paddle y velocidad , en este caso lo igualaremos a la direccion y velocidad que sepa nuestro GameObject ya que podremos acceder a sus variables
	direccionArkanoid = direcciones;
	velocidadPala = velocityPala;

	//guardas los valores iniciales en otras variables que no se modifican
	direccionIni = direccionArkanoid;
	posicionIni = pos;

	playGameState = playGameStateref;

	//definimos destRect
	//asociamos posicion al destino de la imagen
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	//asociamos tamaño a destino de la imagen 
	destRect.w = width;
	destRect.h = height;

	//para atributos de movingObject
	posicionArkanoid= pos;
	destRectArkanoid = destRect;

}
//destRect
SDL_Rect Paddle::getDestRect()
{
	//asociamos posicion al destino de la imagen
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	//asociamos tamaño a destino de la imagen 
	destRect.w = width;
	destRect.h = height;

	return destRect;
}
//renderizado de paddle
void Paddle::render() 
{
	texture->render(getDestRect());
}

//paddle update de posicion y limites
void Paddle::update()
{
	
	int posicionX = pos.getX() + direccionArkanoid.getX();
	//en caso de que no supere limites se puede mover
	if (posicionX >= WALL_WIDTH && posicionX+width < WIN_WIDTH - WALL_WIDTH)
	{
		pos = pos + direccionArkanoid;
		//asociamos X a la pos
		destRect.x = pos.getX();
	}

}

//ponemos a más tamaño
void Paddle::AlargarPlataforma()
{
	width = widthAlargado;

	//comprobamos si la pos + width alargado es > que limites derecho
	if ((pos.getX() + widthAlargado) > (WIN_WIDTH - WALL_WIDTH))
	{
		//el paddle se reposiciona
		//buscamos tamaño del espacio entre la esquina del paddle derecha y el limite del mapa
		Vector2D tamañoQuitar = { (pos.getX() + widthAlargado) - (WIN_WIDTH - WALL_WIDTH), 0 };
		pos = pos - tamañoQuitar;
	}
	//comprobamos si la pos + width alargado es < que limites izquierdo
	else if ((pos.getX() + widthAlargado) < (WALL_WIDTH))
	{
		Vector2D tamañoQuitar = { (pos.getX() + widthAlargado) - ( WALL_WIDTH), 0 };
		pos = pos + tamañoQuitar;
	}
	
}

void Paddle::PlataformaWidthNormal()
{
	width = widthNormal;
}

void Paddle::AcortarPlataforma()
{
	width = widthCorto;
}



//devuelve pos de x de la pala
int Paddle::checkPosX()
{
	return pos.getX();
}

void Paddle::SetPosX(int x)
{
	pos.setX(x);
}

bool Paddle::CollideBall(SDL_Rect ballRect, Vector2D& colVect)
{
	if (SDL_HasIntersection(&ballRect, &destRect))
	{
		//punto medio del ball
		double ballpoint = ballRect.x + (ballRect.w / 2);
		double proportion = (ballpoint - (pos.getX() + width / 2)) / (width / 2);//calculo del angulo de reflexión
		collisionVect = { proportion , -2.5 };
		collisionVect.normalize();
		colVect = collisionVect;
		return true;
	}

	return false;

}

bool Paddle::CollideReward(SDL_Rect RewardRect)
{
	//guardamos dstRect de paddle
	SDL_Rect RectPaddle  = destRect;
	//comprobamos si hay colision en RewardRect y rectPaddle
	if (SDL_HasIntersection(&RewardRect, &RectPaddle))
	{
		//si chocan Paddle y Reward , debemos destruir reward y quitarlo de la lista
		return true;
	}

	return false;
}

////se hace la llamada desde el handleEvent del game , aquí se verá si se ha pulsado hacia la izq o der
void Paddle::handleEvents(bool& exit, SDL_Event& event)
{

		if (event.type == SDL_QUIT) exit = true;
		/*User requests quit , mientras se pulsa una tecla*/
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym) {
			
				case SDLK_LEFT:
				case SDLK_a:

					/*actualizamos la direccion del paddle a la izquierda*/
					//para no dejar pulsado
					/*pos.setX(pos.getX() - velocidadPala);*/
					direccionArkanoid = { -1*velocidadPala,0 };
					break;
					/*si se pulsa d  se mueve posicion de paddle der*/
				case SDLK_RIGHT:
				case SDLK_d:
					//para no dejar pulsado
					/*pos.setX(pos.getX() + velocidadPala);*/
					direccionArkanoid = { 1*velocidadPala,0 };
					break;
			
			}
		}
		//si se deja de pulsa la tecla a o d se para
		 else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a)) 
			direccionArkanoid = { 0,0 }; //Si se suelta la tecla, no se mueve
	
}

//direccion , posicion y anchura
void Paddle::resetState()
{
	direccionArkanoid = direccionIni;
	pos = posicionIni;
	PlataformaWidthNormal();
}

