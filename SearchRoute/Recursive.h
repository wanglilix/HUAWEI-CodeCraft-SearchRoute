#include "DataType.h"
void Recursive(GRAPH& Graph, //ͼ
	PATH_TREE& PathTree,//DJ�㷨·����
	PATH_TABLE& PathTable,//·����
	NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
	DIJ_VD_QUEUE& Queue,    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
	std::vector<MatrixNode>& Result,
	std::vector<std::vector<MatrixNode>>& Matrix,
	std::vector<MatrixNode>& tmp,
	MatrixNode& MN,
	PATH& Path,
	std::vector<USHORT>& PathResult//���
	);