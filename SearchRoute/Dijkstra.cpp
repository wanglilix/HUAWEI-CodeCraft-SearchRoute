#include "Dijkstra.h"
#include <algorithm>
void Dijkstra(
				GRAPH& Graph, //ͼ
				PATH_TREE& PathTree,//DJ�㷨·����
				std::vector<PATH>& PathTableLine,//·�����ӦԴ�ڵ��������
				NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
				DIJ_VD_QUEUE& Queue,    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
				USHORT SourceID,         //��Դ�ڵ�ʼ��ID
				UINT&  AlreadyFind,      //��Ѱ����
				UINT&  NowFind,			//��Ѱ����
				UINT&  NeedFind       //�ؾ�����
			)
{
	if (SourceID == *(NodeDemand.begin()))//S��
		 ++NeedFind;//S��Ϊ������ʱ��NeedFindҪ��һ��
	
	DIJ_VD SmallNode;  //��������ĵط� ��С�ڵ�
	PATH TmpPath;      //��������ĵط���ʱ·��
	USHORT TmpID(0);     //��������ĵط���ʱID
	short TableRow(0);	//·��������
	UINT TmpVd(0);      //��ʱȨ��
	std::vector<UINT>::iterator TmpIterator ;//��ʱ������

	while (1)
	{
		if ((AlreadyFind + NowFind) == NeedFind || Queue.empty())//���������бؾ���,����������ѭ��    //�����ȶ���Ϊ��,����������ѭ��
			break;

		SmallNode = Queue.top();
		Queue.pop();//ȡ����ɾ����С�ڵ�
		
		PathTree[SmallNode.curID] = SmallNode.fatID;//��С�ڵ����·����
		Graph[SmallNode.curID][0].isInPathTree = true;//������С�ڵ�Ϊ����־

		if (Graph[SmallNode.curID][0].isDominators)//����С�ڵ��Ǳؾ��ڵ�
		{
			++NowFind;
			if (PathTree[SmallNode.curID] != SmallNode.curID) //��·�����ڵ㲻�Ǳ���
			{
				TmpPath.clear();//�����ʱ����
				TmpID = SmallNode.curID;
				TmpPath.push_back(Graph[SmallNode.curID][0].vd);  //��ȡȨ��
				TmpPath.push_back(SmallNode.fatID);  //����ʱ�����ռλ�ã��ȵ��ҵ�������ֱ���滻
				TmpPath.push_back(SmallNode.curID);  //�յ����
				TmpIterator = TmpPath.end();
				while (PathTree[PathTree[TmpID]] != PathTree[TmpID])//����û��������ʱ
				{
					TmpID = PathTree[TmpID];
					TmpIterator = TmpPath.insert(TmpIterator, TmpID);   //��ȡ·��
				}
				TmpPath[1] = PathTree[TmpID];

				TableRow = (std::find(NodeDemand.cbegin(), NodeDemand.cend(), SmallNode.curID) - NodeDemand.cbegin()) - 1;//	���㵱ǰ��С�ڵ㼴�յ� ��Ӧ��·��������
				PathTableLine[TableRow].swap(TmpPath);//����·��
			}
		
		}
		if (!Graph[SmallNode.curID][0].isDominators || (SmallNode.curID == SourceID))//����С�ڵ㲻�Ǳؾ��ڵ�����ǵ�ǰ��������һ�ؾ��ڵ�
		{
			std::for_each(++Graph[SmallNode.curID].begin(), Graph[SmallNode.curID].end(), 
				[&](NODE_UNIT & neighborNode){
													TmpVd = SmallNode.vd + neighborNode.cost;
													if ((!Graph[neighborNode.ID][0].isInPathTree) && (TmpVd< Graph[neighborNode.ID][0].vd)) //���ھ�Ϊ�����ڵ��ҿ��Ը���Vd
													{
														Queue.push(DIJ_VD{ neighborNode.ID, SmallNode.curID, TmpVd });//����µĽڵ㵽���ȶ���
														Graph[neighborNode.ID][0].vd = std::move(TmpVd);//���·����ھ�Vd
													}
					
			});
		}

	}

}
