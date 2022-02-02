#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "CharCanvas.h"
#include "distanceMatrix.h"
#include <limits.h>


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

int read_file(const char* name_file, town *towns, int counttowns)
{
    FILE* in;
    in = fopen(name_file, "r");
    if(in == NULL)
    {
        //printf("11 Error %d \n", errno);
        return -1;
    }
    int symbol;
    for(int i = 0; (symbol = fgetc(in)) != EOF && symbol != '\n'; i++);


    double x, y, cap;
    for(int i = counttowns-1; i >= 0 ; i--)
    {
        fscanf(in, "%lf\t%lf\t%lf\n", &x, &y, &cap);
        towns[i] = maketown(i, x, y, cap);
    }
    //fscanf(in, "%lf\t%lf\t\n", &depot[0], &depot[1]);
    fclose(in);
    return 0;
}

double getDistance(const town town1, const town town2)
{
	//TODO: distanse from OSRM
	//return sqrt(pow(town2.x - town1.x, 2) + pow(town2.y - town1.y, 2));
	char path[PATH_MAX];
	char output[120];
	FILE *fp; int status;

	char *req = "curl -s 'http://router.project-osrm.org/route/v1/driving/%lf,%lf;%lf,%lf?overview=false'";
	snprintf(output, 120, req, town1.y, town1.x, town2.y, town2.x);
	//printf("%s\n", output);
	fp = popen(output, "r");
	if(fp == NULL) {
		return -2.0;
	}

	char num[12]; int trigger = 0;
	char *eptr;

	for(int c = 3; (c = fgetc(fp)) != EOF; ) {
		if(trigger <= 3 && c == 'd' && (c = fgetc(fp)) == 'i' && (c = fgetc(fp)) == 's' &&
		  (c = fgetc(fp)) == 't' && (c = fgetc(fp)) =='a' && (c = fgetc(fp)) == 'n' &&
		  (c = fgetc(fp)) == 'c' && (c = fgetc(fp)) == 'e' && (c = fgetc(fp)) == '"' &&
		  (c = fgetc(fp)) == ':') {
		  	if(trigger < 2) {
		  		trigger++;
		  	}
		  	int h = 0;
			while((c = fgetc(fp)) != ',') {
				num[h] = c;
				h++;
			}
			num[h] = '\0';
			trigger++;
		}
	}
	double result = strtod(num, &eptr);
	//printf("%lf\n", result);
	pclose(fp);	
	return result;
}

void printAllMap(int counttown, const town *towns)
{
	CharCanvas c;
	initCharCanvasWithSymbol(&c, 50, 50, '`');
	for(int i = 0; i < counttown; i++)
	{
		if(towns[i].weight != 0) {
			pointAtCharCanvas(&c, makeVector2d((int)((towns[i].x - 43) * 50), (int)((towns[i].y - 76) * 50)), '0' + towns[i].name);
		} else {
			pointAtCharCanvas(&c, makeVector2d((int)((towns[i].x - 43) * 50), (int)((towns[i].y - 76) * 50)), '@');
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

void reverseTown(town *sub, int i, int j)
{
	int s = (j + i) / 2;
	if((j + i) % 2 == 0) {
		for(int k = 0; k < (j - i + 1) / 2; k++)
		{
			swap(&sub[s - k], &sub[s+1+k]);
		}
	} else {
		for(int k = 0; k < (j - i) / 2; k++)
		{
			swap(&sub[s-1-k], &sub[s+1+k]);
		}	
	}
}

void moveEmels(town *sub, int start1, int end1, int start2, int end2)
{
	int difference = (end1 - start1 - (end2 - start2));
	if(difference > 0) {
		town *tmp = (town*)malloc(difference*sizeof(town));
		// 0 1 2 3 4 5 6 7 8 9 10
		//[0 1 2 3]4 5 6[7 8 9]10
		//tmp[difference], tmp[1]
		for(int i = 0; i < difference; i++) {
			tmp[i] = sub[end1 - difference + 1 + i];
		}


		town t;		
		for(int i = 0; i < end2 - start2 + 1; i++)
		{
			t = sub[start1 + i];
			sub[start1 + i] = sub[start2 + i];
			sub[start2 + i] = t;
		}

		for(int i = 0; i < start2 - end1 + 1; i++)
		{
			sub[end1 + 1 + i - difference] = sub[end1 + 1 + i];
		}

	} else if(difference < 0) {
		town *tmp = (town*)malloc(-difference*sizeof(town));
		for(int i = 0; i < end2-start2+1; i++) {
			tmp[i] = sub[start2 + i];
		}
		town t;		
		for(int i = 0; i < end2 - start2 + 1; i++)
		{
			t = sub[start1 + i];
			sub[start1 + i] = sub[start2 + i];
			sub[start2 + i] = t;
		}
	} else {

	}
	//free(tmp);
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
		while(a == b) {
			b = rand() % lenSub;
		}
		reverseTown(subcopy, my_min(a, b), my_max(a, b));
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

void lkh3opt(town *sub, int lenSub, halfmatrix *m)
{
	/*
	2-opt
	0: Or O  O
	1: O  Or O
	2: O  O  Or

	3-opt
	3: O  [O  O ]
	4: Or [O  O ]
	5: O  [Or O ]
	6: O  [O  Or]
	*/
	int a, b, mode;
	for(int i = 0; i < countUpdate; i++)
	{
		mode = rand() % 7;
		if(mode < 3) {
			return lkh2opt(sub, lenSub, m);
		}

		a = rand() % lenSub;
		b = rand() % lenSub;
		
		while(a==b) {
			b = rand() % lenSub;
		}


	}
}



void lkh4opt(town *sub, int lenSub, halfmatrix* m)
{
	int a, b, c;
	for(int i = 0; i < countUpdate; i++)
	{
		a = rand() % lenSub;
		b = rand() % lenSub;
		c = rand() % lenSub;
		while(a==b) {
			b = rand() % lenSub;
		}
		while(a == c || b == c) {
			c = rand() % lenSub;
		}

		//hahahhahahhaa
		//int nmin, ns, nmax = my_min(my_min(a, b), my_min(a, c)), \
		a + b + c - my_min(my_min(a, b), my_min(a, c)) - my_max(my_max(a, b), my_max(a, c)), \
		my_max(my_max(a, b), my_max(a, c));

		int nmin, ns, nmax;
		if(a > b && b > c) {
			nmin = c; ns = b; nmax = a;
		} else if(c < a && a < b) {
			//nmin, ns, nmax = c, a, b;
		} else if(a > c && c > b) {
			//nmin, ns, nmax = b, c, a;
		} else if(b < a && a < c) {
			//nmin, ns, nmax = b, a, c;
		} else if(b > c && c > a) {
			//nmin, ns, nmax = a, c, b;
		} else if(a < b && b < c) {
			//nmin, ns, nmax = a, b, c;
		}
		printf("%d, %d, %d\n", nmin, ns, nmax);


	}
}

