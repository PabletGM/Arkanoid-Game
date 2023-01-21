//se incluye a sí mismo
#include "EndMenuState.h"

//se declara la constante del ID
const string EndMenuState::EndMenuID = "END";

//constructora
EndMenuState::EndMenuState(Game* gameref, bool lost)
{
	//referencia de game
	game = gameref;
	//si lost es true se renderizará la textura lost , sino la textura Win
	estadoPartida = lost;
}

//destructora
EndMenuState::~EndMenuState()
{
	
}

//al entrar en el estado se crean los elementos de la interfaz
bool EndMenuState::onEnter()
{
	MainMenuGameButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2 - 90),(WIN_HEIGHT * 0.7) }, 200, 75, game->getTexture(MainMenu), game, functionEndMainMenu);
	exitGameButtonGO = new MenuButton(Vector2D{ (WIN_WIDTH / 2 - 90),(WIN_HEIGHT * 0.4) }, 200, 75, game->getTexture(ExitButton), game, functionExitGame);

	//lo metemos en la lista para que lo renderice
	listaObjetos.push_back(MainMenuGameButtonGO);
	listaObjetos.push_back(exitGameButtonGO);

	std::cout << "entering EndState\n";
	return true;
}

bool EndMenuState::onExit()
{
	return false;
}

//handleEvents de EndGame
void EndMenuState::handleEvents()
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

//update de escena EndGame
void EndMenuState::update()
{
	for (GameObject* objeto : listaObjetos) objeto->update();
}

//render de escena EndGame
void EndMenuState::render()
{
	//si estadoPartida = lost = true , se ha perdido
	if (estadoPartida)
	{
		Texture* lost = game->getTexture(GameOver);
		SDL_Rect destRect;
		destRect.x = 0; destRect.y = -250;
		destRect.w = WIN_WIDTH;
		destRect.h = WIN_HEIGHT;
		lost->render(destRect);
	}
	//si estadoPartida != lost = false  , se ha ganado
	else
	{
		//textura
		Texture* victory = game->getTexture(Winner);
		SDL_Rect destRect;
		destRect.x = 0; destRect.y = -250;
		destRect.w = WIN_WIDTH;
		destRect.h = WIN_HEIGHT;
		victory->render(destRect);
	}
	//renderizamos objetos del juego
	for (GameObject* objeto : listaObjetos)
	{
		objeto->render();
	}
}

//funcion callBack exitGame
void EndMenuState::functionExitGame(Game* game)
{
	game->SetEndGame(true);
	cout << "Exit Game";
}

//funcion callBack mainmenu
void EndMenuState::functionEndMainMenu(Game* game)
{
	game->PauseMainMenuButton();
}
