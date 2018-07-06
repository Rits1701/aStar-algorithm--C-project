#ifndef _ASTAR_H
#define _ASTAR_H

#include "map.h"

/**
	Set the g(n) for all cities except start city
*/
void setGn(List* cityList,City* currentCity);

/**
	Calculate the h(n) for all cities using distance formula
*/
double calculateHn(City* currentCity,City* goalCity);

/**
	Set the h(n) for all cities by calling the calculateHn function
*/
void computeHn(List* cityList,City* currentCity,City* goalCity);

/**
	Find the shortest path from the start city to the end city
*/
status findShortestPath(List* cityList,City* startCity,City* endCity);

#endif //_ASTAR_H
