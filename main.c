#include <stdio.h>

#include "parameters.h"
#include "generate-script/generate-bin-lib.h"
#include "generate-script/parameters-bin.h"

#include "logistic.h"
#include "distanceMatrix.h"


int main()
{
	srand(time(NULL));
	//STARTTOWNS;
	//FILES;


	halfmatrix m;
	//inithalfmatrix(&m, countTowns-1);


	FILE *out = fopen(fileout, "w");
	if(out == NULL) {
		exit(-1);
	}

	town towns[countTowns];
	for(int i = 0; i < countFilesBin; i++)
	{
		readOneTownByBinary(towns, &m, "test", i);
		printf("twn: ");
		for(int i = 0; i < countTowns; i++) {
			printf("%d ", towns[i].name);
		} putchar('\n');
		printtown(towns[1]);		
		//[0, 1, 2, 3, 4, 5, 6]
		//Вариант 1
		//[1, 2, 6, 0, 0, 0, 0]
		//[1, 2, 6]
		//Вариант 2
		//[-2, 1, 2, -2, -2, -2, 6]
		for(int c = 0; c < countTowns; c++) {
			if(towns[c].weight > maxCapacity) {
				towns[c] = zerotown;
				printf("c: %d\n", c);
			}
		}
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
		town *sub = (town*)malloc((countTowns - 1) * sizeof(town)); // города
		
		int w = 0; town t;
		for(int i = 1; i < countTowns; i++)
		{
			t = getTownByName(i, countTowns, towns);
			// отсечение лишний городов путем, поиска их в массиве.(по нашей реализации, в случае если город не был найден возвращался errortown)
			if(t.name == -1){
				printf("Error town: %d\n", t.name);
				continue;
			}
			sub[w] = t;
			w++;
		}
		int newCountTowns = w;
		sub = realloc(sub, newCountTowns * sizeof(town));

		printf("sub: ");
		for(int i = 0; i < newCountTowns; i++) {
			printf("%d ", sub[i].name);
		} putchar('\n');
		printtown(sub[1]);

		town temp[countTowns];// координаты |
		temp[0] = towns[0];
		
		double distanceInTourBest = -1.0, distanceInTourNew = 0.0, noneOptimalDistance = 0.0;
		printf("%d\n", getTownByName(16, countTowns - 1, sub).weight);
		double runtime = clock();
		for(int i = 0; i < countTasks;i++)
		{

			doShuffle(newCountTowns, sub);
			//printTownList(newCountTowns, sub);

			int cap = 0, l = 0;
			for(int g = 0; g < newCountTowns; g++) {
				
				if(cap + sub[g].weight <= maxCapacity) {
					temp[l] = sub[g];
					l++;
					cap += sub[g].weight;
				} else {
					noneOptimalDistance += subtourdistance(temp, l, &m);
					//printTownList(l, temp);
					if(l >= 3) {
						distanceInTourNew += LKH(temp, l, &m);
					} else {
						distanceInTourNew += subtourdistance(temp, l, &m);
					}
					cap = 0;
					l = 0;
					g--;
				}
			}
			//printTownList(l, temp);
			noneOptimalDistance += subtourdistance(temp, l, &m);
			//printTownList(l, temp);
			if(l >= 3) {
				distanceInTourNew += LKH(temp, l, &m);
			} else {
				distanceInTourNew += subtourdistance(temp, l, &m);
			}


			if(distanceInTourBest == -1.0) {
				//printf("I\'m in if\n");
				fprintf(out, "%lf\t%lf\n", noneOptimalDistance, 0.0);
				distanceInTourBest = noneOptimalDistance;
			}


			if(distanceInTourNew < distanceInTourBest) {
				distanceInTourBest = distanceInTourNew;
			    fprintf(out, "%lf\t%lf\n", distanceInTourBest, (clock() - runtime) / CLOCKS_PER_SEC);
			}
			distanceInTourNew = 0.0;

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
		fprintf(out, "%lf\t%lf\n", distanceInTourBest, (clock() - runtime) / CLOCKS_PER_SEC);
		fputc('\n', out);
		free(sub);
	}
	fclose(out);
	finalizehalfmatrix(&m);
	return 0;
}