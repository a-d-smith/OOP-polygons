
#ifndef MANAGER_H
#define MANAGER_H

#include "polygon.h"
#include <map>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

namespace polygons{

// ------------------------------------------------------------------------------------------

// A class to manage the polygons in a session
// ------------------------------------------------------------------------------------------

template <class T>
class manager{
  protected:
    // A map for polygons. Each polygon in the library has a (string) name.
    map<string, polygon<T>*> m_library;  
	public:
		// Default constructor
    manager(){};

    // Default destructor
    ~manager(){};

    // Functions to add / remove / get polygons in the library
    // --------------------------------------------------------------------------------------
    void add(polygon<T> *p_polygon, string p_name);
    bool exists(string p_name);
    polygon<T> *& get(string p_name);
    void remove(string p_name);


    // A function to list all polygons
    void listAll();

    // Function to write a .htm file which displays the polygons.
    void display(string p_filename);
};

// Functions to add / remove / get polygons in the library
// --------------------------------------------------------------------------------------

// Function adds a polygon to the library
template <class T> void manager<T>::add(polygon<T> *p_polygon, string p_name){
  if (exists(p_name)){
    cerr << "Error: A polygon with name \" " << p_name << " \" already exists." << endl;
    exit(1);
  }
  else{
    m_library[p_name] = p_polygon;
  }
}

// Function returns true if a polygon with the supplied name is in the library
template <class T> bool manager<T>::exists(string p_name){
   return (m_library.find(p_name) != m_library.end());
}

// Function returns the iterator for the polygon with the supplied name
template <class T> polygon<T> *& manager<T>::get(string p_name){
  if (exists(p_name)){
    return m_library.find(p_name)->second;
  }
  else{
    cerr << "Error: Can not get polygon \" " << p_name << " \", as it does not exist." << endl;
    exit(1);
  }
}

// Function removes the polygon from the library with the supplied name
template <class T> void manager<T>::remove(string p_name){
  if (exists(p_name)){
    typename map<string, polygon<T>*>::iterator it;
    it = m_library.find(p_name);
    m_library.erase(it);
  }
  else{
    cerr << "Error: Can not remove polygon \" " << p_name << " \", as it does not exist." << endl;
    exit(1);
  }
}

// A function to list all polygons.
template <class T> void manager<T>::listAll(){
  if (m_library.size() == 0){
    cout << "No polygons have been created" << endl;  
  }
  else{
    // Output the top row of the table
    cout << setw(44) << "Name"       << " | ";
    cout << setw(6)  << "Sides"      << " | ";
    cout << setw(20) << "Type"       << " | ";
    cout << setw(10) << "Modified?"  << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    // Loop over all of the polygons
    typename map<string, polygon<T>*>::iterator it;
    for (it = m_library.begin(); it != m_library.end(); it++){
      // Output the name of the polygon
      cout << setw(44) << it->first          << " | ";
      cout << setw(6)  << it->second->N()    << " | ";
      cout << setw(20) << it->second->type() << " | ";
      cout << setw(10) << it->second->modified() << endl;
    }
  }
}

// Function to write a .htm file which displays the polygons.
template <class T> void manager<T>::display(string p_filename){
  if (m_library.size() == 0){
    cerr << "Error: No polygons exist to visualise!" << endl;
    exit(1);
  }


  // Open the output file for writing
  ofstream oFile;
  oFile.open(p_filename + ".htm");
  if (!oFile.is_open()){
    cerr << "Error: Can not open file \" " << p_filename << ".htm" << " \" for writing" << endl;  
    exit(1);
  }

  // Start off the HTML file
  oFile << "<!DOCTYPE HTML>"                                         << endl;
  oFile << "<head>"                                                  << endl;
  oFile << "  <title>Polygon Visualisation</title>"                  << endl;
  oFile << "</head>"                                                 << endl;
  oFile << "<body>"                                                  << endl;
  oFile << "  <h1>Polygon Visualisation</h1>"                        << endl; 
  oFile << "  <canvas id='canv' width='800' height='600'>"           << endl;
  oFile << "    Sorry your browser doesn't support the HTML5 canvas" << endl;
  oFile << "  </canvas>"                                             << endl;
  oFile << "  <script type='text/javascript'>"                       << endl;
  oFile << "    // Set up the canvas"                                << endl;
  oFile << "    var c = document.getElementById('canv');"            << endl;
  oFile << "    var ctx = c.getContext('2d');"                       << endl;

  // The canvas on to which we are drawing has width 800px, height 600px
  T W = 800;
  T H = 600;

  // The point (0, 0) is defied to be the top left corner and (W, H) is the bottom right
  // For isometric projection (assuming 1:1 scale, and coinciding origins for now), 
  // the conversion from a 3D (x, y, z) coordinate to a 2D (a, b) coordinate is:
  //
  //   a = (y + x) * cos(PI/6);
  //   b = (y - x) * sin(PI/6) + z;
  //
  // We need to find the maximum and minimum values of a & b for all vertices to be drawn
  // when using this 1:1, then we can scale the axes such that we are sure all polygons
  // in the library will be displayed.


  T minA =  9999999999999999;
  T maxA = -9999999999999999;
  T minB =  9999999999999999;
  T maxB = -9999999999999999;

  T minX =  9999999999999999;
  T maxX = -9999999999999999;
  T minY =  9999999999999999;
  T maxY = -9999999999999999;
  T minZ =  9999999999999999;
  T maxZ = -9999999999999999;

  // Loop over all of the polygons
  typename map<string, polygon<T>*>::iterator it;
  for (it = m_library.begin(); it != m_library.end(); it++){
    // Loop over all of the vertices
    for (int i=0; i<it->second->N(); i++){
      vertex<T> vtx = (*(it->second))[i];

      // Calcualte a & b
      T a = (vtx.y() + vtx.x()) * cos(PI/6);
      T b = (vtx.y() - vtx.x()) * sin(PI/6) + vtx.z();

      // Check a
      minA = min(a, minA);
      maxA = max(a, maxA);

      // Check b
      minB = min(b, minB);
      maxB = max(b, maxB);

      // Check x, y & z
      minX = min(vtx.x(), minX);
      maxX = max(vtx.x(), maxX);
      minY = min(vtx.y(), minY);
      maxY = max(vtx.y(), maxY);
      minZ = min(vtx.z(), minZ);
      maxZ = max(vtx.z(), maxZ);
    }
  }

  // We now define a margin size around the canvas
  T M = 20;

  // Now we can determine the scale factor to ensure everything fits nicely
  T f = min( (W - 2*M)/(maxA - minA), (H - 2*M)/(maxB - minB));

  // Now we can convert between (x, y, z) to the 2D canvas plane (X, Y) using:
  // 
  //   X = M + f * ( (y + x)*sin(PI/6) - minA );
  //   Y = M + f * ( (y + x)*sin(PI/6) + z - minB );


  // Here we want to draw the isometric grid on to which we shall draw our polygons.
  // We will either draw grid lines every ... 0.1, 1, 10, 100, ... units depending
  // on the data we have. 
 
  // If all of the polygons are in a single plane then we will have issues trying
  // to draw the axis normal to the plane in which case we shall set the max and min
  // values by hand


  if (abs(maxZ - minZ) == 0){
    if (abs(maxY - minY) == 0){
      maxY = maxX;
      minY = minX;
    }
    maxZ = maxY;
    minZ = minY;
  }

  if (abs(maxY - minY) == 0){
    if (abs(maxX - minX) == 0){
      maxX = maxZ;
      minX = minZ;
    }
    maxY = maxX;
    minY = minX;
  }

  if (abs(maxX - minX) == 0){
    if (abs(maxZ - minZ) == 0){
      maxZ = maxY;
      minZ = minY;
    }
    maxX = maxZ;
    minX = minZ;
  }

  // We want at least 10 ticks on the display...
  // For a tick size of 10^m, we want to find m such that the number of ticks,
  //   T(m) >= 10 && T(m+1) < 10;
  //
  // T(m) = floor((maxX - minX)/(10^m)) (on the x-axis)

  // First try mx = 0
  int mx = 0;
  bool optimum{false};

  while (!optimum){
    if (floor((maxX - minX) / pow(10,mx)) < 10){
      // T(m) < 10
      // Need to reduce mx
      mx--;    
    }
    else{
      // Need to check T(m+1) < 10
      if (floor((maxX - minX) / pow(10, mx+1)) < 10){
        // This scale is good  
        optimum = true;
      }
      else{
        // We need to increase mx
        mx++;
      }
    }
  }

  // Now repeat for the y- & z-axes
  int my = 0;
  optimum = false;

  while (!optimum){
    if (floor((maxY - minY) / pow(10, my)) < 10){
      // T(m) < 10
      // Need to reduce my
      my--;    
    }
    else{
      // Need to check T(m+1) < 10
      if (floor((maxY - minY) / pow(10, my+1)) < 10){
        // This scale is good  
        optimum = true;
      }
      else{
        // We need to increase my
        my++;
      }
    }
  }
   
  int mz = 0;
  optimum = false;

  while (!optimum){
    if (floor((maxZ - minZ) / pow(10, mz)) < 10){
      // T(m) < 10
      // Need to reduce mz
      mz--;    
    }
    else{
      // Need to check T(m+1) < 10
      if (floor((maxZ - minZ) / pow(10, mz+1)) < 10){
        // This scale is good  
        optimum = true;
      }
      else{
        // We need to increase mz
        mz++;
      }
    }
  }

  // Now we have mx, my and mz. We need to choose the minimum
  int m = min(mx, my);
  m = min(m, mz);

  // Set the colour to grey
  oFile << "    ctx.strokeStyle = '#DDDDDD';"                       << endl;

  // Now draw the isometric grid
  T X, Y;

  // Lines parallel to the x-axis
  for (T j=minY; j<=maxY; j+= pow(10, m)){
    for (T k=minZ; k<=maxZ; k+= pow(10, m)){
      oFile << "    ctx.beginPath();"                             << endl;
        
      X = M + f * ( (j + minX) * cos(PI/6) - minA ) + 0.5;
      Y = M + f * ( (j - minX) * sin(PI/6) + k - minB) + 0.5;
      oFile << "    ctx.moveTo(" << X << ", " << Y << ");"        << endl;

      X = M + f * ( (j + maxX) * cos(PI/6) - minA ) + 0.5;
      Y = M + f * ( (j - maxX) * sin(PI/6) + k - minB) + 0.5;
      oFile << "    ctx.lineTo(" << X << ", " << Y << ");"        << endl;
      oFile << "    ctx.stroke();"                             << endl;
    }
  }

  // Lines parallel to the y-axis
  for (T i=minX; i<=maxX; i+= pow(10, m)){
    for (T k=minZ; k<=maxZ; k+= pow(10, m)){
      oFile << "    ctx.beginPath();"                             << endl;
        
      X = M + f * ( (minY + i) * cos(PI/6) - minA ) + 0.5;
      Y = M + f * ( (minY - i) * sin(PI/6) + k - minB) + 0.5;
      oFile << "    ctx.moveTo(" << X << ", " << Y << ");"        << endl;

      X = M + f * ( (maxX + i) * cos(PI/6) - minA ) + 0.5;
      Y = M + f * ( (maxX - i) * sin(PI/6) + k - minB) + 0.5;
      oFile << "    ctx.lineTo(" << X << ", " << Y << ");"        << endl;
      oFile << "    ctx.stroke();"                                << endl;
    }
  }

  // Lines parallel to the z-axis
  for (T i=minX; i<=maxX; i+= pow(10, m)){
    for (T j=minY; j<=maxY; j+= pow(10, m)){
      oFile << "    ctx.beginPath();"                             << endl;
        
      X = M + f * ( (j + i) * cos(PI/6) - minA ) + 0.5;
      Y = M + f * ( (j - i) * sin(PI/6) + minZ - minB) + 0.5;
      oFile << "    ctx.moveTo(" << X << ", " << Y << ");"        << endl;

      X = M + f * ( (j + i) * cos(PI/6) - minA ) + 0.5;
      Y = M + f * ( (j - i) * sin(PI/6) + maxZ - minB) + 0.5;
      oFile << "    ctx.lineTo(" << X << ", " << Y << ");"        << endl;
      oFile << "    ctx.stroke();"                                << endl;
    }
  }
  
  T X1, X2, Y1, Y2;
  oFile << "    ctx.strokeStyle = '#000000';"                     << endl;

  // Loop over all of the polygons
  for (it = m_library.begin(); it != m_library.end(); it++){
    // Loop over all of the vertices
    for (int i=0; i<it->second->N(); i++){
      vertex<T> vtx1 = (*(it->second))[i];
      vertex<T> vtx2 = (*(it->second))[(i + 1) % it->second->N()];

      // Calcualte X & Y
      X1 = M + f * ( (vtx1.y() + vtx1.x()) * cos(PI/6) - minA );
      Y1 = M + f * ( (vtx1.y() - vtx1.x()) * sin(PI/6) + vtx1.z() - minB);

      X2 = M + f * ( (vtx2.y() + vtx2.x()) * cos(PI/6) - minA );
      Y2 = M + f * ( (vtx2.y() - vtx2.x()) * sin(PI/6) + vtx2.z() - minB);
 
      oFile << "    ctx.beginPath();"                             << endl;
      oFile << "    ctx.moveTo(" << X1 << ", " << Y1 << ");"      << endl;
      oFile << "    ctx.lineTo(" << X2 << ", " << Y2 << ");"      << endl;
      oFile << "    ctx.stroke();"                                << endl;
    }
  }
  
  // Finish off the HTML file
  oFile << "  </script>"                                             << endl;
  oFile << "</body>"                                                 << endl;

  // Close the file
  oFile.close();
}

}
#endif
