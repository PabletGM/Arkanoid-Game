#pragma once
//para poder crear la pila de estados
#include "GameState.h"

//para poder utilizar la pila stack
#include <stack>
//una de las 2 fromas
#include<vector>

//clase que no hereda de nadie ya que se utiliza para que el GameState compruebe en que estado está y pueda pasar a el estado
//o clae hija conveniente

//para evitar recurrencia ciclica
class GameStateMachine	
{
	public:
		GameStateMachine();
		virtual ~GameStateMachine();
		//metodos currentState, pushState, changeState y popState

		//devuelve estado actual
		GameState* currentState();

		//apilar un elemento, pone un estado arriba del todo para indicar nuevo estado actual
		void pushState( GameState* estado);

		//cambia el estado actual por otro que se pase como parametro
		void changeState(GameState* estado);

		//para quitar un elemento del top de la pila quitando el estado actual
		void popState();

		//limpia estados que no se utilizan
		void limpiarLista();

		void render();
		void update();

		void saveFile();
		void LoadFile();

		//elimina la lista de objetos o el escenario del estado activo
	private:
		//atributo una pila de estados o stack de clases GameState
		stack<GameState*> pilaEstados;
		vector<GameState*> elementosBorrar;
		//añadimos estado extra para tener uno en segundo plano
		GameState* secondState = nullptr;
};
