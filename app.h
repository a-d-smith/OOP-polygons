#ifndef APP_H
#define APP_H

#include "polygon.h"
#include "manager.h"
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

namespace polygons{

// ------------------------------------------------------------------------------------------
// A class to control user input and interface with the manager
// ------------------------------------------------------------------------------------------

template <class T>
class app{
  protected:
		// A manager to hold the polygons
		manager<T> m_man;

		// A string for the display file name
		string m_fileName;

		// Boolean to indicate if the app is in use
		bool m_using;
	public:
		// Default constructor
    app() : m_fileName("defaultVisualisation"), m_using(false){};

		// Parametrised constructor
		app(manager<T> p_man, string p_fileName) : m_man(p_man), m_fileName(p_fileName), m_using(false) {};

		// Destructor
		~app(){};

		// Functions to control the running of the app
		// --------------------------------------------------------------------------------------
		void start();
		void loop();
		void end();

		// Asks the user for a polygon name that either does or doesn't exist in the manager
		string getNewName();		
		string getExistingName();

		// Takes a list of characters and asks the user to input one. The function keeps asking
		// until a listed character is given, this is then returned. The function displays the
		// message msg.
    template <class U> char getOption(initializer_list<U> p_chars, string p_msg);
};

template <class T> void app<T>::start(){
	m_using = true;
	this.loop();
}

template <class T> void app<T>::loop(){
	// Keep calling yourself unless the using flag is set to false
	if (m_using){
		this.loop();
	}
}

template <class T> void app<T>::end(){
	m_using = false;
}

template <class T> string app<T>::getNewName(){
	string nam;

	cout << "Please enter a unique name for this polygon" << endl;
	cout << "  name << ";
	cin  >> nam;

	while (m_man.exists(nam)){
		cout << "  Sorry that name is taken. The list of current names is" << endl;
		m_man.listAll();
		cout << "  name << ";
		cin >> nam;
	}

	return nam;
}

template <class T> string app<T>::getExistingName(){
	string s;
	return s;
}

template <class T> template <class U> char app<T>::getOption(initializer_list<U> p_chars, string p_msg){
	char c;
	return c;
}


}
#endif
