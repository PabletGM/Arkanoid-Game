//se incluye a sí mismo
#include "PauseMenuState.h"

//se declara la constante del ID
const string PauseMenuState::PauseGameID = "PAUSE";

PauseMenuState::PauseMenuState(Game* gameref)
{
	game = gameref;
}

PauseMenuState::~PauseMenuState()
{
}

bool PauseMenuState::onEnter()
{
	//Seguir con game
	resumeButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2 - 90),(WIN_HEIGHT * 0.25) }, 200, 75, game->getTexture(ResumeButton), game, functionPauseGame);
	//guardar partida
	SaveGameButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2 - 90),(WIN_HEIGHT * 0.5) }, 200, 75, game-> getTexture(SaveGameButton), game, functionPauseSaveFile);
	//vamos a MAIN Menu
	mainMenuButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2 - 90),(WIN_HEIGHT * 0.75) }, 200, 75, game-> getTexture(MainMenu), game, functionPauseMainMenu);

	listaObjetos.push_back(resumeButtonGO);
	listaObjetos.push_back(SaveGameButtonGO);
	listaObjetos.push_back(mainMenuButtonGO);
	std::cout << "entering PauseState\n";
	return true;
}
bool PauseMenuState::onExit()
{
	std::cout << "exiting PauseState\n";
	return true;
}

void PauseMenuState::handleEvents()
{
	bool exit = game->EndGame();
	//pedimos handleEvents de los botones o objetos de el estado
	SDL_Event event;
	//aseguramos que hay eventos pendientes
	while (SDL_PollEvent(&event))
	{
		//recoremos para todos los objetos del escenario del estado su handleEvents
		for (GameObject* objeto : listaObjetos)
		{
			objeto->handleEvents(exit, event);
		}
	}
}

void PauseMenuState::update()
{
	for (GameObject* objeto : listaObjetos) objeto->update();
}

void PauseMenuState::render()
{
	for (GameObject* objeto : listaObjetos) objeto->render();
}

void PauseMenuState::functionPauseGame(Game* game)
{
	game->ReanudarGameButton();
	cout << "Enter Game";
}

void PauseMenuState::functionPauseSaveFile(Game* game)
{
	game->SaveFile();
}

void PauseMenuState::functionPauseMainMenu(Game* game)
{
	cout << "Enter Main Menu";
	game->PauseMainMenuButton();
}
