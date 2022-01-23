#include <stdio.h>

#include "parameters.h"
#include "logistic.h"
#include "distanceMatrix.h"

int main()
{
	STARTTOWNS;
	//printf("%d\n", sumweights(2, towns) / maxCapacity);

	//printtown(towns[0]);
	//logcar(makecar(1, maxCapacity), 2, towns);
	//printf("%d\n", inRadiusTown(towns[0], towns[1], 2));

	printAllMap(countTowns, towns);

	
	halfmatrix m;
	inithalfmatrix(&m, countTowns-1);
	//fillhalfmatrix(&m, -1);
	//printhalfmatrix(&m);
	
	for(int i = 0; i < countTowns; i++)
	{
		for(int j = 0; j < countTowns-i-1; j++)
		{
			//printf("t%d %d t%d %lf\n", i, j, m.width-j, getDistance(towns[i], towns[m.width-j]));
			//m.data[i][j] = getDistance(towns[j], towns[i]);
			if(getTownByName(i, countTowns, towns).weight + getTownByName(m.width-j, countTowns, towns).weight > maxCapacity) {
				pointAthalfmatrix(&m, i, j, -1.0);
				continue;
			}
			pointAthalfmatrix(&m, i, j, getDistance(getTownByName(i, countTowns, towns), getTownByName(m.width-j, countTowns, towns)));
		}
	}
	//printhalfmatrix(&m);
	printtownmatrix(&m);
	printf("%lf\n", getByTown(&m, 2, 11));
	//town subturs[countTowns-1][2*countTowns - 1];

	/*
	for(int i = 0; i < countTowns; i++) {
		for(int j = i; i < countTowns; j++) {

		}
	}*/
	

	finalizehalfmatrix(&m);
	return 0;
}