#include <stdio.h>
#include <math.h>
#include "astar.h"

static int compString(void* s1,void* s2) {
	City* city1 = s1;
	City* city2 = s2;	
	return strcmp(city1->cityName,city2->cityName);
}

static int compFn(void* s1,void* s2) {
	City* neighborCity1 = s1;
	City* neighborCity2 = s2;
	double neighborCity1Fn = neighborCity1->gn + neighborCity1->hn;
	double neighborCity2Fn = neighborCity2->gn + neighborCity2->hn;
	if (neighborCity1Fn > neighborCity2Fn) {
		return 1;
    } else if (neighborCity1Fn < neighborCity2Fn) {
		return -1;
    } else {
        return 0;
    }
}

static void prString(void* s) {
	City* city = s;
	printf("City: %s\t\t%d\t%d\n",city->cityName,city->longitude,city->latitude);
	displayList(city->neighbors);
}

void setGn(List* cityList,City* startCity) {
	Node* tmp = cityList->head;
	while (tmp) {
		City* city = (City*)tmp->val;
		if (strcmp(city->cityName,startCity) == 0) {
			city->gn = 0;
        }
		else {
			city->gn = 2000;
        }
		tmp = tmp->next;	
	}
}

double calculateHn(City* currentCity,City* goalCity) {
	return (abs(currentCity->longitude - goalCity->longitude)+abs(currentCity->latitude - goalCity->latitude))/4;
}

void computeHn(List* cityList,City* currentCity,City* goalCity) {	
	Node* tmp = cityList->head;
	while (tmp) {
		City* city = (City*)tmp->val;
		if (strcmp(city->cityName,goalCity->cityName) == 0)
			city->hn = 0;
		else {
			city->hn = calculateHn(currentCity,goalCity);
        }
		tmp = tmp->next;
	}
}

status findShortestPath(List* cityList, City* startCity, City* endCity) {
	List* Open = newList(compFn,prString);
	List* Closed = newList(compString,prString);
	City* currentCity;
	City* goalCity;
	int cityFound = 0;
	Node* tmp = cityList->head;
	while (tmp) {
		City* city = (City*)tmp->val;		
		if (strcmp(city->cityName,startCity) == 0) {
			currentCity = city;
			cityFound = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (cityFound == 0) {
		return ERRABSENT;
    }
	tmp = cityList->head;
	while (tmp) {
		City* city = (City*)tmp->val;		
		if (strcmp(city->cityName,endCity) == 0) {
			goalCity = city;
			break;
		}
		tmp = tmp->next;
	}
	addList(Open,currentCity);
	tmp = cityList->head;
	while (tmp) {
		City* city = tmp->val;
		computeHn(cityList,city,goalCity);
		tmp = tmp->next;	
	}
	setGn(cityList,startCity);
	if (Open->nelts == 0) {
		return ERRABSENT;
    }
	while (Open->nelts != 0) {
		City* visitedCity;
		remFromListAt(Open,0,(void**)&visitedCity);
		currentCity = visitedCity;
		addList(Closed,currentCity);
		if (strcmp(currentCity->cityName,goalCity->cityName) == 0) {
			displayPath(currentCity);
			return OK;
		}
		Node* tmp = currentCity->neighbors->head;
		while (tmp) {
			Neighbor* neighbor = (Neighbor*)tmp->val;
			City* city = neighbor->neighborCity;
			int newGn = currentCity->gn + neighbor->distance;
			if ((isInList(Open,city) == (Node*)1) && (newGn > city->gn)) {
				tmp = tmp->next;								
				continue;
			} else {
				remFromList(Open,city);
			}
			if ((isInList(Closed,city) == (Node*)1) && (newGn > city->gn)) {
				tmp = tmp->next;								
				continue;
			} else {
				remFromList(Closed,city);
			}
			addList(Open,city);
			city->gn = newGn;
			city->prevCity = currentCity;
			tmp = tmp->next;
		}
	}
	return ERRABSENT;
}
