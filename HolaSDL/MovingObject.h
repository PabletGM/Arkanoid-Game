#pragma once
//hereda de ArkanoidObject
#include "ArkanoidObject.h"

class MovingObject: public ArkanoidObject
{
	public:
		MovingObject();
		virtual ~MovingObject(){};
		virtual void resetState();
		virtual void loadFromFile(ifstream& lectura);
		virtual void SaveToFile(ofstream& archivo);
	private:
    protected:
		//asi haces el resetState desde aquí 
		Vector2D direccionIni;
		Vector2D posicionIni;

};
