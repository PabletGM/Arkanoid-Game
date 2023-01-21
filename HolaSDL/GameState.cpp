//Se incluye a sí mismo
#include "GameState.h"
#include "Game.h"

GameState::GameState()
{
}

GameState::~GameState()
{
	for (GameObject* g : listaObjetos) delete g;
}

bool GameState::onEnter()
{
	return false;
}

bool GameState::onExit()
{
	return false;
}


void GameState::render()
{
}

void GameState::update()
{
}

void GameState::handleEvents()
{
}

