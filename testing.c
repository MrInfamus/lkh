#include "logistic.h"


int main() 
{
	//int c = 11;
	//STARTTOWNS;
	
	//0[1 2]3 4 5 6[7 8 9 10]

	//0[9 10]3 4 5 6[7 8 1 2]
	//0[* *]9 10 3 4[5 6 1 2]
	//printTownList(c, towns);
	//[0 1 2 3 4 5]6 7[8 9]10

	town t[3] = {
		maketown(0, 1, 1, 1),
		maketown(1, 1, 1, 1),
		maketown(2, 1, 1, 1)
	};
	//[0, 1, 2]
	reverseTown(t, 1, 2);
	printTownList(3, t);

	//0[1 2 3 4 5]6[7]8 9 10
	//0[1 6 7 * *]*[*]8 9 10
	//0[7 6 1 * *]*[*]8 9 10
	//0{7}6{1 2 3 4 5}8 9 10
	//int a = moveElems(towns, 1, 5, 7, 7);
	//0{7}6{1 2 3 4 5}8 9 10
	//0{7 8 9 10}3 4 5 6{1 2}
	//0[1]2 3 4[5 6 7]8 9 10
	//0{5 6 7}2 3 4{1}8 9 10
	//printTownList(c, towns);
	//printf("%d\n", a);
	return 0;
}