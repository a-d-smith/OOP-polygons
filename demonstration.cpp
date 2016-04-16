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

  m.add(new square<double>(0.5, 0.5, 1), "mySquare");
  m.add(new isoTriangle<double>(-0.5, -0.5, 0.5), "myTriangle");
  m.add(new pentagon<double>(1, 1, 2), "fat ass");

  m.listAll();
  m.display("testDisplay");

  return 0;
}
