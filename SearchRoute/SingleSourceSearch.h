#include "DataType.h"
void SingleSourceSearch(
						GRAPH& Graph, //ͼ
						PATH_TREE& PathTree,//DJ�㷨·����
						std::vector<PATH>& PathTableLine,//·�����ӦԴ�ڵ��������
						NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
						DIJ_VD_QUEUE& Queue,    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
						USHORT SourceID         //��Դ�ڵ�ID
						);