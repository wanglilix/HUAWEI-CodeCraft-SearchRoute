#include <string>  
#include <stdio.h>
#include <algorithm>

#include "DataType.h"
#include "SearchAllPath.h"
#include "DJX.h"

void Recursive(GRAPH& Graph, //ͼ
	PATH_TREE& PathTree,//DJ�㷨·����
	PATH_TABLE& PathTable,//·����
	NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
	DIJ_VD_QUEUE& Queue,    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
	std::vector<MatrixNode>& Result,//���������
	std::vector<std::vector<MatrixNode>>& Matrix,//������ԭʼ����
	std::vector<MatrixNode>& tmp,//������������
	MatrixNode& MN, //����������ڵ�
	PATH& Path,		//������
	std::vector<USHORT>& PathResult
	)
{
	//�ҵĺ���
	SearchAllPath(Graph, PathTree, PathTable, NodeDemand, Queue);

	UINT i, j;//ѭ������
	///////////////////////////////////////////////////////////////////////////////////
	Matrix.clear();
	for ( i = 0; i < PathTable.size(); ++i)//�����ȡ
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
	//�Խ����㷨
	Result.clear();
	DJX(Matrix, Result);

	if (Result.empty())//�޽�
	{
		PathResult.clear();
		Result.clear();
		return;
	}
	//��ȡ���������
	MatrixNode  Tmp = *std::find_if(Result.begin(), Result.end(), [&](const MatrixNode& Nod){ return Nod.X == 0; });//��ʱ����㣺��ʼ���
	UINT VD=0;
	Path.clear();
	Path.push_back(0);//Ȩ�س�ʼ0
	for (i = 0; i < Matrix.size(); ++i)
	{
		Path.push_back(*(PathTable[Tmp.X][Tmp.Y].begin() + 1));//����������
		Path.insert(Path.end(), PathTable[Tmp.X][Tmp.Y].begin()+3, PathTable[Tmp.X][Tmp.Y].end());//·
		//�յ�Ϊ��һ�����
		VD += Tmp.RealValue;//�ۼ�Ȩ
		if (Tmp.RealValue == MAX)
		{
			Path[0] = MAX;
		}
		Tmp = *std::find_if(Result.begin(), Result.end(), [&](const MatrixNode& Nod){ return Nod.X == Tmp.Y; });//����һ����
	}
	Path.push_back(NodeDemand[1]);//����յ�
	Path[0] = (Path[0] == MAX) ? MAX : VD;


	//����ű�ɱ����: Ȩ+���+A B C +�յ� -> �ߵ����
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


	//���Ϸ���:�ظ���
	PATH PathCheck(Path);
	std::sort(PathCheck.begin()+1,PathCheck.end());
	auto itera = std::adjacent_find(PathCheck.begin() + 1, PathCheck.end());
	if (PathCheck.end()==itera)//û���ظ��ڵ�
	{
		return;
	}
	else//���ظ��ڵ�
	{
		std::vector<PATH> tmpPath;
		USHORT NewPod;
		while (PathCheck.end() != itera)//add all new point
		{
			NewPod = *itera;
			NodeDemand.push_back(NewPod); //�����ؾ��ڵ�
			Graph[NewPod][0].isDominators = true;//����������ıؾ�����

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

	


	//std::cout << "���" << std::endl;
// 	std::for_each(Result.begin(), Result.end(), [&](const MatrixNode& Nod){   PathTree; });
}