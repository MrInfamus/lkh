
#pragma once
// for towns
//#define countTowns 21

#define speed 60 //km/h
#define kmhToMM (speed / 60 * 1000)

// for cars
//#define maxCapacity 30
long long maxCountCar =  3;
double optimalRadius = 0.37;
//#define countFiles 1

/*
#define FILES \
	char *mfiles[] = { \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20200925_093755.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201027_214904.csv", \
		"20(20_задач)/20201028_202211.csv", \
		"20(20_задач)//20201029_201947.csv", \
		"20(20_задач)//20201105_201910.csv", \
		"20(20_задач)//20201109_190333.csv", \
		"20(20_задач)//20201110_211510.csv", \
		"20(20_задач)//20201110_212146.csv", \
		"20(20_задач)//20201117_214239.csv", \
		"20(20_задач)//20201127_184250.csv", \
		"20(20_задач)//20201128_220622.csv", \
		"20(20_задач)//20201203_215226.csv", \
		"20(20_задач)//20201204_205445.csv", \
		"20(20_задач)//20201209_152236.csv", \
		"20(20_задач)//20201214_185310.csv", \
		"20(20_задач)//20201007_185322.csv", \
		"20(20_задач)//20201023_203450.csv" \
	}*/


#define STARTTOWNS \
	town towns[] = { \
		maketown(0, 0.77, 0.24, 0), \
		maketown(1, 0.1, 0.2, 30), \
		maketown(2, 0.15, 0.35, 23), \
		maketown(3, 0.43, 0.27, 10), \
		maketown(4, 0.9, 0.13, 2), \
		maketown(5, 0.81, 0.55, 73), \
		maketown(6, 0.28, 0.61, 48), \
		maketown(7, 0.37, 0.22, 51), \
		maketown(8, 0.21, 0.69, 7), \
		maketown(9, 0.7 , 0.9 , 24), \
		maketown(10,0.13, 0.91, 62), \
		maketown(11,0.89, 0.01, 27), \
		maketown(12,0.32, 0.51, 87), \
		maketown(13,0.48, 0.47, 41) \
	}

// a[0] == 'l' && a[1] == 'j'

// for lkh
#define ALGFOR(i) i < countUpdate
//(timeUpdate < ((clock() - runtime) / CLOCKS_PER_SEC))

long long countTasks = 10000;
long long countUpdate= 100;
//#define timeUpdate 1500000
//lkh3optTw
#define LKH lkh3optTw
#define fileout "/Users/ivandruzkov/project/lkh/tmp/lkh_out.txt"
int maxCapacity = 500;
//for sa
long double tmax = 1000;
long double tmin = 0.1;

//parameters-bin
long long countTowns = 21;
#define countFilesBin 19

#define pathSavingTowns "/Users/ivandruzkov/project/lkh/bin-towns"
#define noteFile "test"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define BLACK   "\033[37;40m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[37;46m"


#define FILESbin \
	char *mfiles[] = { \
		//"/Users/ivandruzkov/Downloads/20201020_182616.csv"} \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20200925_093755.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201225_204810.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201228_230627.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20200927_100114.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20200928_114457.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20200930_163005.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201005_160200.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201008_165020.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201014_154416.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201025_141430.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201025_142105.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201101_150113.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201115_132354.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201116_232344.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201129_132858.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201205_151827.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201224_015312.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201224_020546.csv", \
		"/Users/ivandruzkov/project/LKH0/20(20_задач)/20201224_222701.csv"}
