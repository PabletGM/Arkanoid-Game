#pragma once
//hereda de GameState
#include "GameState.h"

//incluimos boton y este a su vez contiene a  include Game
#include "MenuButton.h"

//clase que controla el menu principal

class Game;
class MainMenuState: public GameState
{
	private:
		static const string MainMenuID;
		//referencia a Game
		Game* game;
		//tres objetos boton para el Menu
		MenuButton* playGameButtonGO = nullptr;//play Game
		MenuButton* loadGameButtonGO = nullptr;//load Game
		MenuButton* exitGameButtonGO = nullptr;//Exit Game

	public:
		MainMenuState(Game* game);
	    ~MainMenuState();

		virtual bool onExit();
		virtual bool onEnter();
		//clase  nos dirá una comprobacion de entrada a el estado MainMenuState
		virtual string getStateID() const { return MainMenuID; }

		virtual void handleEvents();
		virtual void update();
		virtual void render();

		//funciones utilizadas para callBack
		 static void functionMenuPlayGame(Game* game);
		 static void functionMenuLoadGame(Game* game);
		 static void functionMenuExitGame(Game* game);

};
