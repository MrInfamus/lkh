#include <stdio.h>
#include <stdlib.h>
#include "../parameters.h"
#include "../distanceMatrix.h"
#include "../logistic.h"

void parseOneTown(const char pathFile[], const char newFileName[], int index)
{

	halfmatrix m;
	inithalfmatrix(&m, countTowns-1);
	town towns[countTowns];
	


	char pathTown[70], pathTable[70];

	snprintf(pathTown, 70, "%s/town%lld/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	snprintf(pathTable, 70, "%s/table%lld/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	//printf("%s\n", pathTown);
	FILE* outtown = fopen(pathTown, "wb");
	if(outtown == NULL) {
		printf("Error writing file: %s", pathTown);
		exit(-1);
	}
	FILE* outtable = fopen(pathTable, "wb");
	if(outtable == NULL) {
		fclose(outtown);
		printf("Error writing file: %s", pathTable);
		exit(-1);
	}

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
	

	fwrite(&m.width, sizeof(int), 1, outtable);
	for(int i = 0; i < m.width; i++) {
		for(int j = 0; j < m.width - i; j++) {
			fwrite(&m.data[i][j], sizeof(double), 1, outtable);
		}
	}
	int tmp = countTowns;
	fwrite(&tmp, sizeof(int), 1, outtown);
	for(int i = 0; i < countTowns; i++) {
		fwrite(&towns[i], sizeof(struct town), 1, outtown);
	}

	//fwrite(&m, sizeof(struct halfmatrix), 1, outtable);
	//fwrite(towns, sizeof(struct town*), 1, outtown);
	finalizehalfmatrix(&m);
	fclose(outtown);
	fclose(outtable);

}

void parseOneTownNoIndex(const char pathFile[], const char newFileName[], int tcountTowns, int maxCapacity)
{

	halfmatrix m;
	inithalfmatrix(&m, tcountTowns-1);
	town towns[tcountTowns];
	
	char pathTown[2000], pathTable[2000];

	snprintf(pathTown, 2000, "%s-town.bin", newFileName);
	snprintf(pathTable, 2000, "%s-table.bin", newFileName);
	//printf("%s\n", pathTown);
	FILE* outtown = fopen(pathTown, "wb");
	if(outtown == NULL) {
		printf("Error writing file: %s", pathTown);
		exit(-1);
	}
	FILE* outtable = fopen(pathTable, "wb");
	if(outtable == NULL) {
		fclose(outtown);
		printf("Error writing file: %s", pathTable);
		exit(-1);
	}

	read_file(pathFile, towns, tcountTowns);

	printTownList(tcountTowns, towns);

	for(int i = 0; i < tcountTowns; i++)
	{
		for(int j = 0; j < tcountTowns-i-1; j++)
		{
			//printf("t%d %d t%d %lf\n", i, j, m.width-j, getDistance(towns[i], towns[m.width-j]));
			//m.data[i][j] = getDistance(towns[j], towns[i]);
			if(getTownByName(i, tcountTowns, towns).weight + getTownByName(m.width-j, tcountTowns, towns).weight > maxCapacity) {
				pointAthalfmatrix(&m, i, j, -1.0);
				continue;
			}

			pointAthalfmatrix(&m, i, j, getDistance(getTownByName(i, tcountTowns, towns), getTownByName(m.width-j, tcountTowns, towns)));
		}
	}
	printtownmatrix(&m);
	

	fwrite(&m.width, sizeof(int), 1, outtable);
	for(int i = 0; i < m.width; i++) {
		for(int j = 0; j < m.width - i; j++) {
			fwrite(&m.data[i][j], sizeof(double), 1, outtable);
		}
	}
	int tmp = tcountTowns;
	fwrite(&tmp, sizeof(int), 1, outtown);
	for(int i = 0; i < tcountTowns; i++) {
		fwrite(&towns[i], sizeof(struct town), 1, outtown);
	}

	//fwrite(&m, sizeof(struct halfmatrix), 1, outtable);
	//fwrite(towns, sizeof(struct town*), 1, outtown);
	finalizehalfmatrix(&m);
	fclose(outtown);
	fclose(outtable);
}



void readOneTownByBinary(town *towns, halfmatrix *m, const char newFileName[], int index) {
	char pathTown[70], pathTable[70];

	snprintf(pathTown, 70, "%s/town%lld/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	snprintf(pathTable, 70, "%s/table%lld/%s%d.bin", pathSavingTowns, countTowns - 1, newFileName, index);
	printf("%s\n", pathTown);
	FILE* intown = fopen(pathTown, "r");
	if(intown == NULL) {
		printf("Error writing file: %s", pathTown);
		exit(-1);
	}
	FILE* intable = fopen(pathTable, "r");
	if(intable == NULL) {
		fclose(intown);
		printf("Error writing file: %s", pathTable);
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
		fread(&towns[i], sizeof(struct town), 1, intown);
	}
}

void readOneTownByBinaryNoIndex(town *towns, halfmatrix *m, const char newFileName[]) {
	char pathTown[70], pathTable[70];

	snprintf(pathTown, 70, "%s-town.bin", newFileName);
	snprintf(pathTable, 70, "%s-table.bin", newFileName);
	printf("%s\n", pathTown);
	FILE* intown = fopen(pathTown, "r");
	if(intown == NULL) {
		printf("Error writing file: %s", pathTown);
		exit(-1);
	}
	FILE* intable = fopen(pathTable, "r");
	if(intable == NULL) {
		fclose(intown);
		printf("Error writing file: %s", pathTable);
		exit(-1);
	}

	//fread(towns, sizeof(struct town*), 1, intown);
	//fread(m, sizeof(struct halfmatrix), 1, intable);
	printf("After open file\n");
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
		fread(&towns[i], sizeof(struct town), 1, intown);
	}

	fclose(intown);
	fclose(intable);
}


