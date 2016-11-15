#include "InitialSingleSourceSearch.h"
#include <algorithm>
void InitialSingleSourceSearch(
						GRAPH&  Graph, //图
						PATH_TREE&  PathTree,//DJ算法路径树
						std::vector<PATH>& PathTableLine,//路径表对应源节点的行引用
						NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
						DIJ_VD_QUEUE& Queue,    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
						USHORT SourceID,         //单源节点ID
						UINT&  AlreadyFind      //已寻点数
						)
{
	Graph[SourceID][0].vd = 0;  //令当前出发点的Vd为0

	//清空优先队列  不用清空路径树
	DIJ_VD_QUEUE tmp;
	Queue.swap(tmp);
// 	while (!Queue.empty())
// 		Queue.pop();
	//当前出发点装入优先队列 临时父序号为它本身
 	Queue.push(DIJ_VD{ SourceID, SourceID, 0 });

	std::for_each(PathTableLine.begin(), PathTableLine.end(), 
		[&]( PATH& path){
								if ( MAX != path[0]    //路径权重非MAX
									&& 
								   ( path.cend()==std::find(path.cbegin()+3 ,path.cend(),(UINT)*(NodeDemand.crbegin())))) //路径:除去权重、出发点和终点  不包含NodeDemand最后一位节点
								{
									Graph[*(path.begin() + 2)][0].isInPathTree = true;  //表示此路径已经位于路径树
									++AlreadyFind;   //已寻点数增加
								}
								else
								{
									PATH tmp{ MAX,0,0 };
									path.swap(tmp);//若路径包含了新增必经节点，则删除路径
								}
	});


}