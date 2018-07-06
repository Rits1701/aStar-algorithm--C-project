#ifndef _NEIGHBOR_H
#define _NEIGHBOR_H

typedef struct City City;

typedef struct Neighbor {
	City* neighborCity;
	int distance;
} Neighbor;

#endif // _NEIGHBOR_H
