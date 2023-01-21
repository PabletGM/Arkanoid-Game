#include <iostream>
#include "PlayGameState.h"
#include "SDL.h"
#include "Time.h"



Time::Time(Texture* tex, Vector2D position, int w, int h, int tiempoTotal) 
{ //Constructora
	texture = tex;
	pos = position;
	width = w; height = h;
	UnitFila = UnitColumna = TenFila = TenColumna =  HundredRow =  HundredCol = 0; //Variables que controlan las texturas de los ditintos dígitos
	TIME_LIMIT = tiempoTotal; //Límite de tiempo
	//al crear la variable cuenta para que lleve el numero de segundos será el SDLGetTicks(Get the number of milliseconds since SDL library initialization) +1 segundo 
	count = (SDL_GetTicks() * 0.001) + 1;
	//creamos destRect
	//Se renderizan 3 dígitos por pantalla, pudiendo llegar a 999 segundos 
	

	
	
}

void Time::update()
{ //Cada segundo se llama al update
	//tiempo de segundos desde que consola se inició SDL
	deltaTime = SDL_GetTicks() * 0.001;
	if (deltaTime >= count) 
	{
		//En caso de llegar a una cantidad de tiempo, se pierde
		addTime();
	}
}

void Time::addTime() {
	++count;
	++currentTime;
	if (currentTime >= TIME_LIMIT) timeUp = true; //En caso de llegar a una cantidad de tiempo, se pierde
	AñadirUnit(); //Se añade 1 segundo
}



//tercera fifra que indica las unidades
void Time::AñadirUnit() {
	//se suma 1 columna para ir a la siguiente cifra
	++UnitColumna;
	//en el caso de que no queden mas columnas , se reinicia y siguiente fila de la textura
	if (UnitColumna > 3) 
	{ 
		UnitColumna = 0;
		++UnitFila;
	}
	// //En caso de que se llegue a 9, reiniciamos filas y columnas para poner el numero a 0 y empezar en el siguiente
	else if (UnitFila == 2 && UnitColumna == 2) 
	{
		UnitFila = 0; UnitColumna = 0;
		AñadirTen();
	}
}
//segunda cifra que indica las decenas
void Time::AñadirTen()
{
	//se suma 1 columna , una unidad
	++TenColumna;
	//en e caso de que lleguemos a 3 columnas , se suma fila para siguiente unidad
	if (TenColumna > 3) {
		TenColumna = 0;
		++TenFila;
	}
	//si se llega a 9 se añade primera cifra el centenar y mismo proceso
	else if (TenFila == 2 && TenColumna == 2)
	{
		TenFila = 0; TenColumna = 0;
		AñadirHundred();
	}
}

void Time::AñadirHundred() 
{
	//se suma 1 columna , una unidad
	++HundredCol;
	//en e caso de que lleguemos a 3 columnas , se suma fila para siguiente unidad
	if (HundredCol > 3) {
		HundredCol = 0;
		++HundredRow;
	}
	//si se llega a 9 se añade primera cifra el centenar y mismo proceso
	else if (HundredRow == 2 && HundredCol == 2) 
	{
		//reiniciamos todas las pos de las filas y coclumnas de las 3 cifras
		HundredRow = 0; HundredCol = 0;
		TenFila = 0; TenColumna = 0;
		UnitFila = 0; UnitColumna = 0;
	}
}
void Time::render() 
{ 
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = width;
	destRect.h = height;

	//asociamos a valores protected
	destRectArkanoid = destRect;

	//renderiza la primera cifra las centenas
	texture->renderFrame(destRect, HundredRow, HundredCol);
	//aumentamos posicion para siguiente cifra el width de la primera
	destRect.x += width;
	//renderiza la segunda cifra las decenas
	texture->renderFrame(destRect, TenFila, TenColumna);
	//aumentamos posicion para siguiente cifra el width de la segunda
	destRect.x += width;
	//renderiza la tercera cifra las unidades
	texture->renderFrame(destRect, UnitFila, UnitColumna);
}
Time::~Time() { 
}
//Se mira si se ha llegado al límite de tiempo
bool Time::getTimeUp() 
{ 
	return timeUp; 
} 
//Cada vez que se empiece un nuevo nivel o  pierda  , se reinicia el tiempo de nuevo
void Time::reiniciarTime() 
{ 
	currentTime = 0;
	UnitFila = 0; UnitColumna = 0;
	TenFila = 0; TenColumna = 0;
	HundredRow = 0; HundredCol = 0;
	timeUp = false;
	
}

int Time::CurrentTime()
{
	return currentTime;
}

//almacenamos el tiempo
void Time::SaveToFile(ofstream& archivo)
{
	archivo << currentTime;
	archivo << endl;
}

void Time::loadFromFile(ifstream& lectura)
{
	lectura >> currentTime;
}
