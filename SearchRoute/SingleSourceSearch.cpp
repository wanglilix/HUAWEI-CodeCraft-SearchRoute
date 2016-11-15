#include "InitialSingleSourceSearch.h"
#include "Dijkstra.h"
#include "SingleSourceSearch.h"

void SingleSourceSearch(GRAPH& Graph, //ͼ
						PATH_TREE& PathTree,//DJ�㷨·����
						std::vector<PATH>& PathTableLine,//·�����ӦԴ�ڵ��������
						NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
						DIJ_VD_QUEUE& Queue,    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
						USHORT SourceID         //��Դ�����ڵ�ID
						)
{
	GRAPH CpyGraph(Graph);
	//std::copy(Graph.begin(),Graph.end(),CpyGraph.begin());//�ģ�memorycopy  ��ͼ�ṹ��ʵ�ε�ͼΪ����ͼ
	PATH_TREE CpyPathTree(PathTree);//�ģ�memorycopy    ��·������ʵ�ε���Ϊ����
	UINT AlreadyFind(0), NowFind(0), NeedFind(NodeDemand.size()-1); //��Ѱ����  �� ��Ѱ���� �� ҪѰ����

	InitialSingleSourceSearch(CpyGraph, CpyPathTree, PathTableLine, NodeDemand, Queue, SourceID, AlreadyFind);

	Dijkstra(CpyGraph, CpyPathTree, PathTableLine, NodeDemand, Queue, SourceID, AlreadyFind, NowFind, NeedFind);
}