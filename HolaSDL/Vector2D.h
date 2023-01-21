#pragma once
#include <iostream>

class Vector2D {
	private:
		double x;
		double y;
	public:
		//constructora
		Vector2D();
		Vector2D(double x, double y);
		//consultar componente X
		double getX() const;
		//consultar componente Y
		double getY() const;
		//inicializar componente X
		void setX(double newX) ;
		//inicializar componente Y
		void setY(double newY) ;
		//normalizar el vector
		void normalize();
		//suma de vector
		Vector2D operator+(const Vector2D& v) const;
		//resta de vectors
		Vector2D operator-(const Vector2D& v) const;
		//producto escalar de vectores
		Vector2D operator*(double d) const;
		//producto de un escalar por un vector
		double operator*(const Vector2D& d) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
}; 
