#include "InitialSearchAllPath.h"
void InitialSearchAllPath(
	GRAPH& Graph, //图
	PATH_TREE& PathTree,//DJ算法路径树
	PATH_TABLE& PathTable,//路径表
	NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
	DIJ_VD_QUEUE& Queue    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
	)
{
	//总起始点S: 初始标记为树
}