#include <stdio.h>
#include <stdlib.h>
#include "parameters-bin.h"
#include "../distanceMatrix.h"
#include "../logistic.h"

void parseOneTown(const char pathFile[], const char newFileName[], int index)
{

	halfmatrix m;
	inithalfmatrix(&m, countTowns-1);
	town towns[countTowns];
	


	char pathTown[70], pathTable[70];

	snprintf(pathTown, 70, "%s/town%d/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	snprintf(pathTable, 70, "%s/table%d/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	printf("%s\n", pathTown);
	FILE* outtown = fopen(pathTown, "wb");
	if(outtown == NULL) {
		exit(-1);
	}
	FILE* outtable = fopen(pathTable, "wb");
	if(outtable == NULL) {
		fclose(outtown);
		exit(-1);
	}


	for(int i = 0; i < countFilesBin; i++)
	{
		read_file(pathFile, towns, countTowns);

		printTownList(countTowns, towns);
		//printtown(getTownByName(0, countTowns, towns));
		//printtown(getTownByName(1, countTowns, towns));
		//printAllMap(countTowns, towns);

		int maxCapacity = -1;
		
		for(int c = 0; c < countTowns; c++) {
			if(towns[c].weight > maxCapacity) {
				maxCapacity = towns[c].weight;
			}
		}
		maxCapacity *= 4;

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
		printtownmatrix(&m);
	}

	fwrite(&m.width, sizeof(int), 1, outtable);
	for(int i = 0; i < m.width; i++) {
		for(int j = 0; j < m.width - i; j++) {
			fwrite(&m.data[i][j], sizeof(double), 1, outtable);
		}
	}
	int tmp = countTowns;
	fwrite(&tmp, sizeof(int), 1, outtown);
	for(int i = 0; i < countTowns; i++) {
		fwrite(&towns[i], sizeof(town), 1, outtable);
	}

	//fwrite(&m, sizeof(struct halfmatrix), 1, outtable);
	//fwrite(towns, sizeof(struct town*), 1, outtown);
	finalizehalfmatrix(&m);
	fclose(outtown);
	fclose(outtable);

}

void readOneTownByBinary(town *towns, halfmatrix *m, const char newFileName[], int index) {
	char pathTown[70], pathTable[70];

	snprintf(pathTown, 70, "%s/town%d/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	snprintf(pathTable, 70, "%s/table%d/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	printf("%s\n", pathTown);
	FILE* intown = fopen(pathTown, "r");
	if(intown == NULL) {
		exit(-1);
	}
	FILE* intable = fopen(pathTable, "r");
	if(intable == NULL) {
		fclose(intown);
		exit(-1);
	}

	//fread(towns, sizeof(struct town*), 1, intown);
	//fread(m, sizeof(struct halfmatrix), 1, intable);
	fread(&m->width, sizeof(int), 1, intable);
	inithalfmatrix(m, m->width);
	for(int i = 0; i < m->width; i++) {
		for(int j = 0; j < m->width - i; j++) {
			//printf("%d %d\n", i, j);
			fread(&m->data[i][j], sizeof(double), 1, intable);
		}
	}

	int tmp;
	fread(&tmp, sizeof(int), 1, intown);
	for(int i = 0; i < tmp; i++) {
		fread(&towns[i], sizeof(town), 1, intable);
	}
}



