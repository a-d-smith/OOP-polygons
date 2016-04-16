#include <iostream>
#include "polygon.h"

using namespace std;
using namespace polygons;

int main(){
	cout.precision(2);
	isoTriangle<double> isoT(0, 0, 3);
	isoT.listVertices();
	cout << "Centre " << isoT.centre() << endl;
	cout << "Normal " << isoT.normal() << endl;
	isoT.rotateCentre(PI/2);
	isoT.listVertices();
	cout << "Centre " << isoT.centre() << endl;
	cout << "Normal " << isoT.normal() << endl;
  return 0;
}
