#include <iostream>
#include "polygon.h"
#include "manager.h"
#include "app.h"

using namespace std;
using namespace polygons;

int main(){
  // Set up preferences for cout
	cout.precision(2);
  cout << fixed;

  // Initiate an intance of the manager
  manager<double> m;
	
  m.add(new rectangle<double>(0, 0, 6, 4), "base");

  m.add(new rectangle<double>(0, 0, 6, 4), "side1");
	m.get("side1")->rotate(0,0,0, 1,0,0, PI/2);
	m.get("side1")->translate(0, 2, 2);

  m.add(new rectangle<double>(0, 0, 6, 4), "side2");
	m.get("side2")->rotate(0,0,0, 1,0,0, -PI/2);
	m.get("side2")->translate(0, -2, 2);

  m.add(new square<double>(0, 0, 4), "side3");
	m.get("side3")->rotate(0,0,0, 0,1,0, PI/2);
	m.get("side3")->translate(3, 0, 2);

  m.add(new square<double>(0, 0, 4), "side4");
	m.get("side4")->rotate(0,0,0, 0,1,0, -PI/2);
	m.get("side4")->translate(-3, 0, 2);

  m.add(new rectangle<double>(0, 0, 7, 5), "roofBase");
	m.get("roofBase")->translate(0, 0, 4);

	m.add(new equiTriangle<double>(0, 0, 5), "roofSide");
	m.get("roofSide")->rotate(0,0,0, 0,1,0, PI/2);
	m.get("roofSide")->translate(3.5, 0, 4 + pow(2, 0.5));

	m.add(new equiTriangle<double>(0, 0, 5), "roofSide2");
	m.get("roofSide2")->rotate(0,0,0, 0,1,0, PI/2);
	m.get("roofSide2")->translate(-3.5, 0, 4 + pow(2, 0.5));

  m.add(new rectangle<double>(0, 0, 7, 5), "roofTop");
	m.get("roofTop")->translate(0, 0, 4);
	m.get("roofTop")->rotate(0, -2.5, 4, 1, -2.5, 4, PI/3);

  m.add(new rectangle<double>(0, 0, 7, 5), "roofTop2");
	m.get("roofTop2")->translate(0, 0, 4);
	m.get("roofTop2")->rotate(0, +2.5, 4, 1, +2.5, 4, -PI/3);

  m.display("houseDisplay");
	
	app<double> a;
	a.start();

  return 0;
}
