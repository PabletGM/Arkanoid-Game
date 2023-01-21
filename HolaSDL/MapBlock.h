#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <fstream>
#include "Block.h"
#include "Vector2D.h"

//hereda de ArkanoidObject
#include "ArkanoidObject.h"

class PlayGameState;
class MapBlock: public ArkanoidObject
{
	public:
		//constructora , ahora en vez de Game es PlayGameState
		MapBlock(Vector2D position,Texture* pointer, int width, int height, string filename, PlayGameState* playGameState);
		//destructora
		virtual ~MapBlock();
		//devuelve numero de bloques totales
		int getNumBlocks();
		void countBlocks();
		//cargar mapa segun nivel
		void LoadMap();
		//metodos para sobreescribir que en clase padre son virtuales
		void render();
		bool collide(SDL_Rect rectBall, Vector2D& colision);
		void loadFromFile(ifstream& lectura);
		void SaveToFile(ofstream & archivo);
		//instancia game + textura
		PlayGameState* playGameState;
		Texture* text;
	private:
		
		//fila , columna, , ancho de bloque , alto de bloque , num de bloques
		int row, col, mapSize,mapHeight, cellSize, cellHeight, nBlocks;
		string name= "";
		//posicion estatica del array
		Vector2D pos;
		Block*** matrix = nullptr;
};