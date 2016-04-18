#include <iostream>
#include "manager.h"
#include "polygon.h"

using namespace std;
using namespace polygons;

int main(){
  // Set up preferences for cout
	cout.precision(2);
  cout << fixed;

  // Initiate an intance of the manager
  manager<double> m;
	/*
  m.add(new square<double>(0, 0, 4), "base");

  m.add(new square<double>(0, 0, 4), "side1");
	m.get("side1")->rotate(0,0,0, 1,0,0, PI/2);
	m.get("side1")->translate(0, 2, 2);

  m.add(new square<double>(0, 0, 4), "side2");
	m.get("side2")->rotate(0,0,0, 1,0,0, -PI/2);
	m.get("side2")->translate(0, -2, 2);

  m.add(new square<double>(0, 0, 4), "side3");
	m.get("side3")->rotate(0,0,0, 0,1,0, PI/2);
	m.get("side3")->translate(2, 0, 2);

  m.add(new square<double>(0, 0, 4), "side4");
	m.get("side4")->rotate(0,0,0, 0,1,0, -PI/2);
	m.get("side4")->translate(-2, 0, 2);

  m.add(new square<double>(0, 0, 4), "top");
	m.get("top")->translate(0, 0, 4);
	*/

	m.add(new isoTriangle<double>(0,0,70), "Rhiannon");
	m.add(new rectangle<double>(1,2,12,45), "Rhiannon2");
	m.get("Rhiannon2")->rotate(2,2,2,4,3,2, PI/2);
	m.get("Rhiannon2")->translate(0,100,89);
  m.listAll();

  m.display("testDisplay");


  return 0;
}
