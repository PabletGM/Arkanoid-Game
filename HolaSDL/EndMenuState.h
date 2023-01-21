#pragma once
//hereda de GameState
#include "GameState.h"

//incluimos a Game en todos los estados
#include "Game.h"

//clase que controla el menu principal
class Game;
class EndMenuState : public GameState
{
	private:
		static const string EndMenuID;

		//2 objetos boton para el EndMenu
		MenuButton* MainMenuGameButtonGO = nullptr;//restart game
		MenuButton* exitGameButtonGO = nullptr;//Exit Game

		//referencia a Game
		Game* game;

		//bool estadoPartida
		bool estadoPartida = false;

	public: 
		EndMenuState(Game* game, bool lost);
		~EndMenuState();
		virtual bool onEnter();
		virtual bool onExit();
		virtual void handleEvents();
		virtual void update();
		virtual void render();
		//clase  nos dirá una comprobacion de entrada a el estado EndMenuState
		virtual string getStateID() const { return EndMenuID; }
		//funciones utilizadas para callBack
		 static void functionExitGame(Game* game);
		 static void functionEndMainMenu(Game* game);

};
