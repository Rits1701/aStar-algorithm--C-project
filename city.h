#ifndef _CITY_H
#define _CITY_H

#include "list.h"

typedef struct Neighbor Neighbor;

typedef struct City {
	char cityName[20];
	int longitude;
	int latitude;
	List* neighbors;
	struct City* prevCity;
	double gn;
	double hn;
} City;

#endif // _CITY_H
