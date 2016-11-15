#include "InitialSingleSourceSearch.h"
#include "Dijkstra.h"
#include "SingleSourceSearch.h"

void SingleSourceSearch(GRAPH& Graph, //图
						PATH_TREE& PathTree,//DJ算法路径树
						std::vector<PATH>& PathTableLine,//路径表对应源节点的行引用
						NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
						DIJ_VD_QUEUE& Queue,    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
						USHORT SourceID         //单源出发节点ID
						)
{
	GRAPH CpyGraph(Graph);
	//std::copy(Graph.begin(),Graph.end(),CpyGraph.begin());//改：memorycopy  新图结构，实参的图为备份图
	PATH_TREE CpyPathTree(PathTree);//改：memorycopy    新路径树，实参的树为备份
	UINT AlreadyFind(0), NowFind(0), NeedFind(NodeDemand.size()-1); //已寻点数  ， 现寻点数 ， 要寻点数

	InitialSingleSourceSearch(CpyGraph, CpyPathTree, PathTableLine, NodeDemand, Queue, SourceID, AlreadyFind);

	Dijkstra(CpyGraph, CpyPathTree, PathTableLine, NodeDemand, Queue, SourceID, AlreadyFind, NowFind, NeedFind);
}