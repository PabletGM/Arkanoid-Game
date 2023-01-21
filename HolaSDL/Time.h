#pragma once
#include "Texture.h"
#include "Vector2D.h"

//hereda de MovingObject
#include "MovingObject.h"

class Time : public MovingObject
{
	public:
		Time(Texture* tex, Vector2D position, int w, int h, int	tiempoTotal);
		virtual ~Time();
		void render();
		void update();
		bool getTimeUp();
		void reiniciarTime();
		//devuelve el tiempo de partida
		int CurrentTime();
		void SaveToFile(ofstream& archivo);
		void loadFromFile(ifstream& lectura);
	
	private:
		void AñadirUnit();
		void AñadirTen();
		void AñadirHundred();

		void addTime();

		unsigned int TIME_LIMIT;
		Texture* texture;
		Vector2D pos;
		int width, height, UnitFila, UnitColumna, TenFila, TenColumna, HundredRow, HundredCol, currentTime = 0;
		bool timeUp = false;
		int count, deltaTime;
		SDL_Rect destRect;
	};

