#pragma once
#include "Texture.h"
#include "Vector2D.h"

class GameObject
{
	public:
		GameObject();
		virtual ~GameObject() {};
		//metodo abstracto ya que todas las clases hijas lo utilizan
		virtual void render()=0;
		virtual void update()=0;
		//no es abstracto ya que no lo poseen todas las clases
		virtual void handleEvents(bool& exit,SDL_Event event);
	private:

    protected:
		
		


};
