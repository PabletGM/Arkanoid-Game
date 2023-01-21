#include "Texture.h"
#include <iostream>

using namespace std;

void Texture::_freeTexture() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}



void Texture::load(string filename, uint nRows, uint nCols) {
	//carga en la superficie una imagen
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw "Error loading surface from " + filename;
	_freeTexture();
	//se crea textura a partir de la superficie
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw "Error loading texture from " + filename;
	//se pone en la fila y columna que se quiere imprimir
	numRows = nRows;
	numCols = nCols;
	//se le pone a la superficie de la imagen la anchura y altura por defecto en textur
	w = tempSurface->w;
	h = tempSurface->h;
	//para que se quede en un lugar haces la anchura total entre la posicion de las columnas en las que se encuentra
	fw = w / numCols;
	fh = h / numRows;
	//se libera la imagen y se renderiza
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	//para poner la imagen con el weight y height y el destRect
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	//asi se le pone inicialmente el tamaño que tendrá por defecto
	srcRect.w = w; 
	srcRect.h = h;
	
	//Copy a portion of the texture to the current rendering, with optional rotation and flipping
	//puede acceder al texture y al renderer privado de la clase Texture al estar el metodo predefinido
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

//coge el numero de filas y columnas que le has pasado del mapa de bloques o rewards y lo divide para ver cuanto ocupa de altura y anchura un bloque o lo que sea
//para el destRect
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	//Copy a portion of the texture to the current rendering, with optional rotationand flipping
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}