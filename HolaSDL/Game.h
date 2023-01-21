#pragma once

#include "Texture.h"

//hacemos que pueda tener puntero de GameState
#include "GameState.h"

//se necesita para excepcion al crear ventana window y renderer
#include "SDLError.h"
//se necesita para crear maquina de estados 
#include "GameStateMachine.h"
//añadimos estados posibles
#include "MainMenuState.h"
#include "PlayGameState.h"
#include "EndMenuState.h"
#include "PauseMenuState.h"


const uint NUM_TEXTURES = 17;//numero de imagenes
//constantes
const uint WIN_WIDTH = 600;
const uint WIN_HEIGHT = 800;
//velocidad de juego
const uint FRAME_RATE = 10;

//enum 
//añadimos botones
enum TextureName {ballEnum,Bricks, Digits, GameOver,paddleEnum, SideWall, TopWall, Winner,Rewarding , Menus, PlayButton, ResumeButton , RestartButton, ExitButton , MainMenu , LoadGameButton,SaveGameButton};

typedef struct
{
	string fileName;
	uint hframes, wframes;//el hframes es el numero de filas tiene la imagen , esto es en el blockMap con imagen bricks , tiene 2 filas
	//el wframes posee 3 columnas ya que es el numero de columnas que tiene la imagen de los bloques = 3

}TextureDescription;


//en el caso de hframes y wframes de rewards , hacemos hasta la R por ahora , esto es hframes =5(numero de filas) , wframes = 8(numero de columnas)
//rutas de datos de archivos
const TextureDescription TEXT_DESCRIPTION[NUM_TEXTURES] =
{
	{"../Images/ball2.png",1,1},{"../Images/bricks2.png" ,2 ,3 },{"../Images/digits2.jpeg",3,4},{"../Images/gameover1.png" ,1 ,1 },{"../Images/paddle2.png",1,1}, { "../Images/side2.png",1 ,1 },{"../Images/topside.png" ,1 ,1 },{ "../Images/youwin.png",1 ,1 },{ "../Images/rewards.png",10 ,8 },{ "../Images/menu.jpg",1,1 }, { "../Images/play.png",1,3 },{ "../Images/resume.png",1,3}, { "../Images/restart.png",1,3 },{ "../Images/exit.png",1,3 },{ "../Images/main.png",1,3 } , { "../Images/load.png",1,3 },{"../Images/Save.png",1,3}//me corta la imagen en 10 filas y 8 columnas para rewards
};


using uint = unsigned int;

class GameState;//para evitar recurencia ciclica ya que se intenta llamar a esta clase GameState y esta a su vez llama a PlayGameState que llama a Game de nuevo
class Game {

	private:
		
		
		//puntero a clase maquina de estados GameState que utiliza a su vez GameStatemachine para cambiar de estado
		GameState* gameState = nullptr;
		GameStateMachine* gameStateMachine;



	public:
		//constructora
		Game();
		//destructora
		virtual ~Game();
		//iniciador para forzar un estado al principio Menu
		void init();
		//cargar texturas
		void LoadTextures(SDL_Renderer* renderer);
		//handleEvents, function will allow us to move between our states
		void handleEvents();
		//renderiza el estado actual
		void render();
		//actualiza el estado actual
		void update();
		//metodo para bucle principal
		void run();
		//devuelve estado de endGame
		bool EndGame();
		void SetEndGame(bool newBool);

		//boton Play Game
		void StartGameButton();

		//boton Exit
		void ExitGameButton();

		//para EndState
		void CambioEstadoPlayEndWin();
		void CambioEstadoPlayEndLose();

		//Pause State
		void ReanudarGameButton();
		void PauseMainMenuButton();


		void CambioEstadoPlayPause();

		void SaveFile();
		void LoadFile();

		//Devuelve una textura del vector
		Texture* getTexture(int n);

		//bool de fin de aplicacion
		bool endGame = false;


		//array de texturas publico para que PlayGameState pueda acceder
		Texture* textures[NUM_TEXTURES];

		//punteros a SDL_Window y sdlrenderer  para que PlayGameState pueda acceder
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		
};
