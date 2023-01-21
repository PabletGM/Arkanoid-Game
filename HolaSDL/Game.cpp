
#include "Game.h"

using namespace std;
using uint = unsigned int;

//constructora, se cargan texturas y crean ventanas y renderizado
Game::Game() 
{
	//las texturas las cogemos directamente del game , sin copiar el array de texturas ya que es demasiada informaxion
	window = nullptr;
	renderer = nullptr;
	//Devuelve 0 en caso de éxito
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED, //Creación de la ventana
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //Creación del render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//cargamos texturas
		LoadTextures(renderer);
		//iniciamos maquina de estados
		init();
	}
	else
	{
		throw SDLError("Error de inicializacion");
	}
}


//destructora de todo
Game::~Game()
{
	//Se borran las texturas del juego
	for (Texture* t : textures) delete t;
	//Se borra la máquina
	delete gameStateMachine;
	//Se destruyen el renderer y la ventana
	SDL_DestroyRenderer(renderer);
	//se destruye ventana
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::init()
{
	//creamos objeto maquina de estados
	gameStateMachine = new GameStateMachine();
	//pedimos un cambio de estado a MenuState por defecto
	gameStateMachine->changeState(new MainMenuState(this));
}

//carga de texturas
void Game::LoadTextures(SDL_Renderer* renderer)
{
	try {
		
		textures[paddleEnum] = new Texture(renderer, TEXT_DESCRIPTION[paddleEnum].fileName, TEXT_DESCRIPTION[paddleEnum].hframes, TEXT_DESCRIPTION[paddleEnum].wframes);

		textures[Bricks] = new Texture(renderer, TEXT_DESCRIPTION[Bricks].fileName, TEXT_DESCRIPTION[Bricks].hframes, TEXT_DESCRIPTION[Bricks].wframes);

		textures[Digits] = new Texture(renderer, TEXT_DESCRIPTION[Digits].fileName, TEXT_DESCRIPTION[Digits].hframes, TEXT_DESCRIPTION[Digits].wframes);

		textures[SideWall] = new Texture(renderer, TEXT_DESCRIPTION[SideWall].fileName, TEXT_DESCRIPTION[SideWall].hframes, TEXT_DESCRIPTION[SideWall].wframes);

		textures[TopWall] = new Texture(renderer, TEXT_DESCRIPTION[TopWall].fileName, TEXT_DESCRIPTION[TopWall].hframes, TEXT_DESCRIPTION[TopWall].wframes);

		textures[ballEnum] = new Texture(renderer, TEXT_DESCRIPTION[ballEnum].fileName, TEXT_DESCRIPTION[ballEnum].hframes, TEXT_DESCRIPTION[ballEnum].wframes);

		textures[Winner] = new Texture(renderer, TEXT_DESCRIPTION[Winner].fileName, TEXT_DESCRIPTION[Winner].hframes, TEXT_DESCRIPTION[Winner].wframes);

		textures[GameOver] = new Texture(renderer, TEXT_DESCRIPTION[GameOver].fileName, TEXT_DESCRIPTION[GameOver].hframes, TEXT_DESCRIPTION[GameOver].wframes);

		textures[Rewarding] = new Texture(renderer, TEXT_DESCRIPTION[Rewarding].fileName, TEXT_DESCRIPTION[Rewarding].hframes, TEXT_DESCRIPTION[Rewarding].wframes);

		textures[Menus] = new Texture(renderer , TEXT_DESCRIPTION[Menus].fileName, TEXT_DESCRIPTION[Menus].hframes, TEXT_DESCRIPTION[Menus].wframes); 

		//añadimos texturas de los diferentes botones
		


		//boton para volver a RESTART
		textures[RestartButton] = new Texture(renderer, TEXT_DESCRIPTION[RestartButton].fileName, TEXT_DESCRIPTION[RestartButton].hframes, TEXT_DESCRIPTION[RestartButton].wframes);

		//boton para volver a MAIN MENU
		textures[MainMenu] = new Texture(renderer, TEXT_DESCRIPTION[MainMenu].fileName, TEXT_DESCRIPTION[MainMenu].hframes, TEXT_DESCRIPTION[MainMenu].wframes);

		//boton para volver a	EXIT
		textures[ExitButton] = new Texture(renderer, TEXT_DESCRIPTION[ExitButton].fileName, TEXT_DESCRIPTION[ExitButton].hframes, TEXT_DESCRIPTION[ExitButton].wframes);

		//boton para volver a	PLAY
		textures[PlayButton] = new Texture(renderer, TEXT_DESCRIPTION[PlayButton].fileName, TEXT_DESCRIPTION[PlayButton].hframes, TEXT_DESCRIPTION[PlayButton].wframes);

		//boton para volver a  RESUME
		textures[ResumeButton] = new Texture(renderer, TEXT_DESCRIPTION[ResumeButton].fileName, TEXT_DESCRIPTION[ResumeButton].hframes, TEXT_DESCRIPTION[ResumeButton].wframes);

		//boton para volver a  LOADGAME
		textures[LoadGameButton] = new Texture(renderer, TEXT_DESCRIPTION[LoadGameButton].fileName, TEXT_DESCRIPTION[LoadGameButton].hframes, TEXT_DESCRIPTION[LoadGameButton].wframes);

		//boton para SAVE GAME
		textures[SaveGameButton] = new Texture(renderer, TEXT_DESCRIPTION[SaveGameButton].fileName, TEXT_DESCRIPTION[SaveGameButton].hframes, TEXT_DESCRIPTION[SaveGameButton].wframes);

	}
	catch (exception e) { throw "Error loading textures"; }
}

//accedes al handleEvents del estado Actual
void Game::handleEvents()
{
	gameStateMachine->currentState()->handleEvents();
}

//render el estado actual y si hay secundario tambien
void Game::render()
{
	SDL_RenderClear(renderer);
	gameStateMachine->render();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	gameStateMachine->currentState()->update();
}

void Game::run()
{
	//ventana y renderer
	if (window == nullptr || renderer == nullptr) 
		throw SDLError("Error fatal SDL");

		uint32_t startTime, frameTime;
		//tiempo de la consola SDL en iniciarse
		startTime = SDL_GetTicks();

	    //hacemos handleEvents , update y render del estado activo
		while (!endGame)
		{
			handleEvents();
			//tiempo de frame , para controlar la velocidad
			frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= FRAME_RATE)
			{
				update();
				startTime = SDL_GetTicks();
			}
			render();
			//Se borran los estados que no se estén usando
			gameStateMachine->limpiarLista();
		}
}

//devuelve estado de booleano de fin de juego
bool Game::EndGame()
{
	return endGame;
}

//cambia booleano de fin de juego
void Game::SetEndGame(bool newBool)
{

	endGame = newBool;
}

//para forzar salida de aplicacion
void Game::ExitGameButton()
{
	SetEndGame(true);
}

//para cambiar a estado EndGameWin
void Game::CambioEstadoPlayEndWin()
{
	gameStateMachine->changeState(new EndMenuState(this,false));
}

//para cambiar a estado EndGameLose
void Game::CambioEstadoPlayEndLose()
{
	gameStateMachine->changeState(new EndMenuState(this,true));
}

//para reanudar partida
void Game::ReanudarGameButton()
{
	//hacemos pop del estado Pausa y solo queda el gameç
	gameStateMachine->popState();
}

//para ir a Main Menu
void Game::PauseMainMenuButton()
{
	//quitas el estado secundario
	gameStateMachine->popState();
	//pones el Main Menu primero
	gameStateMachine->changeState(new MainMenuState(this));
}


//cambio estado a PAUSE
void Game::CambioEstadoPlayPause()
{
	////no queremos cambiar el estado queremos añadir  uno por encima
	gameStateMachine->pushState(new PauseMenuState(this));
}

//guardas partida 
void Game::SaveFile()
{
	//para guardar el estado actual y poder acceder a el
	gameStateMachine->saveFile();
	cout << "Saving file";
}

//cargas partida
void Game::LoadFile()
{

	gameStateMachine->changeState(new PlayGameState(this,true));
	cout << "Loading file";
}

//coges textura
Texture* Game::getTexture(int n)
{
     return textures[n];;
}

//pasa a el estado de juego
void Game::StartGameButton()
{
		gameStateMachine->changeState(new PlayGameState(this));
}
