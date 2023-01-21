//aparte de heredar de Game y de ella misma
#include "MapBlock.h"
#include "PlayGameState.h"
#include "checkML.h"

using namespace std;

//constructora
MapBlock::MapBlock(Vector2D position,Texture* pointer, int width, int height, string filename, PlayGameState* playGameStateref)
{
	pos = position;
	//para que el arkanoidObject conozca todo
	posicionArkanoid = pos;
	//inicializas numero de bloques
	nBlocks = 0;
	//anchura del mapa
	mapSize = width;
	mapHeight = height;
	//nombre de archivo
	name = filename;
	//cargas mapa
	//countBlocks();
	playGameState = playGameStateref;
	text = pointer;
}


//cargas mapa con sus bloques y luego si quieres hacer LoadMap por encima cambias su color de bloque y ya
void MapBlock::LoadMap() {
	//intenta esto , sino se puede saltar excepcion
	try {
		ifstream in(name);
		//leemos sus filas y columnas
		in >> row;
		in >> col;
		//anchura de celda o bloque 
		cellSize = mapSize / col;
		//altura de cada bloque o celda
		cellHeight = mapHeight / row;
		//iniciamos matriz 
		matrix = new Block * *[row];
		for (int e = 0; e < row; e++) matrix[e] = new Block * [col];

		for (int x = 0; x < row; x++) {
			for (int y = 0; y < col; y++) {
				int n = 0;
				//almacenas en n el numero leido de bloque o color
				in >> n;
				//sino está vacio
				if (n != 0) 
				{	
					//segun la pos que tengas en x e y cargas la instancia Block con ese color y textura
					matrix[x][y] = new Block(n,text, WALL_WIDTH + cellSize*y, WALL_WIDTH + cellHeight*x,cellSize,cellHeight);
					//aumentas numero de bloques creados
					++nBlocks;
					//comprobacion del win con 1 bloque 
					/*nBlocks = 2;*/
				}
				//si el bloque está vacio lo ponemos en nulo
				else matrix[x][y] = nullptr;
			}
		}
	}
	//no se puede cargar el nivel
	catch (exception) {
		throw string("Error loading level" + name);
	}
}

//renderizar los bloques
void MapBlock::render() 
{
	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			if (matrix[x][y] != nullptr) {
				matrix[x][y]->render();
			}
		}
	}	
}
// algun bloque exacto ha colisionado, creacion rewards
bool MapBlock::collide(SDL_Rect rectBall, Vector2D& colision)
{
	int caso = 0;
	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++)
		{
			//si hay colision entre el bloque y la bola creamos reward
			if (matrix[x][y] != nullptr && matrix[x][y]->collides(rectBall,caso,colision)) 
			{
				//guardamos el destRect del bloque antes de destruirlo
				SDL_Rect rect = matrix[x][y]->getDestRect();
				//borramos el bloque
				delete matrix[x][y];
				matrix[x][y] = nullptr;
				nBlocks--;
				//pasando como argumento la posicion del bloque para pasarlo al constructor de reward
				playGameState->CrearReward(rect);
				//devolvemos true
				return true;
			}
		}
	}
	return false;
}

//cargar archivo
void MapBlock::loadFromFile(ifstream& lectura)
{
	lectura >> row;
	lectura >> col;

	//inicializamos datos 


	//anchura de celda o bloque 
	cellSize = mapSize / col;
	//altura de cada bloque o celda
	cellHeight = mapHeight / row;
	//iniciamos matriz 
	matrix = new Block * *[row];
	for (int e = 0; e < row; e++) matrix[e] = new Block * [col];



	for (int x = 0; x < row; x++) 
	{
		for (int y = 0; y < col; y++)
		{
			//lees el color
			int colorBloque=0;
			lectura >> colorBloque;
			if (colorBloque != 0)
			{
				//segun la pos que tengas en x e y cargas la instancia Block con ese color y textura
				matrix[x][y] = new Block(colorBloque, text, WALL_WIDTH + cellSize * y, WALL_WIDTH + cellHeight * x, cellSize, cellHeight);
				//aumentas numero de bloques creados
				++nBlocks;
				//comprobacion del win con 1 bloque 
				/*nBlocks = 2;*/
			}
			//si el bloque está vacio lo ponemos en nulo
			else matrix[x][y] = nullptr;
			
		}
		//saltamos de linea
	}
}

//guardamos archivo
void MapBlock::SaveToFile(ofstream& archivo)
{
	//debemos guardar filas y columnas del mapa y el propio mapa
	archivo << row << " " << col;
	archivo << endl;
	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++)
		{
			//almacenamos el color, si es nullptr lo ponemos como 0
			if (matrix[x][y] == nullptr)
			{
				archivo << 0 <<" ";
			}
			else
			{
				int color = matrix[x][y]->ColorPosicion();
				archivo << color << " ";
			}
		}
		//saltamos de linea
		archivo << endl;
	}
}

//devuelve numBloques
int MapBlock::getNumBlocks() { return nBlocks; }

void MapBlock::countBlocks()
{
	ifstream in(name);
	//leemos sus filas y columnas
	in >> row;
	in >> col;
	//iniciamos matriz 
	matrix = new Block * *[row];
	for (int e = 0; e < row; e++) matrix[e] = new Block * [col];

	for (int x = 0; x < row; x++) {
		for (int y = 0; y < col; y++) {
			int n = 0;
			//almacenas en n el numero leido de bloque o color
			in >> n;
			//sino está vacio
			if (n != 0)
			{
				//aumentas numero de bloques creados
				/*++nBlocks;*/
				//comprobacion del win con 1 bloque 
				nBlocks = 2;
			}

		}
	}
}


//destructor
MapBlock::~MapBlock() 
{
	for (int e = 0; e < row; ++e) {
		for (int c = 0; c < col; ++c) {
			if (matrix[e][c] != nullptr) delete matrix[e][c];
		}
		delete[] matrix[e];
	}
	delete[] matrix;
}