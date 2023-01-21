//se incluye a sí mismo
#include "PlayGameState.h"
//hereda de GameState
#include "GameState.h"


using namespace std;
using uint = unsigned int;



//se declara la constante del ID
const string PlayGameState::PlayGameID = "PLAY";

//constructora, se cargan textturas e inician objetos
PlayGameState::PlayGameState(Game * gameref)
{
	game = gameref;
		exit = gameOver = win = false;
		currentLevel = 0;
		// /*We finally create the game objects*/
		InitGameObjects();
}

PlayGameState::PlayGameState(Game* gameref, bool load)
{           
	game = gameref;
	exit = gameOver = win = false;
	currentLevel = 0;
	loadGame = load;//si es true se cargaran el loadLevel
	loadGameTime = loadGame;//si es true el loadlGame aplicaremos el colntador del nivel Loaded
	// /*We finally create the game objects*/
	InitGameObjects();
	//condicion de load
	
	
}

//destructora de todo
PlayGameState::~PlayGameState()
{
	//destructor de lista con gameObjects
	for (list<ArkanoidObject*>::iterator it = objectsListArk.begin(); it != objectsListArk.end(); it++)
	{
		delete* it;
	}

	//destructor de lista con gameObjects
	for (list<Reward*>::iterator it = rewards.begin(); it != rewards.end(); it++)
	{
		delete* it;
	}

}

//nivel actual
int PlayGameState::ActualLevel()
{
	return currentLevel;
}

//menu bool
bool PlayGameState::menuBool()
{
	return menu;
}

//cambiar menu bool
void PlayGameState::CambiarMenuBool(bool menuNew)
{
	menu = menuNew;
}

//devuelve numVidas
int PlayGameState::NumVidas()
{
	return numVidas;
}


//carga nextLevel
void PlayGameState::CargarNextLevel()
{
	//Si quedan más niveles se carga el siguiente
	if (currentLevel < NUM_LEVELS) {
		//se borra el nivel antiguo
		delete blockMap;
		//destructor de blockMap de la lista, borra el ultimo elemnto
		objectsListArk.pop_back();
		//se carga el nuevo blockMap
		blockMap = new MapBlock(Vector2D(0, 0), game->getTexture(Bricks), WIN_WIDTH - WALL_WIDTH, WIN_HEIGHT / 2 - WALL_HEIGHT, LEVEL_NAMES[currentLevel], this); //Se pasa al siguiente nivel
		blockMap->LoadMap();																																						  //se mete en la lista
		objectsListArk.push_back(blockMap);
		win = false; //Reinicio de la condición
		//Se borran los rewards
		//dejamos la lista vacia despues
		nRewards = 0;
		rewards = {};
	}
}

//para cuando pierdes pero tienes vidas aun cargar el nivel otra vez
void PlayGameState::RepetirLevel()
{
	if (currentLevel < NUM_LEVELS)
	{
		//se borra el nivel antiguo
		delete blockMap;
		//destructor de blockMap de la lista, borra el ultimo elemnto
		objectsListArk.pop_back();
		//se carga el nuevo blockMap
		blockMap = new MapBlock(Vector2D(0, 0), game->getTexture(Bricks), WIN_WIDTH - WALL_WIDTH, WIN_HEIGHT / 2 - WALL_HEIGHT, LEVEL_NAMES[currentLevel], this); //Se pasa al siguiente nivel
		objectsListArk.push_back(blockMap);
		win = false; //Reinicio de la condición
		gameOver = false;
		numVidas = NUM_VIDAS;
		//Se borran los rewards
		nRewards = 0;
		rewards = {};
	}
}

//quitar 1 vida
void PlayGameState::QuitarVida()
{
	numVidas -= 1;
}

void PlayGameState::LoadLevel()
{
	string name;
	cout << "¿Qué partida quieres cargar?: ";
	cin >> name;
	string nombre = "..//Maps//" + name + ".dat";
	//accedemos a leer el archivo 	
	ifstream lectura(nombre);
	//damos ese permiso de lectura a cada objeto pasando el parametro ifstream para 
	//dar en cada sitio valor a las variables
	//sino se encuentra
	if (lectura.is_open())
	{
		//ponemos numVidas
		lectura >> numVidas;
		//ponemos nivel actual
		lectura >> currentLevel;
		//borras mapa actual---> en este caso no porque no se ha creado por el load = true
		//se carga el nuevo blockMap
		//blockMap = new MapBlock(Vector2D(0, 0), game->getTexture(Bricks), WIN_WIDTH - WALL_WIDTH, WIN_HEIGHT / 2 - WALL_HEIGHT, LEVEL_NAMES[currentLevel], this); //Se pasa al siguiente nivel
		//se mete en la lista
		/*objectsListArk.push_back(blockMap);*/
		//arkanoidObjects objetos
		for (auto a : objectsListArk)
		{
			//creamos reward y le pasamos todo por argumento
			a->loadFromFile(lectura);
		}

		//numero de rewards lo leemos
		lectura >> nRewards;
		//arkanoidObjects rewards
		for (int i = 0; i < nRewards; i++)
		{
			//creas los objetos con los pocos argumentos que tienes y luego en el loadFromFile de reward acabas de completar algunos al leer los valores
			rewards.push_back(new Reward(game->getTexture(Rewarding), REWARD_WIDTH, REWARD_HEIGHT, Vector2D{ 0,1 }, 0.8, this));
		}
		for (auto a : rewards)
		{
			a->loadFromFile(lectura);
		}
		lectura.close();
	}
	//si el archivo ha sido abierto comienza proceso de load
	else
	{
		//excepcion
		throw FileNotFoundError("No se puede abrir el archivo");
	}

}

//llamamos al SaveToFile de todos los ArkanoidObjects
void PlayGameState::SaveFile()
{
	string filename;
	//leemos el nombre que pongan en consola
	cin >> filename;
	//unimos el nombre en ruta de datos
	string nombreUbicacion = "..//Maps//" + filename + ".dat";
	//string nombreUbicacion = "..//Imagenes//" + filename + ".dat";
	//creamos archivo ofstream
	ofstream archivo;
	//abrimos el archivo
	archivo.open(nombreUbicacion, ios::out);
	//sino se encuentra
	if (archivo.fail())
	{
		//ponemos game a null para que me deje destruirlo
		this == nullptr;
		//excepcion
		throw FileFormatError("Proceso de guardado fallido ");
	}
	//si el archivo ha sido abierto comienza proceso de guardado
	else
	{
		//antes guardamos en archivo el numero de vidas del player
		archivo << numVidas;
		archivo << endl;
		//guardamos en archivo el numero del nivel del mapa
		archivo << currentLevel;
		archivo << endl;
		//para cada objeto de la lista vamos a su metodo SaveToFile el cual tiene en cuenta las acciones anteriores
		//al archivo ofstream y después lo sobreescribe
		for (auto a : objectsListArk)
		{
			a->SaveToFile(archivo);
		}
		//guardamos numero de rewards
		int n = NumeroRewards();
		archivo << n;
		archivo << endl;
		//guardamos posicion y tipo reward de la lista
		for (auto a : rewards)
		{
			a->SaveToFile(archivo);
		}
		//cerramos flujo
		archivo.close();
	}

}

//devuelve numero de reewards
int PlayGameState::NumeroRewards()
{
	return nRewards;
}

//tiempo de loadGame
void PlayGameState::TimeLoadGame()
{
	if (loadGameTime)
	{
		int timeLoadGame = time->CurrentTime();
		//se llama a update currentTime veces
		for (int i = 0; i < timeLoadGame; i++)
		{
			time->update();
		}
	}

}

bool PlayGameState::onEnter()
{
	std::cout << "entering PlayGameState\n";
	return true;
}

bool PlayGameState::onExit()
{
	std::cout << "exiting  PlayGameState\n";
	return true;;
}

//crear reward
void PlayGameState::CrearReward(SDL_Rect blockRect)
{
	//ver si ha tocado premio
	//poner que tipo de premio es 
	//crear objeto premio
	//render el premio adecuado con fila y columna

	//si choca , vemos si se crea reward o no
	int numRandom = rand() % 100;
	//probabilidad del 25%
	if (numRandom <= 24)
	{
		//vemos que reward ha tocado aleatorio, por ahora haremos 4 tipos de reward
		int numTiposReward = 4;// de 0 a 3, esto es4filas
		int numRandomTipos = rand() % numTiposReward;
		/*int numRandomTipos = 1;*/
		//segun el tipo de reward  en el aleatorio tendremos la fila tendremos una fila diferente
		int fila = numRandomTipos;
		//la columna siempre3 será el frame inicial 0
		int columna = 0;
		//creamos reward y pasamos todo a la constructora , incluido la posicion del bloque desde donde instanciaremos a nuestro reward
		//direccion 0,1 ya que por defecto esta en 0,0 arriba izq
		reward = new Reward(fila, columna, numRandomTipos, blockRect, game->getTexture(Rewarding), REWARD_WIDTH, REWARD_HEIGHT, Vector2D{ 0,1 }, 0.8, this);
		nRewards = nRewards + 1;
		//lo metemos en la lista
		rewards.push_back(reward);
	}
	//si quedan bloques 
}

//destruir reward poniendolo a null
void PlayGameState::DestruirReward(Reward* reward)
{
	iteradorGlobal = rewards.erase(iteradorGlobal);
	//se borra objeto
	delete reward;
	reward = nullptr;
}

//para actualizar su posicion
void PlayGameState::update()
{
	//rederizar tiempo
	 //Cada segundo, se llama al update del tiempo
	time->update();
	if (time->getTimeUp())
	{
		gameOver = true;
	}
	
	//actualizar posicion paddle y ball
	paddle->update();
	ball->update();

	//actualizar time
	
	//actualizar cada reward y su posicion
	iteradorGlobal = rewards.begin();
	while (iteradorGlobal != rewards.end())
	{
		Reward* r = *iteradorGlobal;
		r->update();
		if (iteradorGlobal != rewards.end())++iteradorGlobal;
	}

	//condicion de win 
	if (Win())
	{
		win = true;
		//reiniciamos posiciones de todo y reiniciamos booleanos
		resetState();
	}

	//condicion de derrota
	if (Lose())
	{
		gameOver = true;
		//reiniciamos posiciones de todo y reiniciamos booleanos
		resetState();
	}
	
	

	//si  has perdido para siempre
	if ((NumVidas() <= 0))
	{
		
		game->CambioEstadoPlayEndLose();
	}

	// si has ganado para siempre
	else if ( currentLevel >= NUM_LEVELS)
	{
		
		game->CambioEstadoPlayEndWin();
	}
	
}

//devuelve alturaPantalla
const int PlayGameState::alturaPantalla()
{
	return WIN_HEIGHT;
}
//devuelve anchuraPantalla
const int PlayGameState::anchuraPantalla()
{
	return WIN_WIDTH;
}

//para conocer la posicion de ball y si ha chocado contra algun GO
bool PlayGameState::CollideBall(SDL_Rect rectBall, Vector2D& CollisionVector)
{
	//COLLIDES WALL-BOLA
	if (LeftWallGO->Collides(rectBall, CollisionVector) || RightWallGO->Collides(rectBall, CollisionVector) || TopWallGO->Collides(rectBall, CollisionVector))
	{
		return true;
	}
	//COLLIDES WALL-PADDLE--> mirar comprobacion en paddle update
	// COLLIDES PADDLE-BALL
	if (paddle->CollideBall(rectBall, CollisionVector))
	{
		return true;//si devuelve true lo que tenemos que hacer es distincion de casos para ver como rebota
	}
	//COLLIDES BALL-MAPBLOCK, probabilidad reward
	if (blockMap->collide(rectBall, CollisionVector))
	{
		return true;
	}
	//si estas dan false , devuelve false
	return false;
}

//colision con reward
bool PlayGameState::CollideReward(SDL_Rect rectReward, int rewardType)
{
	//miras si hay colision con paddle y reward
	if (paddle->CollideReward(rectReward))
	{
		//si hay colision elegimos efecto segun reward
		EfectosRewards(rewardType);
		return true;
	}
	return false;
}

//efectos
void PlayGameState::EfectosRewards(int rewardType)
{
	//al coger otro premio nos aseguramos que volvemos a anchura normal
	paddle->PlataformaWidthNormal();
	switch (rewardType)
	{
		//pasar de nivel L, esta en fila 0
	case 0:
		win = true;
		break;

		//alargar plataforma E, se reestablece en siguiente nivel, 
	case 1:
		paddle->AlargarPlataforma();
		break;

		//C-->unknown
		/*case 2:
			break;*/

			//S--> acortar plataforma
	case 2:
		paddle->AcortarPlataforma();
		break;

		//vida extra R ,  esta en fila 4
	case 3:
		numVidas += 1;
		break;

		////M--->unknown
		//case 5:

		//	break;

		////D---> unknown
		//case 6:

		//	break;

		////B--->unknown
		//case 7:

		//	break;

		////T--->unknown
		//case 8:

		//	break;

		////P-->unknown
		//case 9:

		//	break;
	}
}

//reiniciar estado de objetos
void PlayGameState::resetState()
{
	//reseteamos booleanos , al pasar de nivel ya el contador desde 0 asi que loadGameTime = false
	win = gameOver = exit = loadGameTime = false;
	//reseteamos direccion y posicion de bola
	resetStateBall();
	//reseteamos direccion y posicion de paddle
	resetStatePaddle();
}


//cada vez que creas un objeto en initGameObjects lo metes en la lista
void PlayGameState::InitGameObjects()
{
	//pared izquierda , posicion , altura y anchura , textura sidewall,direccion
	LeftWallGO = new Wall(Vector2D(0, 0), WIN_HEIGHT, WALL_WIDTH, game->getTexture(SideWall), Vector2D{ 1,0 });
	objectsListArk.push_back(LeftWallGO);
	//pared derecha , posicion , altura y anchura , textura y direccion
	RightWallGO = new Wall(Vector2D(WIN_WIDTH - WALL_WIDTH, 0), WIN_HEIGHT, WALL_WIDTH, game->textures[SideWall], Vector2D{ -1, 0 });
	objectsListArk.push_back(RightWallGO);
	//pared de arriba , posicion , altura y anchura , textura y direccion
	TopWallGO = new Wall(Vector2D(0, 0), WALL_HEIGHT, WIN_WIDTH, game->getTexture(TopWall), Vector2D{ 0,1 });
	objectsListArk.push_back(TopWallGO);

	//heredan de movingObject
	//create the paddle con textura , posicion y velocidad o direccion inicial, padel con direccion automatica,velocidad de la pala
	paddle = new Paddle(game->getTexture(paddleEnum), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D{ 0,0 }, Vector2D{ 1,-1 }, 3, this);
	objectsListArk.push_back(paddle);
	//create the ball , pones la posicion , pones la altura y anchura , la dirección ,texturas de pelota y este script
	ball = new Ball(Vector2D{ WIN_WIDTH / 2, WIN_HEIGHT * 0.9 }, BALL_WIDTH, BALL_HEIGHT, Vector2D{ 0,-1 }, game->getTexture(ballEnum), this, 3.5);
	objectsListArk.push_back(ball);

	//tiempo
	time = new Time(game->getTexture(Digits), Vector2D{ WIN_WIDTH - WALL_WIDTH - 30 , 0 }, WALL_WIDTH, WALL_HEIGHT, 400);
	objectsListArk.push_back(time);

	//cargo mapa
	blockMap = new MapBlock(Vector2D(0, 0), game->getTexture(Bricks), WIN_WIDTH - WALL_WIDTH * 2, WIN_HEIGHT / 2 - WALL_HEIGHT, LEVEL_NAMES[currentLevel], this);
	objectsListArk.push_back(blockMap);

	//iniciamos mapas, el ultimo objeto para poder sacarlo mas facil, mientras que loadGame = false , es partida normal

	//si es partida normal , LoadMap
	if (!loadGame)
	{
		blockMap->LoadMap();
	}

	//si es partida Load , LoadLevel
	else
	{
		LoadLevel();
	}
	
}

//condicion de victoria y pones imagen
bool PlayGameState::Win()
{
	//si no quedan bloques es que ha ganado
	if (blockMap->getNumBlocks() <= 0 || win)
	{
		
		

		//pasas de nivel
		NextLevel();
		//cargar nextLevel
		CargarNextLevel();

		//solo renderizar YOU WIN sino has ganado del todo
		if (currentLevel < NUM_LEVELS)
		{
			//textura
			Texture* victory = game->getTexture(Winner);
			SDL_Rect destRect;
			destRect.x = destRect.y = 0;
			destRect.w = WIN_WIDTH;
			destRect.h = WIN_HEIGHT;
			victory->render(destRect);
			//cargarla
			SDL_RenderPresent(game->renderer);
			SDL_Delay(500);
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

//condicion de derrota y pones imagen
bool PlayGameState::Lose()
{
	//si la bola ha superado la altura por debajo es que ha perdido
	if (ball->getDestRect().y + ball->getDestRect().h >= WIN_HEIGHT + 50 || gameOver)
	{
		//le quitamos 1 vida
		QuitarVida();

		//si aun le quedan vidas repetimos nivel
		if (NumVidas()>0)
		{
			Texture* lost = game->getTexture(GameOver);
			SDL_Rect destRect;
			destRect.x = destRect.y = 0;
			destRect.w = WIN_WIDTH;
			destRect.h = WIN_HEIGHT;
			lost->render(destRect);
			SDL_RenderPresent(game->renderer);
			SDL_Delay(500);
			//repetimos nivel y mapa
			RepetirLevel();
			return true;
		}
		//sino le quedan vidas 
		return true;
		
		
	}
	else
	{
		return false;
	}

}

//paso de nivel
void PlayGameState::NextLevel()
{
	currentLevel++;
}

//renderizado general
void PlayGameState::render()
{
	
	//hacemos render listaObjetos
	for (auto a : objectsListArk)
	{
		a->render();

	}
	//hacemos render lista rewards
	for (auto b : rewards)
	{
		b->render();

	}
	


}

//controlador de eventos
void PlayGameState::handleEvents()
{
	//creamos evento
	SDL_Event event;
	//aseguramos que hay eventos pendientes
	
	while (SDL_PollEvent(&event) && !exit) 
	{
		paddle->handleEvents(exit, event);
		switch (event.key.keysym.sym) 
		{
			/*se mira si se pulsa escape quit =true*/
			case SDLK_ESCAPE:
				/*ponemos exit a true para que salga del bucle principaL*/
				game->CambioEstadoPlayPause();
				break;
		
		}
	}

}

//reinicio pos bola
void PlayGameState::resetStateBall()
{
	ball->resetState();
}

//reinicio pos paddle
void PlayGameState::resetStatePaddle()
{
	paddle->resetState();
}
