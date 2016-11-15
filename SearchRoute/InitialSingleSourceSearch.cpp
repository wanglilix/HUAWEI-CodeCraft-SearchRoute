#include "InitialSingleSourceSearch.h"
#include <algorithm>
void InitialSingleSourceSearch(
						GRAPH&  Graph, //ͼ
						PATH_TREE&  PathTree,//DJ�㷨·����
						std::vector<PATH>& PathTableLine,//·�����ӦԴ�ڵ��������
						NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
						DIJ_VD_QUEUE& Queue,    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
						USHORT SourceID,         //��Դ�ڵ�ID
						UINT&  AlreadyFind      //��Ѱ����
						)
{
	Graph[SourceID][0].vd = 0;  //�ǰ�������VdΪ0

	//������ȶ���  �������·����
	DIJ_VD_QUEUE tmp;
	Queue.swap(tmp);
// 	while (!Queue.empty())
// 		Queue.pop();
	//��ǰ������װ�����ȶ��� ��ʱ�����Ϊ������
 	Queue.push(DIJ_VD{ SourceID, SourceID, 0 });

	std::for_each(PathTableLine.begin(), PathTableLine.end(), 
		[&]( PATH& path){
								if ( MAX != path[0]    //·��Ȩ�ط�MAX
									&& 
								   ( path.cend()==std::find(path.cbegin()+3 ,path.cend(),(UINT)*(NodeDemand.crbegin())))) //·��:��ȥȨ�ء���������յ�  ������NodeDemand���һλ�ڵ�
								{
									Graph[*(path.begin() + 2)][0].isInPathTree = true;  //��ʾ��·���Ѿ�λ��·����
									++AlreadyFind;   //��Ѱ��������
								}
								else
								{
									PATH tmp{ MAX,0,0 };
									path.swap(tmp);//��·�������������ؾ��ڵ㣬��ɾ��·��
								}
	});


}