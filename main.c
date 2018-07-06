#include <stdio.h>
#include "map.h"

static int compCity(void* s1,void* s2) {
	City* city1 = s1;
	City* city2 = s2;
	return 0;
}

static void prString(void* s) {
	City* city = s;
	printf("City: %s\n",city->cityName);
}

void displayPath(City* city) {
	List* pathList = newList(compCity,prString);
	while (city != NULL) {
		addList(pathList,city);
		city = city->prevCity;
	}
	printf("\n");
	Node* tmp = pathList->head;
	while (tmp) {
		City* city = tmp->val;
		printf("->%s",city->cityName);
		tmp = tmp->next;
	}
	printf("\n");
	free(pathList);
}

void freeAll(List* cityList) {
	Node* tmp1 = cityList->head;
	while (tmp1) {
		City* city = (City*)tmp1->val;
		Node* tmp2 = city->neighbors->head;
		while (tmp2) {
			Neighbor* neighbor = (Neighbor*)tmp2->val;
			if (neighbor != NULL) {
				free(neighbor);
            }
			tmp2 = tmp2->next;
		}
		if (city != NULL) {
			free(city->neighbors);
			free(city);
		}
		tmp1 = tmp1->next;
	}
	free(cityList);
}

int main(int argc,char* argv[]) {
	if (argc != 3) {
		printf("\nIncorrect Usage\n\nSyntax: ./ProgramName StartCity GoalCity\n\nExample: ./astar Rennes Nice\n\n");
		return 1;
	}
	char* startCity = argv[1];
	char* endCity = argv[2];
	List* cityList = newList(compCity,prString);
	if (parseMap("FRANCE.MAP",cityList) == OK) {
		printf("\nMap parsed successfully\n");
    }
	else {
		printf("\nError while parsing map, Please try again\n\n");
		return 1;
	}
	if (findShortestPath(cityList,startCity,endCity) == OK) {
		printf("\nShortest path calculation successful\n\n");
    }
	else {
		printf("\nInvalid city, Please try again\n\n");
		return 1;
	}
	freeAll(cityList);
	return 0;
}
