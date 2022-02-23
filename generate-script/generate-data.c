#include "parameters-bin.h"
#include "generate-bin-lib.h"

int main() {
	FILESbin;

	halfmatrix m;
	town towns[countTowns];

	for(int i = 0; i < countFilesBin; i++) {
		printf("%sstartus: %d/%d%s\n", YELLOW, i+1, countFilesBin, RESET);
		readOneTownByBinary(towns, &m, noteFile, i);
		printtownmatrix(&m);
		printTownList(countTowns, towns);
		//parseOneTown(mfiles[i], noteFile, i);
	}

	//parseOneTown("/Users/ivandruzkov/project/LKH0/20(20_задач)/20200925_093755.csv", "test", 0);
	//halfmatrix m;
	//town towns[21];
	//readOneTownByBinary(towns, &m, noteFile, 0);
	//printtownmatrix(&m);
	//printTownList(countTowns, towns);
	//printtown(towns[1]);
	return 0;
}