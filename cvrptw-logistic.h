#include <stdio.h>
#include "logistic.h"


typedef struct timeWindowTown {
	town t;
	double mTimeStart, mTimeEnd;
	double mTimeService;
} twtown;

twtown maketwtown(town t, double mTimeStart, double mTimeEnd, double mTimeService) {
	twtown tw;
	tw.t = t;
	tw.mTimeService = mTimeService;
	tw.mTimeStart = mTimeStart;
	tw.mTimeEnd = mTimeEnd;
	return tw;
}

void printtwtown(const twtown t) {
	printtown(t.t);
	printf("%lf-%lf s:%lf\n", t.mTimeStart, t.mTimeEnd, t.mTimeService);
}

int read_file_tw(const char* name_file, twtown *towns, int counttowns)
{
    FILE* in;
    in = fopen(name_file, "r");
    if(in == NULL)
    {
        //printf("11 Error %d \n", errno);
        return -1;
    }
    int symbol;
    for(int i = 0; (symbol = fgetc(in)) != EOF && symbol != '\n'; i++);


    double x, y, cap, st;
	int hst, mst, het, met;
    for(int i = counttowns-1; i >= 0 ; i--)
    {
        fscanf(in, "%lf\t%lf\t%lf\t%d:%d-%d:%d\t%lf\n", &x, &y, &cap, &hst, &mst, &het, &met, &st);
        towns[i] = maketwtown(maketown(i, x, y, cap), hst * 60 + mst, het * 60 + met, st);
    }
    //fscanf(in, "%lf\t%lf\t\n", &depot[0], &depot[1]);
    fclose(in);
    return 0;
}