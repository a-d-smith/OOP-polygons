
#ifndef MANAGER_H
#define MANAGER_H

#include "polygon.h"
#include <map>
#include <string>
#include <iomanip>

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


    // Functions to print the data on all of the polygons
    // --------------------------------------------------------------------------------------

    // A function to list all polygons
    void listAll();

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

// Functions to print the data on all of the polygons
// --------------------------------------------------------------------------------------

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

}
#endif
