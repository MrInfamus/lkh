#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "CharCanvas.h"


#pragma once

typedef struct town {
	int name;
	double x, y;
	int weight;
} town;

#define errortown maketown(-1, -1, -1, -1);

town maketown(int name, double x, double y, int weight)
{
	town t;
	t.name = name;
	t.x = x;
	t.y = y;
	t.weight = weight;
	return t;
}

void printtown(const town t)
{
	printf("%d %lf %lf %d\n", t.name, t.x, t.y, t.weight);
}

int sumweights(int counttown, const town *t)
{
	int rsum = 0;
	for(int i = 0; i < counttown; i++)
	{
		rsum += t[i].weight;
	}
	return rsum;
}

typedef struct car {
	int name;
	int capacity;
} car;

car makecar(int name, int capacity)
{
	car c;
	c.name = name;
	c.capacity = capacity;
	return c;
}

void logcar(const car car, int counttown, const town *towns)
{
	printf("car[%d] move to tows[", car.name);
	for(int i = 0; i < counttown - 1; i++)
	{
		printf("%d, ", towns[i].name);
	}
	printf("%d]\n", towns[counttown-1].name);
}

town getTownByName(int name, int counttown, const town* towns)
{
	for(int i = 0; i < counttown; i++)
	{
		if(towns[i].name == name) {
			return towns[i];
		}
	}
	return errortown;
}

double getDistanceBetweenTowns(int name1, int name2)
{
	//name1 = 1, name2 = 0
	//x = 0, y = 5

	//name1 = 2, name2 = 4
	//x = 2, y = 2
	return 0.0;
}


double getDistance(const town town1, const town town2)
{
	//TODO: distanse from OSRM
	return sqrt(pow(town2.x - town1.x, 2) + pow(town2.y - town1.y, 2));
}

void printAllMap(int counttown, const town *towns)
{
	CharCanvas c;
	initCharCanvasWithSymbol(&c, 50, 50, '`');
	for(int i = 0; i < counttown; i++)
	{
		if(towns[i].weight != 0) {
			pointAtCharCanvas(&c, makeVector2d((int)(towns[i].x * 50), (int)(towns[i].y * 50)), '0' + towns[i].name);
		} else {
			pointAtCharCanvas(&c, makeVector2d((int)(towns[i].x * 50), (int)(towns[i].y * 50)), '@');
		}
	}
	printCharCanvas(&c);
	finalizeCharCanvas(&c);
}



