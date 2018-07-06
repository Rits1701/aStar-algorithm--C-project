#include <stdio.h>
#include <string.h>
#include "map.h"

static int compString(void* s1,void* s2) {
	City* city1 = s1;
	City* city2 = s2;	
	return strcmp(city1->cityName,city2->cityName);
}

static void prString(void* s) {
	City* city = s;
	printf("City: %s\t\t%d\t%d\n",city->cityName,city->longitude,city->latitude);
	displayList(city->neighbors);
}

static void prString2(void* s) {
	Neighbor* neighbor = s;
	printf("Neighbor: %s\n",neighbor->neighborCity->cityName);
	printf("Distance: %d\n",neighbor->distance);
}

status parseMap(char* fileName,List* cityList) {
	char first[20],cityName[20],neighborName[20];
	int second,third,cityLong,cityLat,neighborDist,cityFound;
	City* currentCity;
	FILE *fp = fopen(fileName,"r");
	if (fp == NULL) {
		return ERROPEN;
    }
	while (!feof(fp)) {	
		int nWords = fscanf(fp,"%s%d%d",first,&second,&third);
		if (nWords == 3) {
			strcpy(cityName,first);
			cityLong = second;
			cityLat = third;
			Node* tmp = cityList->head;
			cityFound = 0;
			while (tmp) {				
				City* city = (City*)tmp->val;
				if (strcmp(city->cityName,cityName) == 0) {
					city->longitude = cityLong;
					city->latitude = cityLat;
					city->neighbors = newList(compString,prString2);
					currentCity = city;
					cityFound = 1;
					break;
				}
				tmp = tmp->next;
			}
			if (cityFound == 0) {
				City* city = (City*)malloc(sizeof(City));
				if (city == NULL) {
					return ERRALLOC;
                }
				strcpy(city->cityName,cityName);
				city->longitude = cityLong;
				city->latitude = cityLat;
				city->neighbors = newList(compString,prString2);
				addList(cityList,city);
				currentCity = city;		
			}
		} else if (nWords == 2) {
			Neighbor* neighbor = (Neighbor*)malloc(sizeof(Neighbor));
			if (neighbor == NULL) {
				return ERRALLOC;
            }
			neighbor->neighborCity = NULL;
			strcpy(neighborName,first);
			neighborDist = second;		
			Node* tmp = cityList->head;
			cityFound = 0;
			while (tmp) {
				City* city = (City*)tmp->val;
				if (strcmp(city->cityName,neighborName) == 0) {
					neighbor->neighborCity = city;
					neighbor->distance = neighborDist;
					addList(currentCity->neighbors,neighbor);					
					cityFound = 1;			
					break;
				}
				tmp = tmp->next;
			}
			if (cityFound == 0) {
				City* city = (City*)malloc(sizeof(City));
				if (city == NULL) {
					return ERRALLOC;
                }
				strcpy(city->cityName,neighborName);			
				addList(cityList,city);
				neighbor->neighborCity = city;
				neighbor->distance = neighborDist;
				addList(currentCity->neighbors,neighbor);
			}			
		} else {
			continue;
        }
	}
	fclose(fp);
	return OK;
}
