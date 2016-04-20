// This "vertex" class template is defined to hold a cartesian position vector (x, y, z) 
// 
// This template can be used with mutliple data types, for example double or float, depending
// on the precision required.
//
// Geometrical transformations (translation, scale, rotations) are defined for a "vertex"
// ------------------------------------------------------------------------------------------

#ifndef VERTEX_H
#define VERTEX_H

#include<cmath>
#include<iostream>
#define PI 3.14159265358979323846

using namespace std;

namespace polygons{

template <class T>
class vertex {
  protected:
	  // An array to hold the x, y and z coordinates of the vertex
    T m_x[3];
  public: 
    // CONSTRUCTORS AND DESTRUCTORS
    // --------------------------------------------------------------------------------------

    // Default constructor (place vertex at origin)
    vertex();

    // Parametrised constructor
    vertex(T p_x1, T p_x2, T p_x3);

    // Destructor
    ~vertex(){};

    // Copy constructor
    vertex(const vertex<T> &);

    // Copy assignment operator
    vertex<T> &operator=(const vertex<T> &);

    // --------------------------------------------------------------------------------------


    // ACCESS FUNCTIONS
    // --------------------------------------------------------------------------------------

    T x(); 
    T y(); 
    T z(); 

		// Access function for the ith positional component.
		T x(int p_i);

		// Function to output the vertex using <<
		friend ostream & operator<<(ostream &p_outStream, vertex<T> const &p_vtx){
			p_outStream << "( " << p_vtx.m_x[0] << ", " << p_vtx.m_x[1] << ", " << p_vtx.m_x[2] << " )";
			return p_outStream;
		}

		// Setter functions for the x, y, z-components 
    void x(T p_x); 
    void y(T p_y);
    void z(T p_z);

    // Setter function for all components in one go
    void pos(T p_x, T p_y, T p_z);

    // --------------------------------------------------------------------------------------


    // GEOMETRICAL TRANSFORMATIONS ON THE VERTEX
    // --------------------------------------------------------------------------------------

    // Translate the vertex by a given amount (p_x, p_y, p_z)
    void translate(T p_x, T p_y, T p_z);

    // Rotate the vertex about the x-axis through an angle theta (specified in radians)
    void rotateX(T p_theta);

    // Rotate the vertex about the y-axis through an angle theta (specified in radians)
    void rotateY(T p_theta);

    // Rotate the vertex about the z-axis through an angle theta (specified in radians)
    void rotateZ(T p_theta);

    /* Rotate the vertex around the line joining the points (x1, y1, z1) & (x2, y2, z2)
     * through an angle theta (specified in radians).
     * 
     * e.g. to rotate the vertex around the z-axis (which goes through the origin) through an
     * angle of 90 degrees, use:
     * 
     *     myVertex.rotate(0,0,0, 0,0,1, PI/2);
     */ 
    void rotate(T p_x1, T p_y1, T p_z1, T p_x2, T p_y2, T p_z2, T p_theta);

    // Scale the distance of the vertex from a point (p_x, p_y, p_z) by factors p_fx, p_fy, p_fz
    void scale(T p_x, T p_y, T p_z, T p_fx, T p_fy, T p_fz);
     
    // --------------------------------------------------------------------------------------

};






// CONSTRUCTORS AND DESTRUCTORS
// ------------------------------------------------------------------------------------------

// Default constructor (place vertex at origin)
template <class T> vertex<T>::vertex(){
  m_x[0] = 0;
  m_x[1] = 0;
  m_x[2] = 0;
}

// Parametrised constructor
 template <class T> vertex<T>::vertex(T p_x1, T p_x2, T p_x3){
  m_x[0] = p_x1;
  m_x[1] = p_x2;
  m_x[2] = p_x3;
}

// Copy constructor
template <class T> vertex<T>::vertex(const vertex<T> &vtx){
  for (int i{0}; i<3; i++){
    m_x[i] = vtx.m_x[i];
  }
}

// Copy assignment operator
template <class T> vertex<T> & vertex<T>::operator=(const vertex<T> &vtx){
  // Disallow self assignment
  if (&vtx == this) return *this;

  for (int i{0}; i<3; i++){
    m_x[i] = vtx.m_x[i];
  }
  
  return *this;
}

// ------------------------------------------------------------------------------------------


// ACCESS FUNCTIONS
// ------------------------------------------------------------------------------------------

// Get the x, y, z coordinates separately
template <class T> T vertex<T>::x(){ return m_x[0]; }
template <class T> T vertex<T>::y(){ return m_x[1]; }
template <class T> T vertex<T>::z(){ return m_x[2]; }

// Get the coordinates directly
template <class T> T vertex<T>::x(int p_i){ return m_x[p_i]; }

// Set the x, y, z coordinates separately
template <class T> void vertex<T>::x(T p_x){ m_x[0] = p_x; }
template <class T> void vertex<T>::y(T p_y){ m_x[1] = p_y; }
template <class T> void vertex<T>::z(T p_z){ m_x[2] = p_z; }

// Set the x, y, z coordinates in one go
template <class T> void vertex<T>::pos(T p_x, T p_y, T p_z){
  m_x[0] = p_x;
  m_x[1] = p_y;
  m_x[2] = p_z;
}

// ------------------------------------------------------------------------------------------


// GEOMETRICAL TRANSFORMATIONS ON THE VERTEX
// ------------------------------------------------------------------------------------------

// Translate the vertex by a given amount
template <class T> void vertex<T>::translate(T p_x, T p_y, T p_z){
  m_x[0] += p_x;
  m_x[1] += p_y;
  m_x[2] += p_z;
}

// Rotate the vertex about the x-axis through an angle theta (specified in radians)
template <class T> void vertex<T>::rotateX(T p_theta){
  // Define the rotation matrix
  T rotX[3][3] = {
    {1,       0     ,       0      },  
    {0, cos(p_theta), -sin(p_theta)},  
    {0, sin(p_theta),  cos(p_theta)} 
  };

  // Make a new array of points at the origin
  T newVertex[3] = {0, 0, 0};

  // Apply the matrix
  for (int i{0}; i<3; i++){
    for (int j{0}; j<3; j++){
      newVertex[i] += rotX[i][j]*m_x[j];
    }
  }

  // Set the coordinates to the new array
  for (int i{0}; i<3; i++){
    m_x[i] = newVertex[i];
  }
}

// Rotate the vertex about the y-axis through an angle theta (specified in radians)
template <class T> void vertex<T>::rotateY(T p_theta){
  // Define the rotation matrix
  T rotY[3][3] = {
    { cos(p_theta), 0 , sin(p_theta)},  
    {     0       , 1 ,      0      },  
    {-sin(p_theta), 0 , cos(p_theta)} 
  };

  // Make a new array of points at the origin
  T newVertex[3] = {0, 0, 0};

  // Apply the matrix
  for (int i{0}; i<3; i++){
    for (int j{0}; j<3; j++){
      newVertex[i] += rotY[i][j]*m_x[j];
    }
  }

  // Set the coordinates to the new array
  for (int i{0}; i<3; i++){
    m_x[i] = newVertex[i];
  }
}

// Rotate the vertex about the z-axis through an angle theta (specified in radians)
template <class T> void vertex<T>::rotateZ(T p_theta){
  // Define the rotation matrix
  T rotZ[3][3] = {
    {cos(p_theta), -sin(p_theta), 0},  
    {sin(p_theta),  cos(p_theta), 0}, 
    {      0     ,       0      , 1},  
  };

  // Make a new array of points at the origin
  T newVertex[3] = {0, 0, 0};

  // Apply the matrix
  for (int i{0}; i<3; i++){
    for (int j{0}; j<3; j++){
      newVertex[i] += rotZ[i][j]*m_x[j];
    }
  }

  // Set the coordinates to the new array
  for (int i{0}; i<3; i++){
    m_x[i] = newVertex[i];
  }
}

// Rotate the vertex around the line joining the points (x1, y1, z1) & (x2, y2, z2)
// through an angle theta (specified in radians).
template <class T> void vertex<T>::rotate(T p_x1, T p_y1, T p_z1, T p_x2, T p_y2, T p_z2, T p_theta){
  // This task is broken up into 5 steps

  //    (1) Translate the vertex such that (x1, y1, z1) is now at the origin
  this->translate(-p_x1, -p_y1, -p_z1); 
  
  //    (2) Rotate around the z-axis so the rotation axis is in the xz plane
	T alpha = atan2( p_y2 - p_y1, p_x2 - p_x1 );
  this->rotateZ( -alpha );

  //    (3) Rotate around the y-axis so the rotation axis is along the z-axis
	T beta = atan2(pow(pow(p_x2 - p_x1, 2) + pow(p_y2 - p_y1, 2), 0.5), p_z2 - p_z1);
  this->rotateY( -beta );

  //    (4) Rotate by theta around the z-axis
  this->rotateZ(p_theta);

  //    (5) Do the inverse of steps (3), (2) and (1).
  this->rotateY( beta );
  this->rotateZ( alpha );
  this->translate(p_x1, p_y1, p_z1); 
}

// Scale the distance of the vertex from a point (x, y, z) by factors fx, fy, fz
template <class T> void vertex<T>::scale(T p_x, T p_y, T p_z, T p_fx, T p_fy, T p_fz){
  m_x[0] = p_x + (m_x[0] - p_x)*p_fx;
  m_x[1] = p_y + (m_x[1] - p_y)*p_fy;
  m_x[2] = p_z + (m_x[2] - p_z)*p_fz;
}
 
}

#endif
