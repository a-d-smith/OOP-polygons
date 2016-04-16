#ifndef POLYGON_H
#define POLYGON_H

#include "vertex.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace polygons{

// Abstract base class for a polygon
// ------------------------------------------------------------------------------------------
template <class T>
class polygon{
	protected:
		// All polygons are made up of a list of vertices. Here we the STL vector container to 
		// hold this list of points  
		vector<vertex<T>> m_vertices;
	public:
		// Destructor
		~polygon(){};

		// FUNCTIONS TO GET INFORMATION ON THE POLYGON
		// --------------------------------------------------------------------------------------

		// Function to return the number of vertices in the polygon
		int N();

		// Function to return a vertex at the centre point of the polygon 
		vertex<T> centre();

		// Function to return a vertex which lies unit distance from the origin in the direction 
		// of the normal to the surface of the polygon
		vertex<T> normal();

		// Pure virtual function to return the type of polygon
		virtual string type() = 0;

		// Function to list the vertices in the polygon
		void listVertices();

		// --------------------------------------------------------------------------------------


		// FUNCTIONS TO TRANSFORM THE POLYGON
		// --------------------------------------------------------------------------------------

		// Function to translate the polygon by a vector (x, y, z)
		void translate(T p_x, T p_y, T p_z);

		// Function to scale the polygon about a point (x, y, z) by scale factors fx, fy and fz
		void scale(T p_x, T p_y, T p_z, T p_fx, T p_fy, T p_fz);

		// Function to scale the polygon about its centre by scale factors fx, fy and fz
		void scaleCentre(T p_fx, T p_fy, T p_fz);

		// Function to rotate the polygon about a point (x1, y1, z1) about the line pointing from 
		// this point to a second point (x2, y2, z2) through an angle theta
		void rotate(T p_x1, T p_y1, T p_z1, T p_x2, T p_y2, T p_z2, T p_theta);

		// Function to rotate the polygon about its centre about the axis normal to it's surface 
		// through an angle theta
		void rotateCentre(T p_theta);

		// --------------------------------------------------------------------------------------
};

// FUNCTIONS TO GET INFORMATION ON THE POLYGON
// ------------------------------------------------------------------------------------------

// Function to return the number of vertices in the polygon
template <class T> int polygon<T>::N(){
	return m_vertices.size();
}

// Function to return a vertex at the centre point of the polygon 
template <class T> vertex<T> polygon<T>::centre(){
	// Find the average position of all of the vertices
	T xCentre{0};
	T yCentre{0};
	T zCentre{0};

	for (vertex<T> &vtx : m_vertices){
		xCentre += vtx.x();
		yCentre += vtx.y();
		zCentre += vtx.z();
	}
	
	xCentre /= this->N();
	yCentre /= this->N();
	zCentre /= this->N();

	vertex<T> retVertex(xCentre, yCentre, zCentre);

	return retVertex;
}

// Function to return a vertex which lies unit distance from the origin in the direction 
// of the normal to the surface of the polygon
template <class T> vertex<T> polygon<T>::normal(){
	// Assuming the polygon is planar (and it should have at least 3 vertices), we can find
	// the normal by finding the cross product of two of the edge vectors

	T xNorm[3] = {0, 0, 0};
	
	for (int i{0}; i<3; i++){
		for (int j{0}; j<3; j++){
			for (int k{0}; k<3; k++){
				xNorm[i] += (i - j)*(j -k)*(k - i)*(m_vertices[2].x(j) - m_vertices[0].x(j))*(m_vertices[1].x(k) - m_vertices[0].x(k))/2;
			}
		}
	}

	// Now normalise the vector
	T L = pow(pow(xNorm[0], 2) + pow(xNorm[1], 2) + pow(xNorm[2], 2), 0.5); 

	xNorm[0] /= L;
	xNorm[1] /= L;
	xNorm[2] /= L;

	vertex<T> retVertex(xNorm[0], xNorm[1], xNorm[2]);

	return retVertex;
}

// Function to list the vertices in the polygon
template <class T> void polygon<T>::listVertices(){
	cout << "Type : " << this->type() << endl;
	for (vertex<T> &vtx : m_vertices){
		cout << "   " << vtx << endl;
	}
}

// ------------------------------------------------------------------------------------------


// FUNCTIONS TO TRANSFORM THE POLYGON
// ------------------------------------------------------------------------------------------

// Function to translate the polygon by a vector (x, y, z)
template <class T> void polygon<T>::translate(T p_x, T p_y, T p_z){
	for (vertex<T> &vtx : m_vertices){
		vtx.translate(p_x, p_y, p_z);
	}
}

// Function to scale the polygon about a point (x, y, z) by scale factors fx, fy and fz
template <class T> void polygon<T>::scale(T p_x, T p_y, T p_z, T p_fx, T p_fy, T p_fz){
	for (vertex<T> &vtx : m_vertices){
		vtx.scale(p_x, p_y, p_z, p_fx, p_fy, p_fz);
	}
}

// Function to scale the polygon about its centre by scale factors fx, fy and fz
template <class T> void polygon<T>::scaleCentre(T p_fx, T p_fy, T p_fz){
	vertex<T> cent = this->centre();
	this->scale(cent.x(), cent.y(), cent.z(), p_fx, p_fy, p_fz);
}

// Function to rotate the polygon about a point (x1, y1, z1) about the line pointing from 
// this point to a second point (x2, y2, z2) through an angle theta
template <class T> void polygon<T>::rotate(T p_x1, T p_y1, T p_z1, T p_x2, T p_y2, T p_z2, T p_theta){
	for (vertex<T> &vtx : m_vertices){
		vtx.rotate(p_x1, p_y1, p_z1, p_x2, p_y2, p_z2, p_theta);
	}
}

// Function to rotate the polygon about its centre about the axis normal to it's surface 
// through an angle theta
template <class T> void polygon<T>::rotateCentre(T p_theta){
	vertex<T> cent = this->centre();
	vertex<T> norm = this->normal();
	this->rotate(cent.x(), cent.y(), cent.z(), cent.x() + norm.x(), cent.y() + norm.y(), cent.z() + norm.z(), p_theta);
}

// ------------------------------------------------------------------------------------------


// Derived class for a general regular polygon
// ------------------------------------------------------------------------------------------
// In this class we define a regular polygon by creating vertices at regular spacings along
// a circle. All polygons can only be produced in the x-y plane, but can be transformed into
// any orientation in 3D.

template <class T>
class regularPolygon : public polygon<T>{
	protected:
		// A function to help with the construction of an N-dimensional regular polygon at a 
		// specified origin (x, y) with a distance, R, between the verticies and that origin.
		vector<vertex<T>> construct(int p_N, T p_x, T p_y, T p_R);
};

template <class T> vector<vertex<T>> regularPolygon<T>::construct(int p_N, T p_x, T p_y, T p_R){
	vector<vertex<T>> retVect;
	for (int i{0}; i < p_N; i++){
		vertex<T> newVtx(p_x + p_R*cos(i*2*PI/double(p_N)), p_y + p_R*sin(i*2*PI/double(p_N)), 0);
		retVect.push_back(newVtx);
	}

	return retVect;
}


// ------------------------------------------------------------------------------------------


// Derived classes for specific regular polygons
// ------------------------------------------------------------------------------------------

// ISOSCELES TRIANGLE
template <class T>
class isoTriangle : public regularPolygon<T>{
	public:
		// Default constructor (unit radius at the origin)
		isoTriangle();

		// Parametrised constructor
		isoTriangle(T p_x, T p_y, T p_R);
	
		// Function to return the type of polygon
		string type();
};

// Default constructor (unit radius at the origin)
template <class T> isoTriangle<T>::isoTriangle(){
	this->m_vertices = this->construct(3, 0, 0, 1);
}

// Parametrised constructor
template <class T> isoTriangle<T>::isoTriangle(T p_x, T p_y, T p_R){
	this->m_vertices = this->construct(3, p_x, p_y, p_R);
}
	
// Function to return the type of polygon
template <class T> string isoTriangle<T>::type(){
	return "Isoceles Triangle";
}

// ------------------------------------------------------------------------------------------
}

#endif
