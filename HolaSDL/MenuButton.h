#pragma once


//hereda de GameObject
#include "GameObject.h"


//clase general Boton
class Game;
class MenuButton : public GameObject
{
	private:
		//creamos variable con funcion callBack y con referencia a game
		void (*functionCallback)(Game* gameReference);
		//destino del boton
		SDL_Rect destRect;
		//textura  del boton
		Texture* texture;
		//referencia a Game
		Game* game;

	public:
		//necesitamos para el boton , una anchura , altura , posicion y textura especifica
		//pasamos referencia a game y variable funcion callback
		MenuButton();
	    virtual ~MenuButton() {};
		MenuButton(Vector2D position, int w, int h, Texture* text,Game * gameref, void (*functionCallback)(Game* gameref));
		
		//metodos update,render y handleEvents heredados de GameObject
		virtual void render();
		virtual void update();
		//no es abstracto ya que no lo poseen todas las clases
		virtual void handleEvents(bool& exit,SDL_Event event);
		

};
