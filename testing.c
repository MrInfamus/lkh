#include "logistic.h"


int main() 
{
	int c = 11;
	STARTTOWNS;
	
	//0[1 2]3 4 5 6[7 8 9 10]

	//0[9 10]3 4 5 6[7 8 1 2]
	//0[* *]9 10 3 4[5 6 1 2]
	//printTownList(c, towns);
	//[0 1 2 3 4 5]6 7[8 9]10
	int a = moveElems(towns, 0, 5, 8, 9);
	//0{7 8 9 10}3 4 5 6{1 2}
	//printTownList(c, towns);
	printf("%d\n", a);
	return 0;
}