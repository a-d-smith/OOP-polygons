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

		// Asks the user for a fileName
		string getFilename();

		// Takes a list of characters and asks the user to input one. The function keeps asking
		// until a listed character is given, this is then returned. The function displays the
		// message msg.
    template <class U> char getOption(initializer_list<U> p_chars, string p_msg);
	public:
		// Default constructor
    app() : m_using(false){};

		// Parametrised constructor
		app(manager<T> p_man) : m_man(p_man), m_using(false) {};

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
	T X, Y, Z, L1, L2, theta, X2, Y2, Z2;
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
			if (m_man.N() == 0){
				cout << "There are no polygons to modify!" << endl;
			}
			else{
				name = this->getExistingName();
				ans2 = this->getOption({'t', 'r', 's'}, ""
															 "What do you want to do to the polygon?   \n"
				                       "  [t] Translate it                       \n"
				                       "  [r] Rotate it                          \n"
				                       "  [s] Scale it                           \n");
				switch (ans2){
					case 't':
						// Translate it
						X = this->getNumber(false, "Please enter the translate in x:");
						Y = this->getNumber(false, "Please enter the translate in y:");
						Z = this->getNumber(false, "Please enter the translate in z:");
						m_man.get(name)->translate(X, Y, Z);
						break;
					case 'r':
						// Rotate it
						ans3 = this->getOption({'n', 'x', 'y', 'z', 'a'}, ""
						    									 "How do you wish to rotate it?            \n"
				                           "  [n] About the normal from its centre   \n"
				                           "  [x] About the x-axis                   \n"
				                           "  [y] About the y-axis                   \n"
				                           "  [z] About the z-axis                   \n"
				                           "  [a] About an arbitrary axis            \n");
						switch (ans3){
							case 'n':
								// Normal axis through centre
								theta = this->getNumber(false, "Please enter the angle you wish to rotate through (deg):");
								theta *= PI/180;
								m_man.get(name)->rotateCentre(theta);
								break;
							case 'x':
								// x-axis
								theta = this->getNumber(false, "Please enter the angle you wish to rotate through (deg):");
								theta *= PI/180;
								m_man.get(name)->rotate(0, 0, 0, 1, 0, 0, theta);
								break;
							case 'y':
								// y-axis
								theta = this->getNumber(false, "Please enter the angle you wish to rotate through (deg):");
								theta *= PI/180;
								m_man.get(name)->rotate(0, 0, 0, 0, 1, 0, theta);
								break;
							case 'z':
								// z-axis
								theta = this->getNumber(false, "Please enter the angle you wish to rotate through (deg):");
								theta *= PI/180;
								m_man.get(name)->rotate(0, 0, 0, 0, 0, 1, theta);
								break;
							case 'a':
								// aribtrary axis
								X  = this->getNumber(false, "Please enter the x-position of the origin of rotation:");
								Y  = this->getNumber(false, "Please enter the y-position of the origin of rotation:");
								Z  = this->getNumber(false, "Please enter the z-position of the origin of rotation:");
								X2 = this->getNumber(false, "Please enter the x-position of another point along the rotation axis:");
								Y2 = this->getNumber(false, "Please enter the y-position of another point along the rotation axis:");
								Z2 = this->getNumber(false, "Please enter the z-position of another point along the rotation axis:");
								theta = this->getNumber(false, "Please enter the angle you wish to rotate through (deg):");
								theta *= PI/180;
								m_man.get(name)->rotate(X, Y, Z, X2, Y2, Z2, theta);
								break;
						}
						break;
					case 's':
						// Scale it
						ans3 = this->getOption({'n', 'o'}, ""
						    									 "How do you wish to scale it?             \n"
				                           "  [n] About its centre                   \n"
				                           "  [o] About the origin                   \n");
						switch (ans3){
							case 'n':
								// About its centre
								break;
							case 'o':
								// About the origin
								break;
						}
						break;
				}
			}
				
			break;
		case 'r':
			// Remove an existing polygon
			name = this->getExistingName();		
			ans2 = this->getOption({'y', 'n'}, ""
			                       "Do you wish remove this polygon to the scene? \n"
														 "  [y] Yes, remove it forever                  \n"
			                       "  [n] No, I want to keep it                   \n");
			if (ans2 == 'y'){
				m_man.remove(name);
				cout << "Polygon \"" << name << "\" has been removed" << endl;
			}

			break;
		case 'd':
			// Display the current scene
			
			// Check to see if the scence has been named yet
			if (m_fileName.length() == 0){
				cout << "Before you can display the scene you must name it!" << endl;
				m_fileName = this->getFilename();
			}
			else{
				cout << "The scene is currently named \"" << m_fileName << "\"." << endl;
				ans2 = this->getOption({'y', 'n'}, ""
			                       "Do you wish change this name? \n"
														 "  [y] Yes, I want to display with a new name   \n"
			                       "  [n] No, I want to update the current display \n");
				if (ans2 == 'y'){
					m_fileName = this->getFilename();
				}
			}
			cout << endl;
			if (m_man.N() != 0){
				m_man.display(m_fileName);
			}
			else{
				cout << "There are no polygons to display!" << endl;
			}

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
	bool good;

	cout << "Please enter a unique name for this polygon" << endl;
	cout << "  name = ";

	cin.clear();
	good = (cin >> nam);

	while (!good || m_man.exists(nam)){
		cout << endl;
		cout << "  Sorry that name is taken. The list of current names is" << endl;
		m_man.listAll();
		cout << "  name = ";
		cin.clear();
		good = (cin >> nam);
		cin.ignore(100000, '\n');
	}
	cin.ignore(100000, '\n');
	cout << endl;
	return nam;
}

template <class T> string app<T>::getExistingName(){
	string nam;
	bool good;

	cout << "Please enter an existing polygon name" << endl;
	cout << "  name = ";
	cin.clear();
	good = (cin >> nam);

	while (!good || !m_man.exists(nam)){
		cout << endl;
		cout << "  Sorry that does not currently exits. The list of current names is" << endl;
		m_man.listAll();
		cout << "  name = ";
		cin.clear();
		cin.ignore(100000, '\n');
		good = (cin >> nam);
	}
	cin.ignore(100000, '\n');
	cout << endl;

	return nam;
}

template <class T> T app<T>::getNumber(bool p_positiveDefinite, string p_msg){
	T num;

	cout << p_msg << endl;
	cout << "  value = ";
	
	T minVal;

	if (p_positiveDefinite){
		minVal = 0;
	}
	else{
		minVal = -9999999999;
	}

	bool good;
	
	good = (cin >> num);
	while (!good || num <= minVal){
		cin.clear();
		cin.ignore(10000, '\n');	
	
		cout << endl;
		if (p_positiveDefinite){
			cout << "  Sorry you must enter a number >= 0" << endl;
		}
		else{
			cout << "  Sorry you must enter a number" << endl;
		}
		cout << "  value = ";
		good = (cin >> num);
	}

	cin.ignore(100000, '\n');

	cout << endl;

	return num;
}

template <class T> string app<T>::getFilename(){
	string nam;

	cout << "Please name the scene" << endl;
	cout << "  name = ";

	cin >> nam;
	cin.ignore(100000, '\n');

	cin.clear();

	return nam;
}

template <class T> template <class U> char app<T>::getOption(initializer_list<U> p_chars, string p_msg){
	vector<char> charList(p_chars);
	char ans;
	bool good;
	stringstream ss;
	string input;
	bool validAns{false};

	cout << p_msg << endl;
	cout << "  response = ";

	cin.clear();
	ss.clear();
	ss.str("");
	getline(cin, input);
	ss << input.substr(0,1);
	good = (ss >> ans);

	while (!validAns || !good){
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

			cin.clear();
			ss.clear();
			ss.str("");
			getline(cin, input);
			ss << input.substr(0,1);
			good = (ss >> ans);
		}
	}
	cout << endl;
	cin.clear();

	return ans;
}


}
#endif
