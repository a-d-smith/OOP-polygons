#ifndef APP_H
#define APP_H

#include "polygon.h"
#include "manager.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

namespace polygons{

// ------------------------------------------------------------------------------------------
// A class to control user input and interface with the manager
// ------------------------------------------------------------------------------------------

/*!
 * This is a cool comment about the app class
 */
template <class T>
class app{
  protected:
		// A manager to hold the polygons
		manager<T> m_man;

		// A string for the display file name
		string m_fileName;

		// Boolean to indicate if the app is in use
		bool m_using;

		// The main function that loops to allow user input
		void loop();

		// Asks the user for a polygon name that either does or doesn't exist in the manager
		string getNewName();		
		string getExistingName();

		// Asks the user for a number 
		T getNumber(bool p_positiveDefinite, string p_msg);

		// Takes a list of characters and asks the user to input one. The function keeps asking
		// until a listed character is given, this is then returned. The function displays the
		// message msg.
    template <class U> char getOption(initializer_list<U> p_chars, string p_msg);
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
		void end();

};

template <class T> void app<T>::start(){
	m_using = true;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "                                                                      " << endl;
	cout << "               ####  ####  #    #   #  ####  ####  #   #              " << endl;
 	cout << "               #  #  #  #  #     # #   #     #  #  ##  #              " << endl;
 	cout << "               ####  #  #  #      #    # ##  #  #  # # #              " << endl;
 	cout << "               #     #  #  #      #    #  #  #  #  #  ##              " << endl;
 	cout << "               #     ####  ####   #    ####  ####  #   #              " << endl;
	cout << "                                                                      " << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "                                                                      " << endl;
	cout << " Final project for the course 'Object Oriented Programming in C++'    " << endl;
	cout << "                                                                      " << endl;	
	cout << " Author: Andrew Smith                                                 " << endl;	
	cout << "         The University of Manchester                                 " << endl;	
	cout << "         April 2016                                                   " << endl;	
	cout << "                                                                      " << endl;	
	cout << "----------------------------------------------------------------------" << endl;
	cout << "                                                                      " << endl;
	this->loop();
}

template <class T> void app<T>::loop(){
	char ans1, ans2, ans3;
	T X, Y, L1, L2;
	string name;

	ans1 = this->getOption({'l', 'a', 'm', 'r', 'd', 'q'}, ""
												 "Please choose an instruction:           \n"
	                       "  [l] List all of the current polygons  \n"
	                       "  [a] Add a new polygon                 \n"
	                       "  [m] Modify an existing polygon        \n"
	                       "  [r] Remove an existing polygon        \n"
	                       "  [d] Display the current scene         \n"
	                       "  [q] Quit the application              \n");
	switch (ans1){
		case 'l':
			// List all of the current polygons
			m_man.listAll();
			break;
		case 'a':
			// Add an new polygon
			name = this->getNewName();		
			ans2 = this->getOption({'e', 'i', 's', 'r', 'p', 'h'}, ""
														 "What type of polygon do you wish to add? \n"
			                       "  [e] Equilateral Triangle               \n"
			                       "  [i] Isosceles Triangle                 \n"
			                       "  [s] Square                             \n"
			                       "  [r] Rectangle                          \n"
			                       "  [p] Pentagon                           \n"
			                       "  [h] Hexagon                            \n");

			X    = this->getNumber(false, "Please enter the x-position of the centre of the polygon:");
			Y    = this->getNumber(false, "Please enter the y-position of the centre of the polygon:");

			if (ans2 == 'i'){
				L1 = this->getNumber(true, "Please enter the base width:");
				L2 = this->getNumber(true, "Please enter length of the other two sides:");
			}
			else if (ans2 == 'r'){
				L1 = this->getNumber(true, "Please enter the width:");
				L2 = this->getNumber(true, "Please enter the height:");
			}
			else{
				L1 = this->getNumber(true, "Please enter the side length");
			}

			polygon<T> *poly;	

			switch (ans2){
				case 'e':
					// Equilateral Triangle
					poly = new equiTriangle<T>(X, Y, L1);
					break;
				case 'i':
					// Isosceles Triangle
					poly = new isoTriangle<T>(X, Y, L1, L2);
					break;
				case 's':
					// Square
					poly = new square<T>(X, Y, L1);
					break;
				case 'r':
					// Rectangle
					poly = new rectangle<T>(X, Y, L1, L2);
					break;
				case 'p':
					// Pentagon
					poly = new pentagon<T>(X, Y, L1);
					break;
				case 'h':
					// Hexagon
					poly = new hexagon<T>(X, Y, L1);
					break;
			}

			cout << "This is the polygon you have defined:" << endl;
			cout << "  Name   = " << name << endl;
			cout << "  Centre = (" << X << ", " << Y << ")" << endl; 
			poly->listVertices();			

			ans3 = this->getOption({'y', 'n'}, ""
			                       "Do you wish to add this polygon to the scene? \n"
														 "  [y] Yes, add it                             \n"
			                       "  [n] No, discard it                          \n");
			if (ans3 == 'y'){
				m_man.add(poly, name);
				cout << "Polygon \"" << name << "\" has been added" << endl;
			}
			else{
				cout << "Polygon \"" << name << "\" has been discarded" << endl;
			}

			break;
		case 'm':
			// Modify an existing polygon
			break;
		case 'r':
			// Remove an existing polygon
			break;
		case 'd':
			// Display the current scene
			break;
		case 'q':
			// Quit the application
			ans2 = this->getOption({'y', 'n'}, ""
			                       "Are you sure you wish to quit? \n"
														 "  [y] Yes, please quit         \n"
			                       "  [n] No, keep using the app   \n");
			if (ans2 == 'y'){
				this->end();
			}
			break;
		default:
			exit(1);
	}

	// Keep calling yourself unless the using flag is set to false
	if (m_using){
		cout << "                                                                      " << endl;	
		cout << "----------------------------------------------------------------------" << endl;
		cout << "                                                                      " << endl;
		this->loop();
	}
}

template <class T> void app<T>::end(){
	m_using = false;
}

template <class T> string app<T>::getNewName(){
	string nam;

	cout << "Please enter a unique name for this polygon" << endl;
	cout << "  name = ";
	getline(cin, nam);

	while (m_man.exists(nam)){
		cout << endl;
		cout << "  Sorry that name is taken. The list of current names is" << endl;
		m_man.listAll();
		cout << "  name = ";
		getline(cin, nam);
	}
	cout << endl;
	return nam;
}

template <class T> string app<T>::getExistingName(){
	string nam;

	cout << "Please enter an existing polygon name" << endl;
	cout << "  name = ";
	getline(cin, nam);

	while (!m_man.exists(nam)){
		cout << endl;
		cout << "  Sorry that does not currently exits. The list of current names is" << endl;
		m_man.listAll();
		cout << "  name = ";
		getline(cin, nam);
	}
	cout << endl;

	return nam;
}

template <class T> T app<T>::getNumber(bool p_positiveDefinite, string p_msg){
	string input;
	stringstream ss;
	T num;

	cout << p_msg << endl;
	cout << "  value = ";
	getline(cin, input);
	ss << input;
	ss >> num;
	ss.clear();	

	if (p_positiveDefinite){
		while (num <= 0){
			cout << endl;
			cout << "  Sorry you must enter a number >= 0" << endl;
			cout << "  value = ";
			getline(cin, input);
			ss << input;
			ss >> num;
			ss.clear();	
		}
	}
	cout << endl;

	return num;
}

template <class T> template <class U> char app<T>::getOption(initializer_list<U> p_chars, string p_msg){
	vector<char> charList(p_chars);
	char ans;
	string input;
	stringstream ss;

	cout << p_msg << endl;
	cout << "  response = ";
	getline(cin, input);
	ss << input.substr(0, 1);
	ss >> ans;	
	ss.clear();
 
	bool validAns{false};

	while (!validAns){
		for (char aChar : charList){
			if (aChar == ans){
				validAns = true;
			}
		}
		if (!validAns){
			cout << endl;
			cout << "  Please enter one of the following characters:" << endl << "  ";
			for (char aChar : charList){
				cout << "[" << aChar << "]  ";
			}
			cout << endl << endl;
			cout << "  response = ";
			getline(cin, input);
			ss << input.substr(0, 1);
			ss >> ans;	
			ss.clear();
		}
	}
	cout << endl;

	return ans;
}


}
#endif
