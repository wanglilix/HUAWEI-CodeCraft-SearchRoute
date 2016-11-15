#include <string>  
#include <stdio.h>
#include <algorithm>

#include "DataType.h"
#include "SearchAllPath.h"
#include "DJX.h"

void Recursive(GRAPH& Graph, //图
	PATH_TREE& PathTree,//DJ算法路径树
	PATH_TABLE& PathTable,//路径表
	NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
	DIJ_VD_QUEUE& Queue,    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
	std::vector<MatrixNode>& Result,//匈牙利结果
	std::vector<std::vector<MatrixNode>>& Matrix,//匈牙利原始矩阵
	std::vector<MatrixNode>& tmp,//匈牙利矩阵行
	MatrixNode& MN, //匈牙利矩阵节点
	PATH& Path,		//保存结果
	std::vector<USHORT>& PathResult
	)
{
	//我的函数
	SearchAllPath(Graph, PathTree, PathTable, NodeDemand, Queue);

	UINT i, j;//循环变量
	///////////////////////////////////////////////////////////////////////////////////
	Matrix.clear();
	for ( i = 0; i < PathTable.size(); ++i)//矩阵获取
	{
		tmp.clear();
		for ( j = 0; j < PathTable[0].size(); ++j)
		{
			MN.RealValue = MN.value = PathTable[i][j][0];
			MN.X = i;
			MN.Y = j;
			tmp.push_back(MN);
		}
		Matrix.push_back(tmp);
	}
	//////////////////////////////////////////////////////////////////////////////////
	//对角线算法
	Result.clear();
	DJX(Matrix, Result);

	if (Result.empty())//无解
	{
		PathResult.clear();
		Result.clear();
		return;
	}
	//提取匈牙利结果
	MatrixNode  Tmp = *std::find_if(Result.begin(), Result.end(), [&](const MatrixNode& Nod){ return Nod.X == 0; });//临时矩阵点：初始起点
	UINT VD=0;
	Path.clear();
	Path.push_back(0);//权重初始0
	for (i = 0; i < Matrix.size(); ++i)
	{
		Path.push_back(*(PathTable[Tmp.X][Tmp.Y].begin() + 1));//各个出发点
		Path.insert(Path.end(), PathTable[Tmp.X][Tmp.Y].begin()+3, PathTable[Tmp.X][Tmp.Y].end());//路
		//终点为下一个起点
		VD += Tmp.RealValue;//累加权
		if (Tmp.RealValue == MAX)
		{
			Path[0] = MAX;
		}
		Tmp = *std::find_if(Result.begin(), Result.end(), [&](const MatrixNode& Nod){ return Nod.X == Tmp.Y; });//找下一个点
	}
	Path.push_back(NodeDemand[1]);//添加终点
	Path[0] = (Path[0] == MAX) ? MAX : VD;


	//点序号变成边序号: 权+起点+A B C +终点 -> 边的序号
	UINT Now;
	UINT Next;
	PathResult.clear();
	for (auto Iterator = Path.begin(); Iterator != (Path.end() - 2); ++Iterator)
	{
		Now = *(Iterator + 1);
		Next = *(Iterator + 2);
		for (i = 0; i < Graph[Now].size(); ++i)
		{
			if (Next == (Graph[Now][i].ID))
			{
				PathResult.push_back(Graph[Now][i].edge);
			}
		}
	}


	//检查合法性:重复点
	PATH PathCheck(Path);
	std::sort(PathCheck.begin()+1,PathCheck.end());
	auto itera = std::adjacent_find(PathCheck.begin() + 1, PathCheck.end());
	if (PathCheck.end()==itera)//没有重复节点
	{
		return;
	}
	else//有重复节点
	{
		std::vector<PATH> tmpPath;
		USHORT NewPod;
		while (PathCheck.end() != itera)//add all new point
		{
			NewPod = *itera;
			NodeDemand.push_back(NewPod); //新增必经节点
			Graph[NewPod][0].isDominators = true;//更新新增点的必经属性

			for (UINT j = 0; j < NodeDemand.size() - 1; ++j)
			{
				tmpPath.push_back(PATH{ MAX, static_cast<UINT>(NodeDemand.size() - 2), j });
			}
			PathTable.push_back(tmpPath);

			for (i = 0; i < NodeDemand.size() - 2; ++i)
			{

				PathTable[i].push_back(PATH{ MAX, i, static_cast<UINT>(NodeDemand.size() - 2) });
			}
			while (itera != PathCheck.end() && *itera == NewPod )
			{
				++itera;
			}
			itera = std::adjacent_find(itera, PathCheck.end());
		}

		Recursive(Graph, PathTree, PathTable, NodeDemand, Queue, Result, Matrix, tmp, MN, Path, PathResult);
	}

	


	//std::cout << "结果" << std::endl;
// 	std::for_each(Result.begin(), Result.end(), [&](const MatrixNode& Nod){   PathTree; });
}