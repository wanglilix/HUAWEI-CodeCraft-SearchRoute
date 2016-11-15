#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include "DataType.h"
#include "Recursive.h"


//��Ҫ��ɵĹ��������
void search_route(char *topo[5000], int edge_num, char *demand)
{
	std::vector<USHORT> result;//���ս��
	GRAPH Graph(500);//ԭʼͼ,��ʼ��Ϊ500
	PATH_TREE PathTree;//Dijkstra�㷨·����
	PATH_TABLE PathTable;//�������㷨·����
	NODEDEMAND NodeDemand;//{S,E,V'..}
	DIJ_VD_QUEUE Queue;//Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
	
	//�ӿڳ�ʼ��
	InitialInterface(topo, edge_num, demand, 
		Graph, PathTree, PathTable, NodeDemand, Queue);
	
	//�㷨����
	//������Ҫ�õı���
	std::vector<MatrixNode> XYLResult;
	std::vector<std::vector<MatrixNode>> Matrix;
	std::vector<MatrixNode> tmp;
	MatrixNode MN;
	PATH Path;//Ȩ + �� + �� + ·
	Recursive(Graph, PathTree, PathTable, NodeDemand, Queue, XYLResult, Matrix, tmp, MN,Path, result);

	//������:��·������ߵı�����δ���result,�������ʲô��������
	if (!result.empty())
	{
		for (const auto &item : result)
			record_result(item);
	}
}