#include <stdio.h>

#include "parameters.h"
#include "logistic.h"

int main()
{
	STARTTOWNS;
	//printf("%d\n", sumweights(2, towns) / maxCapacity);

	//printtown(towns[0]);
	//logcar(makecar(1, maxCapacity), 2, towns);
	//printf("%d\n", inRadiusTown(towns[0], towns[1], 2));

	printAllMap(countTowns, towns);

	
	
	
	/*
	for(int i = 0; i < countTowns; i++)
	{
		for(int j = i; j < countTowns; j++)
		{

		}
	}*/

	return 0;
}