#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "CharCanvas.h"
#include "distanceMatrix.h"


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

void swap(town *town1, town *town2)
{
	town m = *town1;
	*town1 = *town2;
	*town2 = m;
}

void doShuffle(int counttown, town *towns)
{
	int j, k;
	for(int i = 0; i < counttown; i++) {
		k = rand() % counttown;
		j = rand() % counttown;
		swap(&towns[j], &towns[k]);
	}
}

void printTownList(int counttown, town *towns)
{
	putchar('[');
	for(int i = 0; i < counttown; i++) 
	{
		printf("%d ", towns[i].name);
	}
	putchar(']');putchar('\n');
}

double subtourdistance(town *sub, int lenSub, halfmatrix* m)
{
	// 1 2 3 4 #4
	// 01 12 23 34 40 #5
	//printTownList(lenSub, sub);
	double r = getByTown(m, 0, sub[0].name) + getByTown(m, 0, sub[lenSub-1].name);
	//printf("@%lf %lf\n", getByTown(m, 0, sub[0].name), getByTown(m, 0, sub[lenSub-1].name));

	for(int i = 0; i < lenSub-1; i++)
	{
		//printf("@%lf\n", getByTown(m, sub[i].name, sub[i+1].name));
		r += getByTown(m, sub[i].name, sub[i+1].name);
	}
	return r;
}

void lkh2opt(town *sub, int lenSub, halfmatrix* m)
{
	town subcopy[lenSub];
	//цикл копирования sub -> subcopy
	for(int i = 0; i < lenSub; i++)
	{
		subcopy[i] = sub[i];
	}

	double best = subtourdistance(subcopy, lenSub, m), newd;
	int a, b;

	printf("Old distance: %lf\n", best);
	printf("Old list: "); printTownList(lenSub, subcopy);
	//Основной цикл lkh
	for(int i = 0; i < countUpdate; i++)
	{
		a = rand() % lenSub;
		b = rand() % lenSub;
		swap(&subcopy[a], &subcopy[b]);
		newd = subtourdistance(subcopy, lenSub, m);
		if(newd < best) {
			best = newd;
			//цикл копирования subcopy -> sub
			for(int j = 0; j < lenSub; j++)
			{
				sub[j] = subcopy[j];
			}
		}
	}
	printf("New distance: %lf\n", best);
	printf("New list: "); printTownList(lenSub, sub);
}

