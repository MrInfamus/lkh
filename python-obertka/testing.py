import cvrp
#import helloworld
#help(cvrp)
#print(helloworld.parseOneTownPy("/Users/ivandruzkov/project/LKH0/20(20_задач)/20200925_093755.csv", "ttt/test0", 21, 60))
#cvrp.parseOneTwTownPy("/Users/ivandruzkov/project/lkh/20200925_093755.csv", "ttt/test0", 21)
cvrp.modelMetaHeuristic("cvrptw_lkh", "ttt/test0", 21, 500)

#cvrp.createBinFile(
	#"/Users/ivandruzkov/project/LKH0/20(20_задач)/20200925_093755_dist.csv", "/test", 21, 60)
