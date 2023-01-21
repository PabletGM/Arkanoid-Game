#pragma once
//hereda de GameState
#include "GameState.h"
//incluimos a Game en todos los estados
#include "Game.h"

//clase que controla el menu principal
class Game;
class PauseMenuState : public GameState
{
	private:
		static const string PauseGameID;
		//referencia a Game
		Game* game;
		//tres objetos boton para el Pause
		MenuButton* resumeButtonGO = nullptr;//resume Game
		MenuButton* SaveGameButtonGO = nullptr;//Exit Game
		MenuButton* mainMenuButtonGO = nullptr;//Main Menu
	public:

		PauseMenuState(Game* game);
		~PauseMenuState();

		virtual bool onEnter();
		virtual bool onExit();
		//clase  nos dirá una comprobacion de entrada a el estado PauseMenuState
		virtual string getStateID() const{ return PauseGameID; }

		virtual void handleEvents();
		virtual void update();
		virtual void render();

		//funciones utilizadas para callBack
		static void functionPauseGame(Game* game);
		static void functionPauseSaveFile(Game* game);
		static void functionPauseMainMenu(Game* game);
};