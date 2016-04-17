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

  m.add(new square<double>(0, 0, 1), "base");

  m.add(new square<double>(0, 0, 1), "side1");
  m.get("side1")->listVertices();

  m.get("side1")->rotate(0, 0, 0, 1, 0, 0, PI);
  m.get("side1")->listVertices();

  m.get("side1")->translate(0.5, 0.5, 0);
  m.get("side1")->listVertices();

  m.listAll();

  m.display("testDisplay");


  return 0;
}
