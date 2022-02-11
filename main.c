#include <stdio.h>

#include "parameters.h"
#include "logistic.h"
#include "distanceMatrix.h"
#include "generate-bin-tables.c"

int main()
{
	srand(time(NULL));
	//STARTTOWNS;
	FILES;


	halfmatrix m;
	//inithalfmatrix(&m, countTowns-1);


	FILE *out = fopen(fileout, "w");
	if(out == NULL) {
		exit(-1);
	}

	town towns[countTowns];
	
	for(int i = 0; i < countFiles; i++)
	{
		readOneTownByBinary(towns, &m, "test", 0);
		/*
		read_file(mfiles[i], towns, countTowns);

		printTownList(countTowns, towns);
		printtown(getTownByName(0, countTowns, towns));
		printtown(getTownByName(1, countTowns, towns));
		//printAllMap(countTowns, towns);

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
		*/
		printtownmatrix(&m);
		//printf("%lf\n", getByTown(&m, 2, 11));
		town sub[countTowns - 1]; // города
		for(int i = 1; i < countTowns; i++)
		{
			sub[i-1] = getTownByName(i, countTowns, towns);
		}


		for(int i = 0; i < countTowns - 1; i++) {
			printf("%d ", sub[i].name);
		} putchar('\n');


		town temp[countTowns];// координаты |
		temp[0] = towns[0];
		
		double distanceInTourBest = -1.0, distanceInTourNew = 0.0, noneOptimalDistance = 0.0;
		printf("%d\n", getTownByName(16, countTowns - 1, sub).weight);
		double runtime = clock();
		for(int i = 0; i < countTasks;i++)
		{

			doShuffle(countTowns - 1, sub);
			printTownList(countTowns - 1, sub);

			int cap = 0, l = 0;
			for(int g = 0; g < countTowns - 1; g++) {
				
				if(cap + sub[g].weight <= maxCapacity) {
					temp[l] = sub[g];
					l++;
					cap += sub[g].weight;
				} else {
					printTownList(l, temp);
					if(l >= 3) {
						LKH(temp, l, &m);
					} else {

					}
					cap = 0;
					l = 0;
					g--;
				}
			}
			printTownList(l, temp);
			if(l >= 3) {
				LKH(temp, l, &m);
			} else {

			}


			//int cap, k = 0, p = 0;
			/*
			while(k < countTowns - 1) {
				//printf("?%d\n", sub[k].weight);
				for(cap = sub[k].weight; cap < maxCapacity && k < countTowns - 1;k++, cap += sub[k].weight) {
					//printf("??%d\n", cap);
					temp[k-p] = sub[k];
				}
				//printTownList(k - p, temp);
				noneOptimalDistance += subtourdistance(temp, k-p, &m);

				if(k-p > 2) {

					distanceInTourNew += LKH(temp, k-p, &m);
					//TODO choose best variant tour.
				} else {
					distanceInTourNew += subtourdistance(temp, k-p, &m);
				}
			
				p = k;
			}

			if(distanceInTourBest == -1.0) {
				fprintf(out, "%lf\t%lf\n", noneOptimalDistance, 0.0);
				distanceInTourBest = noneOptimalDistance;
			}

			if(distanceInTourNew < distanceInTourBest) {
				distanceInTourBest = distanceInTourNew;
			    fprintf(out, "%lf\t%lf\n", distanceInTourBest, (clock() - runtime) / CLOCKS_PER_SEC);
			}
			distanceInTourNew = 0.0;

		}
		fprintf(out, "%lf\t%lf\n", distanceInTourBest, (clock() - runtime) / CLOCKS_PER_SEC);
		fputc('\n', out);
		*/
		}
	}
	
	fclose(out);
	finalizehalfmatrix(&m);
	return 0;
}