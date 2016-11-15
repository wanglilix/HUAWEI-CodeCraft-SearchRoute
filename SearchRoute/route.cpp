#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include "DataType.h"
#include "Recursive.h"


//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
	std::vector<USHORT> result;//最终结果
	GRAPH Graph(500);//原始图,初始化为500
	PATH_TREE PathTree;//Dijkstra算法路径树
	PATH_TABLE PathTable;//匈牙利算法路径表
	NODEDEMAND NodeDemand;//{S,E,V'..}
	DIJ_VD_QUEUE Queue;//Dijkstra算法的VD优先队列，不修改队列，只push,pop
	
	//接口初始化
	InitialInterface(topo, edge_num, demand, 
		Graph, PathTree, PathTable, NodeDemand, Queue);
	
	//算法处理
	//匈牙利要用的变量
	std::vector<MatrixNode> XYLResult;
	std::vector<std::vector<MatrixNode>> Matrix;
	std::vector<MatrixNode> tmp;
	MatrixNode MN;
	PATH Path;//权 + 起 + 终 + 路
	Recursive(Graph, PathTree, PathTable, NodeDemand, Queue, XYLResult, Matrix, tmp, MN,Path, result);

	//输出结果:有路则将有向边的编号依次存入result,否则可以什么都不用做
	if (!result.empty())
	{
		for (const auto &item : result)
			record_result(item);
	}
}