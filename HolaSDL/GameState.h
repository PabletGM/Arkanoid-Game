#pragma once

//para la lista de GameObjects estados
#include <list>;
#include "GameObject.h"

class Game;//recurrencia cíclica entre Game y GameState al tener un puntero al gameState desde game y viceversa , no son padre e hijo
class GameState 
{
	//posee 2 atributos
	protected:
		//escenario del estado de juego , lista con objetos del estado
		list<GameObject*> listaObjetos;
		//puntero al juego Game
		Game* game = nullptr;
	private:

	public:

		GameState();
		virtual ~GameState();

		//clase abstracta ya que la poseen todas las clases hijas
		virtual bool onEnter()=0;
		//clase abstracta que devolverá y nos dirá una comprobacion de entrada a los estados
		virtual string getStateID()const = 0;
		virtual bool onExit() =0;

		//hacemos los 3 metodos abstractos handleEvents, render y update y se llamaran desde game para llamar a su vez al estado que sea
		virtual void handleEvents() = 0;
		virtual void update() = 0;
		virtual void render() = 0;


	
};

