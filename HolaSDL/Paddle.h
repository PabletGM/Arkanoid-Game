#pragma once
#include "Texture.h"
#include "Vector2D.h"
//hereda de MovingObject
#include "MovingObject.h"

class PlayGameState;
class Paddle : public MovingObject
{
	protected:
		double velocidadPala;

	private:
		int widthNormal, widthAlargado, widthCorto;
		Vector2D pos;
		//vector para ver su colision
		Vector2D collisionVect;
		int height, width;
		Texture* texture;
		SDL_Rect destRect;
		PlayGameState* playGameState;
		void loadFromFile(ifstream& lectura);
		void SaveToFile(ofstream& archivo);

	public:
		//movimiento automatico
		Paddle(Texture* text, int w, int h, Vector2D direccion, Vector2D colVector, double velocidadPal, PlayGameState* playGameStateref);
		virtual ~Paddle() {};
		//para devolver posicion de destRect de paddel
		SDL_Rect getDestRect();
		//sobreescriben los metodos virutales de la clae base
		void render();
		void update();
		void AlargarPlataforma();
		void PlataformaWidthNormal();
		void AcortarPlataforma();
		//devuelve posX
		int checkPosX();
		//cambia posX
		void SetPosX(int x);
		bool CollideBall(SDL_Rect ballRect, Vector2D& colVect);
		bool CollideReward(SDL_Rect RewardRect);
		void handleEvents(bool& exit, SDL_Event& event);
		//sobreescribo el resetState de ball
		void resetState();

};