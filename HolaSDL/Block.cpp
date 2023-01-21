//aparte de incluirse a sí mismo
#include "Block.h"



//constructora con tipo de bloque , textura , posicion y tamaño
Block::Block(int color, Texture* pointer, int x, int y, int w, int h)
{
	//donde quieres pintar el bloque
	width = w; height = h;
	//cuanto miden tus muros de grosor es importante para que empiecen los bloques a partir de ahí y no se pongan por encima, asi ponemos la posicion inicial
	destRect.x = x; destRect.y = y;
	//como tamaño de bloque asocias la anchura y altura
	destRect.w = width; destRect.h = height;
	texture = pointer;
	blockType = color;

	//atributos protected de Arkanoid
	destRectArkanoid = destRect;
	
}

//renderizas segun el tipo de bloque en una fila o columna
void Block::render() 
{
	int row = 0, col = 0;
	switch (blockType) 
	{ 
		case 1: row = 0; col = 0; break;
		case 2: row = 0; col = 1; break;
		case 3: row = 0; col = 2; break;
		case 4: row = 1; col = 0; break;
		case 5: row = 1; col = 1; break;
		case 6: row = 1; col = 2; break;
	}
	//renderizas las textura en la posicion fil,col
	texture->renderFrame(destRect, row, col); //REnderizado
}


//posible colision la bola en diferentes partes de la pala
bool Block::collides(SDL_Rect ballRect, int& caso,Vector2D& colVector) {
	
	SDL_Rect areaColision; // area de colision 	
	//booleano que dice si hay colision
	//creas area de colision
	bool interseccion = SDL_IntersectRect(&ballRect, &destRect, &areaColision);
    

	//si hay colision
	if (interseccion) 
	{ 		
		//arriba
		if (areaColision.y < destRect.y + (height / 2))
		{ 			
			// izquierda			
			if (areaColision.x <= destRect.x+ (width / 2))
			{ 			
				//sino, en una cara superior o inferior de el bloque , ya que tiene mas anchura que altura
				//parte de arriba , parte izquierda y ancha no lateral
				if (areaColision.w > areaColision.h) colVector = {0,-1};
				//si el area de colision tiene mas alto que ancho significa que ha  pegado en un lateral del bloque 
				//cara arriba parte izq y ancha lateral
				else colVector = { -1,0 };
			} 	
			// parte derecha
			else 
			{ 		
				//sino, en una cara superior o inferior de el bloque , ya que tiene mas anchura que altura
				//parte de arriba ,parte derecha , parte no lateral
				if (areaColision.w > areaColision.h) colVector = { 0,-1 };
				//si el area de colision tiene mas alto que ancho significa que ha  pegado en un lateral del bloque 
				//parte de arriba ,parte derecha , parte  lateral
				else colVector = { 1,0 };
			} 		
		} 
		//if areaColision.y >= destRect.y + (height/2)
		// abajo
		else 
		{
				// izquierda		
				if (areaColision.x <= destRect.x + (width / 2))
				{ 	
					//sino, en una cara superior o inferior de el bloque , ya que tiene mas anchura que altura
					//parte abajo , parte izq , parte no lateral
					if (areaColision.w > areaColision.h)colVector = { 0,1 };
					//si el area de colision tiene mas alto que ancho significa que ha  pegado en un lateral del bloque , en este caso lateral izq
					//parte abajo , parte izq , parte  lateral
					else colVector = { -1,0 };
				} 			
				//derecha	
				else 
				{ 		
					//sino, en una cara superior o inferior de el bloque , ya que tiene mas anchura que altura
					//parte abajo , parte der , parte no lateral
					if (areaColision.w > areaColision.h) colVector = { 0,1 };
					//parte abajo , parte der , parte  lateral
					//si el area de colision tiene mas alto que ancho significa que ha  pegado en un lateral del bloque 
					else colVector = { 1,0 };
				} 		
		} 	
	} 	
	//una vez se devuelve colision y se cambia el valor Vector2D , se crea reward
	return interseccion; 

	
}
//devuelves destRect
SDL_Rect Block::getDestRect()
{
	return destRect;
}

int Block::ColorPosicion()
{
	int color = blockType;
	return color;
}
