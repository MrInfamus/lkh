#include "parameters-bin.h"
#include "generate-bin-lib.h"

int main() {
	FILESbin;

	for(int i = 0; i < countFilesBin; i++) {
		parseOneTown(mfiles[i], noteFile, i);
		printf("startus: %d/%d\n", i+1, countFilesBin);
	}

	//parseOneTown("/Users/ivandruzkov/project/LKH0/20(20_задач)/20200925_093755.csv", "test", 0);
	//halfmatrix m;
	//town towns[21];
	//readOneTownByBinary(towns, &m, noteFile, 0);
	//printtownmatrix(&m);
	//printTownList(countTowns, towns);
	return 0;
}