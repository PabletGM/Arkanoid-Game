//Pablo Garcia Moreno 



#include "checkML.h"
#include <iostream>
#include "Game.h"

using namespace std;
using uint = unsigned int;

int main(int argc, char* argv[]) 
{
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	Game* game= nullptr;
	//excepciones solo en game
	try
	{
		////creas instancia de clase Game para que cargue texturas primero
		game = new Game();
		//menu
 		while (!game->EndGame())
		{
			//renderizamos estado actual
			game->run();
		}
	}
	//excepciones de formato , al guardar
	catch (FileFormatError e)
	{
		cout << e.what();
		cout << endl;
	}
	//excepciones de inicializacion de SDL
	catch (SDLError s)
	{
		cout << s.what();
		cout << endl;
	}
	//excepciones de archivo no encontrado
	catch (FileNotFoundError f)
	{
		cout << f.what();
		cout << endl;
	}
	delete(game);
	return 0;
}

	