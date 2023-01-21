//se incluye a sí mismo
#include "MainMenuState.h"
//incluimos a Game en todos los estados
#include "Game.h"
//se declara la constante del ID
const string MainMenuState::MainMenuID = "MENU";

MainMenuState::MainMenuState(Game* gameref)
{
	game = gameref;
}
MainMenuState::~MainMenuState()
{
}
//cuando entremos a la clase o estado MainMenu queremos crear los 3 botones
bool MainMenuState::onEnter()
{

	playGameButtonGO = new MenuButton(Vector2D{(WIN_WIDTH/2-90),(WIN_HEIGHT*0.25)} , 200,75, game->getTexture(PlayButton), game, functionMenuPlayGame);
	//creamos boton LOAD GAME, solo diferente la altura, la textura y la funcion
	loadGameButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2-90),(WIN_HEIGHT * 0.5) }, 200,75, game-> getTexture(LoadGameButton), game, functionMenuLoadGame);
	//creamos boton EXIT GAME
	exitGameButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2-90),(WIN_HEIGHT * 0.75) }, 200,75, game->getTexture(ExitButton), game, functionMenuExitGame);
	
	listaObjetos.push_back(playGameButtonGO);
	listaObjetos.push_back(loadGameButtonGO);
	listaObjetos.push_back(exitGameButtonGO);

	std::cout << "entering MenuState\n";
	return true;
}
void MainMenuState::handleEvents()
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
void MainMenuState::update()
{
	for (GameObject* objeto : listaObjetos) objeto->update();
}
void MainMenuState::render()
{
	//renderizamos el estado Menu con Play
	//renderizamos el estado Menu con loadGame
	for (GameObject* objeto : listaObjetos) objeto->render();
	
}

//pasa a el estado de juego
void MainMenuState::functionMenuPlayGame(Game * game)
{
	game->StartGameButton();
	cout << "Enter Game";
}
void MainMenuState::functionMenuLoadGame(Game* game)
{
	game->LoadFile();
	cout << "Load Game";
}
void MainMenuState::functionMenuExitGame(Game* game)
{
	cout << "Exit Game";
	game->ExitGameButton();
	
}
bool MainMenuState::onExit()
{
	std::cout << "exiting MenuState\n";
	return true;
}

