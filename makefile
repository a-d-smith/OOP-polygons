all: polygons

polygons: demonstration.o
	g++ -std=c++11 demonstration.o -o polygons

demonstration.o: demonstration.cpp
	g++ -std=c++11 -c demonstration.cpp

clean:
	rm *o polygons
