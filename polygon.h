#ifndef POLYGON_H
#define RPOLYGON_H

#include "polygonBase.h"

using namespace std;

namespace polygons{

// ------------------------------------------------------------------------------------------

// Derived classes for specific polygons
// ------------------------------------------------------------------------------------------

// ISOSCELES TRIANGLE
template <class T>
class isoTriangle : public polygon<T>{
	public:
		// Default constructor (unit side length at the origin)
		isoTriangle() : polygon<T>(3, 0, 0, 1) {};

		// Parametrised constructor
		isoTriangle(T p_x, T p_y, T p_L) : polygon<T>(3, p_x, p_y, p_L) {};
	
		// Function to return the type of polygon
		string type();
};

// Function to return the type of polygon
template <class T> string isoTriangle<T>::type(){
	return "Isoceles Triangle";
}

// ------------------------------------------------------------------------------------------

// SQUARE
template <class T>
class square : public polygon<T>{
	public:
		// Default constructor (unit side length at the origin)
		square() : polygon<T>(4, 0, 0, 1) {};

		// Parametrised constructor
		square(T p_x, T p_y, T p_L) : polygon<T>(4, p_x, p_y, p_L) {};
	
		// Function to return the type of polygon
		string type();
};

// Function to return the type of polygon
template <class T> string square<T>::type(){
	return "Square";
}

// ------------------------------------------------------------------------------------------

// RECTANGLE
template <class T>
class rectangle : public square<T>{
	public:
		// Default constructor (unit side length at the origin)
		rectangle() : square<T>() {};

		// Parametrised constructor
		rectangle(T p_x, T p_y, T p_W, T p_H ) : square<T>(4, p_x, p_y, 1) {
      this->scaleCentre(p_W, p_H, 0);  
    };
	
		// Function to return the type of polygon
		string type();
};

// Function to return the type of polygon
template <class T> string rectangle<T>::type(){
  return "Rectangle";
}

// ------------------------------------------------------------------------------------------

// PENTAGON
template <class T>
class pentagon : public polygon<T>{
	public:
		// Default constructor (unit side length at the origin)
		pentagon() : polygon<T>(5, 0, 0, 1) {};

		// Parametrised constructor
		pentagon(T p_x, T p_y, T p_L) : polygon<T>(5, p_x, p_y, p_L) {};
	
		// Function to return the type of polygon
		string type();
};

// Function to return the type of polygon
template <class T> string pentagon<T>::type(){
	return "Pentagon";
}

// ------------------------------------------------------------------------------------------

// HEXAGON
template <class T>
class hexagon : public polygon<T>{
	public:
		// Default constructor (unit side length at the origin)
		hexagon() : polygon<T>(6, 0, 0, 1) {};

		// Parametrised constructor
		hexagon(T p_x, T p_y, T p_L) : polygon<T>(6, p_x, p_y, p_L) {};
	
		// Function to return the type of polygon
		string type();
};

// Function to return the type of polygon
template <class T> string hexagon<T>::type(){
	return "Hexagon";
}

// ------------------------------------------------------------------------------------------
}

#endif
