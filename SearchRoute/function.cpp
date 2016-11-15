#include "DataType.h"

#include <string>
#include <algorithm>
#include <cctype>
#include <list>

void InitialInterface(
	char *topo[5000], int edge_num, char *demand,
	GRAPH& Graph, //图
	PATH_TREE& PathTree,//DJ算法路径树
	PATH_TABLE& PathTable,//路径表
	NODEDEMAND& NodeDemand, //{S,E,V'..}起点+终点+必经点：新增必经点位于最后一位
	DIJ_VD_QUEUE& Queue    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
	)
{
	NODE_UNIT Node;//结点单元
	std::vector<NODE_UNIT> vNode;//相邻结点容器
	USHORT MaxSouNodeID(0);//记录最大的含出发边的结点ID
	USHORT MaxNodeID(0);//记录最大的结点ID

	std::string strLine(""), strValue("");
	std::vector<int> vValue;
	
	//根据demand构建NodeDemand
	strLine = static_cast<std::string>(demand);
	strLine += ";";
	for (auto iter = strLine.cbegin(); iter != strLine.cend(); ++iter)
	{
		if (isdigit(*iter))
		{
			strValue += *iter;
		}
		else
		{
			if (!strValue.empty())
			{
				NodeDemand.push_back(static_cast<USHORT>(std::stoi(strValue)));
				strValue.erase();
			}
		}
	}
	
	//根据topo构建Graph
	for (size_t i = 0; i < static_cast<size_t>(edge_num); ++i)
	{
		strLine = topo[i];
		strLine += ";";
		//		//'，'换成" "
		// 		std::cout << strLine << std::endl;
		// 		while (string::npos != (pos = strLine.find(',')))
		// 		{
		// 			strValue += strLine.at(++pos);
		// 
		// 			strLine.replace(pos++, 1, " ");
		// 		}
		strValue.clear();//清空strValue
		vValue.clear();//清空vValue
		for (auto iter = std::find(strLine.cbegin(), strLine.cend(), ',') + 1; iter != strLine.cend(); ++iter)
		{
			if (isdigit(*iter))
			{
				strValue += *iter;
			}
			else
			{
				if (!strValue.empty())
				{
					vValue.push_back(std::stoi(strValue));
					strValue.erase();
				}
			}
		}

		vNode = Graph.at(static_cast<size_t>(vValue.front()));//根据SourceID取出graphORI的相邻结点容器vNode
															  //如果该vNode为空则需要先设置起始结点
		if (vNode.empty())
		{	//根据demand初始化Graph中起始点的结点单元
			Node.ID = static_cast<USHORT>(vValue.front());//起始结点的DestinationID是本身ID
			Node.edge = 0xffff;//起始结点到自身的有向边不存在
			Node.cost = MAX_COST;//起始结点的权重设为最大值
			Node.isDominators = std::find(NodeDemand.cbegin(), NodeDemand.cend(), Node.ID) != NodeDemand.cend();//该起始结点是否是必经节点
			Node.isInPathTree = false;
			vNode.push_back(Node);
		}
		//设置起始结点的相邻结点
		Node.ID = vValue.at(1);
		Node.edge = static_cast<USHORT>(i);//有向边编号
		Node.cost = vValue.back();
		Node.isDominators = false;
		Node.isInPathTree = false;
		Node.vd = MAX;
		vNode.push_back(Node);
		//更新graphORI中SourceID的相邻结点容器vNode
		Graph.at(static_cast<size_t>(vNode.front().ID)) = vNode;
		//更新最大的含出发边的结点ID
		if (MaxSouNodeID < static_cast<USHORT>(vValue.front()))
			MaxSouNodeID = static_cast<USHORT>(vValue.front());
		//更新最大的含到达边的结点ID，暂存maxNodeID
		if (MaxNodeID < Node.ID)
			MaxNodeID = Node.ID;
	}
	//更新最大的结点ID
	MaxNodeID = std::max(MaxNodeID, MaxSouNodeID);
	//处理E
// 	Node.ID = NodeDemand.at(1);
// 	Node.cost = MAX_COST;
// 	Node.edge = 0xffff;
// 	Node.isDominators = true;
// 	Node.isInPathTree = false;
// 	Graph.at(Node.ID).push_back(Node);

	//处理多个终点（即只有到达没有出发边）的情况
	for (USHORT i = 0; i < MaxNodeID; ++i)
	{
		if (Graph[i].empty())
		{
			Node.ID = i;
			Node.cost = MAX_COST;
			Node.edge = 0xffff;
			Node.isDominators= std::find(NodeDemand.cbegin(), NodeDemand.cend(), Node.ID) != NodeDemand.cend();//该起始结点是否是必经节点
			Node.isInPathTree = false;
			Node.vd = MAX;
			Graph[i].push_back(Node);
		}
	}

	//标记S的node位于路径树
	Graph.at(NodeDemand.front()).front().isInPathTree = true;
	//整理graph，删去多余的vNode
	Graph.erase(Graph.begin() + MaxSouNodeID + 1, Graph.end());
	Graph.shrink_to_fit();

	//考虑不使用:以下memcpy一个二维vector方法失败，有资料表明不能用一个vector去memcpy另一个vector
	//需要先将graphTMP初始化graphORI.size()个元素
	// 	GRAPH graphTMP(graphORI.size());
	// 	for (size_t sz = 0; sz < graphORI.size(); ++sz)
	// 	{
	// 		//然后将graphTMP[sz]设置为graphORI[sz].size()个元素
	// 		graphORI[sz].resize(graphORI[sz].size());
	// 		memcpy(&graphTMP[sz], &graphORI[sz], sizeof(NODE_UNIT)*graphORI[sz].size());
	// 	}
	//使用泛型算法copy成功
	//需要先将graphTMP初始化graphORI.size()个元素
	//GRAPH graphTMP(graphORI.size());
	//std::copy(graphORI.cbegin(), graphORI.cend(), graphTMP.begin());
	//test:结果显示，每个node都完成了拷贝
	//std::cout << "&graphTMP.front().front():" << &graphTMP.front().front() << std::endl;
	//std::cout << "&graphORI.front().front():" << &graphORI.front().front() << std::endl;
	//
	//建立graphTMP，直接用graphORI来初始化graphTMP
	//GRAPH graphTMP(Graph);
	//test graphTMP
	// 	for (const auto& item : graphTMP)
	// 	{
	// 		std::cout << "SourceID:";
	// 		if (!item.empty())
	// 		{
	// 			for (auto& it : item)
	// 			{
	// 				std::cout << it.ID << " ";
	// 			}
	// 		}	
	// 		std::cout << std::endl;
	// 	}

	//建立Dijkstra路径树
	PathTree.reserve(MaxNodeID);
	for (USHORT i = 0; i <= MaxNodeID; ++i)
	{
		PathTree.push_back(i);//下标为当前节点序号，存储为父节点序号: 初始化为本节点序号
	}

	//构建PathTable
	std::vector<PATH> vPath;
	vPath.reserve(NodeDemand.size() - 1);
	std::list<USHORT> lSou(NodeDemand.cbegin(), NodeDemand.cend());
	lSou.erase(++lSou.begin());
	std::list<USHORT> lDes(NodeDemand.cbegin() + 1, NodeDemand.cend());
	for (auto iterS = lSou.cbegin(); iterS != lSou.cend(); ++iterS)
	{
		vPath.clear();
		for (auto iterD = lDes.cbegin(); iterD != lDes.cend(); ++iterD)
		{
			vPath.push_back(PATH{ MAX, *iterS, *iterD });
		}
		PathTable.push_back(vPath);
	}
}