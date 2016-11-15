#include "SearchAllPath.h"
#include "InitialSearchAllPath.h"
#include "SingleSourceSearch.h"

#include <algorithm>
void SearchAllPath(GRAPH& Graph, //图
					PATH_TREE& PathTree,//DJ算法路径树
					PATH_TABLE& PathTable,//路径表
					NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
					DIJ_VD_QUEUE& Queue    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
					)
{
	InitialSearchAllPath(Graph, PathTree, PathTable, NodeDemand, Queue);
	
	short TableLine(0);//路径表行数

	std::for_each(NodeDemand.begin(), NodeDemand.end(), 
			[&](const USHORT& source){//隐式引用捕获 + 每一次的出发点：source const

										if (source != *(NodeDemand.begin() + 1))//若当前出发点不是终点
										{
											TableLine = (std::find(NodeDemand.cbegin(), NodeDemand.cend(), source) - NodeDemand.cbegin())-1;
											TableLine = TableLine< 0 ? 0 : TableLine; //	计算当前source对应的路径表行数
											SingleSourceSearch(Graph, PathTree, PathTable[TableLine], NodeDemand, Queue, source);
										}
									});
//可替代程序
// 	for (int i = 0; i < NodeDemand.size(); ++i)
// 	{
// 		if (i != 1)//若当前出发点不是终点
// 			SingleSourceSearch(Graph, PathTree, PathTable[NodeDemand[i]], NodeDemand, Queue, NodeDemand[i]);
// 	}

}