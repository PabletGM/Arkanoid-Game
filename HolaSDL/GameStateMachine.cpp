#include "GameStateMachine.h"
#include "PlayGameState.h"

GameStateMachine::GameStateMachine()
{
	
}

GameStateMachine::~GameStateMachine()
{
	//sino esta vacio haces esto en bucle
	while (!pilaEstados.empty()) {
		//eliminas la primera referencia de la pila
		delete pilaEstados.top();
		//quitas el estado
		pilaEstados.pop();
	}
}

//devuelve el estado actual , el de mas arriba
GameState* GameStateMachine::currentState()
{	 
	/*devuelve primer elemento de todos en pila*/
	return pilaEstados.top();
}

//metes un estado nuevo como actual
void GameStateMachine::pushState(GameState* estadoNuevo)
{
	//asigna estado actual al estado 2 por si necesitamos poner otro estado por encima para que este se quede en segundo plano
	secondState = pilaEstados.top();
	//haces push del nuevo estado
	pilaEstados.push(estadoNuevo);
	pilaEstados.top()->onEnter();
}

//cambiar el estado actual por el estado del argumento
void GameStateMachine::changeState(GameState* estadoNuevo)
{
		if (!pilaEstados.empty())
		{
			//comprobamos el getStateId del primer elemento de la pila y vemos si coincide con
			//el del estado nuevo
			if (pilaEstados.top()->getStateID() == estadoNuevo->getStateID())
			{
				return; // do nothing
			}

			//si se quiere salir del estado
			if (pilaEstados.top()->onExit())
			{
				
				//ponemos el estado 2 a null para que este sea nulo mientras cambiamos el estado primero
				secondState = nullptr;
				//estamos añadiendo el estado actual a la lista de borrar
				elementosBorrar.push_back(currentState());
				//lo quitamos de la pila de estados
				pilaEstados.pop();
			}
		}
		// push back our new state en la pila ,  //Añade el estado y lo ejecuta
		pilaEstados.push(estadoNuevo);
		// initialise it
		pilaEstados.top()->onEnter();
}

//desapilas el elemento de arriba
void GameStateMachine::popState()
{
	 //En caso de no estar vacía la pila
	if (!pilaEstados.empty())
	{
		//ponemos el estado 2 a nulo
		secondState = nullptr;
		////Añade el estado actual a la pila de destrucción
		elementosBorrar.push_back(pilaEstados.top());
		//quitamos el estado actual de la pila
		pilaEstados.pop();
	}
	
}

//para borrarme elementos del estado actual
void GameStateMachine::limpiarLista()
{
	//mientras no este vacia 
	if(!pilaEstados.empty())
	{
		for (GameState* gS : elementosBorrar)
		{
			delete gS;
		}
		//borra la lista , la devuelve a size =0 
		elementosBorrar.clear();
	}
}

void GameStateMachine::render()
{
	//si la pila no esta vacia
	if (!pilaEstados.empty())
	{
		//debemos renderizar tambien el estado seundario aa veces , lo haecmos si no es nulo
		//asi lo renderizará por debajo del actual
		if (secondState != nullptr) 
		{ 
			secondState->render(); 
		}
		//hacer render del elemento de arriba de la pila
		pilaEstados.top()->render();
	}
}

void GameStateMachine::update()
{
	if (!pilaEstados.empty())
	{
		pilaEstados.top()->update();
	}
}

void GameStateMachine::saveFile()
{
	//el PlayGame state creamos otra instancia y la convertimos en nuestra propio estado secundario  PlayGameState
	PlayGameState* instanciaPlay = static_cast<PlayGameState*>(secondState);
	instanciaPlay->SaveFile();
}

void GameStateMachine::LoadFile()
{
	//el PlayGame state creamos otra instancia y la convertimos en nuestra propio estado secundario  PlayGameState
	PlayGameState* instanciaPlay = static_cast<PlayGameState*>(secondState);
	instanciaPlay->LoadLevel();
}

