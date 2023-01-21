//se incluye a si mismo
#include "MenuButton.h"
#include "Game.h"
//como ultimo parametro pasamos la variable callBack con una referencia de un metodo de Game para poder utilizarlo
MenuButton::MenuButton(Vector2D position, int w, int h, Texture* text, Game * gameref, void (*callbacks)(Game* gameref)) : functionCallback(callbacks)
{
	//ponemos la posicion del argumento como destino y tamaño
	destRect.x = position.getX();
	destRect.y = position.getY();
	destRect.w = w;
	destRect.h = h;
	//asocias textura
	texture = text;
	//referencia a Game
	game = gameref;
}

//llamamos al render de la textura
void MenuButton::render()
{
	texture->renderFrame(destRect,0,0);	
}

//posicion fija , no hace falta
void MenuButton::update()
{
}


void MenuButton::handleEvents(bool& exit, SDL_Event event)
{
	SDL_Point mousePoint; 

		if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP) { //Input del ratón en el menú
			
				//ponemos posicion del cursor la del boton
				mousePoint.x = event.button.x; mousePoint.y = event.button.y;
				//si coinciden,Use this function to check if a point resides inside a rectangle.
				//vemos si el punto o cursor mPoint esta dentro de el rectangulo destino destRect , si es así ejecutamos el callback de game
				if (SDL_PointInRect(&mousePoint, &destRect))
				{
						functionCallback(game);
				}
			
		}
}

