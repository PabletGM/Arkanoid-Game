#pragma once

#include "Game.h"
//arkanoidObjects y premios del juego
#include "Reward.h"
#include "Texture.h"
#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"
#include "MapBlock.h"
#include "checkML.h"
#include <list>
#include "Reward.h"
#include "ArkanoidObject.h"
#include "Time.h"

//excpciones
#include "FileFormatError.h"
#include "SDLError.h"
#include "FileNotFoundError.h"




const uint WALL_WIDTH = 15;
const uint WALL_HEIGHT = 15;
const uint PADDLE_WIDTH = 500;
//width minimo de Rewards
const uint PADDLE_WIDTHMinimum = 500;
const uint PADDLE_HEIGHT = 200;
const uint BALL_WIDTH = 100;
const uint BALL_HEIGHT = 100;
const uint REWARD_WIDTH = 50;
const uint REWARD_HEIGHT = 25;
const uint NUM_LEVELS = 3;//0,1 y 2
//numero de vidas
//const uint NUM_VIDAS = 3;
//si queremos ir rapido
const uint NUM_VIDAS = 1;




//niveles
const string LEVEL_NAMES[NUM_LEVELS]{ //Array con la información de niveles
		"../Maps/level01.dat","../Maps/level02.dat","../Maps/level03.dat"
};

using uint = unsigned int;

class Game; //para evitar llamada ciclica entre Game y PlayGameState
//es el estado de juego de arkanoid , simula a Game
class PlayGameState : public GameState
{

		private:

			//escenario heredado de GameState , digo yo que para ve en que estado estamos
			list<GameObject*> estadosJuego;
			//lista de objetos y rewards


			//iterador Global para saber todo el rato la posicion de reward y a cual estamos apuntando
			list<Reward*>::iterator iteradorGlobal;
			bool exit, gameOver, win;
			bool renderTime = false;
			bool loadGame = false;
			//para que si accedemos a un nivel con loadGame no s nos reinicie el contador por defecto
			bool loadGameTime = false;
			bool menu = true;
			int currentLevel = 0;
			int numVidas = 1;
			int nRewards = 0;

			int FRAME_RATE = 10;//****

			static const string PlayGameID;

			unsigned int deltaTime, elapsedTicks;

			Paddle* paddle = nullptr;
			Ball* ball = nullptr;
			MapBlock* blockMap = nullptr;
			Reward* reward = nullptr;

			//las 3 paredes del juego
			Wall* LeftWallGO = nullptr;
			Wall* RightWallGO = nullptr;
			Wall* TopWallGO = nullptr;
			//tiempo
			Time* time = nullptr;
			//GameObject 
			GameObject* go = nullptr;

			

			//Creamos lista de objetos arkanoid
			list<ArkanoidObject*>objectsListArk;
			//lista  de objetos rewards
			list<Reward*> rewards;

			//referencia a Game
			Game* game;

		public:
			//constructora para crear la instancia de clase sin cuerpo en cpp
			PlayGameState() {};
			//primera constructora
			PlayGameState(Game * game);
			//segunda constructora con bool load
			PlayGameState(Game* game, bool load);
			//destructora
		    ~PlayGameState();
			//metodos
			bool menuBool();
			void CambiarMenuBool(bool menuu);
			void CrearReward(SDL_Rect blockRect);
			void DestruirReward(Reward* reward);
			void render();
			void handleEvents();
			void resetStateBall();
			void resetStatePaddle();
			int ActualLevel();
			void update();
			const int alturaPantalla();
			const int anchuraPantalla();
			bool CollideBall(SDL_Rect rectBall, Vector2D& CollisionVector);
			bool CollideReward(SDL_Rect rectReward, int rewardType);
			void EfectosRewards(int rewardType);
			void resetState();
			void InitGameObjects();
			bool Win();
			bool Lose();
			void NextLevel();
			int NumVidas();
			void CargarNextLevel();
			void RepetirLevel();
			void QuitarVida();
			void LoadLevel();
			void SaveFile();
			int NumeroRewards();
			void TimeLoadGame();
			//clase  nos dirá una comprobacion de entrada a el estado PlayGameState
			virtual string getStateID() const { return PlayGameID; }
			virtual bool onEnter();
			virtual bool onExit();

};
