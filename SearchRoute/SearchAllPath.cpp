#include "SearchAllPath.h"
#include "InitialSearchAllPath.h"
#include "SingleSourceSearch.h"

#include <algorithm>
void SearchAllPath(GRAPH& Graph, //ͼ
					PATH_TREE& PathTree,//DJ�㷨·����
					PATH_TABLE& PathTable,//·����
					NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
					DIJ_VD_QUEUE& Queue    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
					)
{
	InitialSearchAllPath(Graph, PathTree, PathTable, NodeDemand, Queue);
	
	short TableLine(0);//·��������

	std::for_each(NodeDemand.begin(), NodeDemand.end(), 
			[&](const USHORT& source){//��ʽ���ò��� + ÿһ�εĳ����㣺source const

										if (source != *(NodeDemand.begin() + 1))//����ǰ�����㲻���յ�
										{
											TableLine = (std::find(NodeDemand.cbegin(), NodeDemand.cend(), source) - NodeDemand.cbegin())-1;
											TableLine = TableLine< 0 ? 0 : TableLine; //	���㵱ǰsource��Ӧ��·��������
											SingleSourceSearch(Graph, PathTree, PathTable[TableLine], NodeDemand, Queue, source);
										}
									});
//���������
// 	for (int i = 0; i < NodeDemand.size(); ++i)
// 	{
// 		if (i != 1)//����ǰ�����㲻���յ�
// 			SingleSourceSearch(Graph, PathTree, PathTable[NodeDemand[i]], NodeDemand, Queue, NodeDemand[i]);
// 	}

}