#include "Dijkstra.h"
#include <algorithm>
void Dijkstra(
				GRAPH& Graph, //图
				PATH_TREE& PathTree,//DJ算法路径树
				std::vector<PATH>& PathTableLine,//路径表对应源节点的行引用
				NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
				DIJ_VD_QUEUE& Queue,    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
				USHORT SourceID,         //单源节点始发ID
				UINT&  AlreadyFind,      //已寻点数
				UINT&  NowFind,			//现寻点数
				UINT&  NeedFind       //必经点数
			)
{
	if (SourceID == *(NodeDemand.begin()))//S点
		 ++NeedFind;//S点为出发点时，NeedFind要多一个
	
	DIJ_VD SmallNode;  //定义待更改地方 最小节点
	PATH TmpPath;      //定义待更改地方临时路径
	USHORT TmpID(0);     //定义待更改地方临时ID
	short TableRow(0);	//路径表列数
	UINT TmpVd(0);      //临时权重
	std::vector<UINT>::iterator TmpIterator ;//临时迭代器

	while (1)
	{
		if ((AlreadyFind + NowFind) == NeedFind || Queue.empty())//若找完所有必经点,则跳出查找循环    //若优先队列为空,则跳出查找循环
			break;

		SmallNode = Queue.top();
		Queue.pop();//取出并删除最小节点
		
		PathTree[SmallNode.curID] = SmallNode.fatID;//最小节点加入路径树
		Graph[SmallNode.curID][0].isInPathTree = true;//更新最小节点为树标志

		if (Graph[SmallNode.curID][0].isDominators)//若最小节点是必经节点
		{
			++NowFind;
			if (PathTree[SmallNode.curID] != SmallNode.curID) //若路径父节点不是本身
			{
				TmpPath.clear();//清空临时变量
				TmpID = SmallNode.curID;
				TmpPath.push_back(Graph[SmallNode.curID][0].vd);  //提取权重
				TmpPath.push_back(SmallNode.fatID);  //用临时父序号占位置，等到找到出发点直接替换
				TmpPath.push_back(SmallNode.curID);  //终点序号
				TmpIterator = TmpPath.end();
				while (PathTree[PathTree[TmpID]] != PathTree[TmpID])//当还没到出发点时
				{
					TmpID = PathTree[TmpID];
					TmpIterator = TmpPath.insert(TmpIterator, TmpID);   //提取路径
				}
				TmpPath[1] = PathTree[TmpID];

				TableRow = (std::find(NodeDemand.cbegin(), NodeDemand.cend(), SmallNode.curID) - NodeDemand.cbegin()) - 1;//	计算当前最小节点即终点 对应的路径表列数
				PathTableLine[TableRow].swap(TmpPath);//保存路径
			}
		
		}
		if (!Graph[SmallNode.curID][0].isDominators || (SmallNode.curID == SourceID))//若最小节点不是必经节点或者是当前出发点这一必经节点
		{
			std::for_each(++Graph[SmallNode.curID].begin(), Graph[SmallNode.curID].end(), 
				[&](NODE_UNIT & neighborNode){
													TmpVd = SmallNode.vd + neighborNode.cost;
													if ((!Graph[neighborNode.ID][0].isInPathTree) && (TmpVd< Graph[neighborNode.ID][0].vd)) //若邻居为非树节点且可以更新Vd
													{
														Queue.push(DIJ_VD{ neighborNode.ID, SmallNode.curID, TmpVd });//添加新的节点到优先队列
														Graph[neighborNode.ID][0].vd = std::move(TmpVd);//更新非树邻居Vd
													}
					
			});
		}

	}

}
