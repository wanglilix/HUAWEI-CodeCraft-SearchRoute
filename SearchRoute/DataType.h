#ifndef __DATATYPE_H__
#define __DATATYPE_H__



#include <vector>
#include <queue>

//#define NodeNum 500//��Ŀ���������
#define MAX      0xffffffff//���·��
#define MAX_COST static_cast<unsigned char>(0xff)//�������Ȩ��
typedef unsigned char UCHAR;//Ȩ��cost[1 20]:һ���ֽ�0-255
typedef unsigned short USHORT;//���ID[1 600]:�����ֽ�0-65535������߱�ţ�Ŀǰ��Ŀ�������������ͣ�
typedef unsigned int UINT;//·������vd:�ĸ��ֽ�
typedef struct 
{
	bool isDominators = { false };//�Ƿ��Ǳؾ���
	bool isInPathTree = { false };//�Ƿ�λ��·����
	UCHAR cost;//Ȩ��
	USHORT ID;//DestinationID
	USHORT edge;//����߱��
	UINT vd = { MAX };//·������
} NODE_UNIT;//һ���ڵ�struct
typedef std::vector<std::vector<NODE_UNIT>> GRAPH;//ͼ
typedef struct
{
	USHORT curID;//CurrentID
	USHORT fatID;//��ʱFatherID
	UINT vd;//·������
} DIJ_VD;//Dijkstra�����ȶ��н��ID

struct CompareVd :public std::binary_function<const DIJ_VD, const DIJ_VD, bool>
{
	bool operator()(const DIJ_VD& lhs, const DIJ_VD& rhs) const
	{
		return lhs.vd > rhs.vd;
	}
};//Compare VD
typedef std::priority_queue<DIJ_VD, std::vector<DIJ_VD>, CompareVd> DIJ_VD_QUEUE;//Dijkstra��VD���ȶ���

// typedef struct BRANCH
// {
// 	BRANCH* pFather;//ָ�򸸽��
// 	USHORT curID;//CurrentID
// } BRANCH;//·������һ�����
typedef std::vector<USHORT> NODEDEMAND;//{S,E,V'}
typedef std::vector<USHORT> PATH_TREE;//Dijkstra·����:�±�Ϊ��ǰ�ڵ���ţ��洢Ϊ���ڵ����: ��ʼ��Ϊ���ڵ����
typedef std::vector<UINT> PATH;//·����Ȩ+��+��+·
typedef std::vector<std::vector<PATH>> PATH_TABLE;//·����

typedef struct
{
	USHORT X;//������
	USHORT Y;//������
	UINT value;//ֵ
	UINT RealValue;//����ֵ
	UINT panish;//����
	UINT star;//*��
}MatrixNode;//�Խ����㷨����ڵ�
struct CompareMatrixNode :public std::binary_function<const MatrixNode, const MatrixNode, bool>
{
	bool operator()(const MatrixNode& lhs, const MatrixNode& rhs) const
	{
		return lhs.panish < rhs.panish;
	}
};
typedef std::priority_queue<MatrixNode, std::vector<MatrixNode>, CompareMatrixNode> MatrixNode_QUEUE;//Dijkstra��Vd���ȶ���

//�ӿڳ�ʼ������
void InitialInterface(
	char *topo[5000], int edge_num, char *demand,
	GRAPH& Graph, //ͼ
	PATH_TREE& PathTree,//DJ�㷨·����
	PATH_TABLE& PathTable,//·����
	NODEDEMAND& NodeDemand, //���+�յ�+�ؾ��㣺�����ؾ���λ�����һλ
	DIJ_VD_QUEUE& Queue    //Dijkstra�㷨��VD���ȶ��У����޸Ķ��У�ֻpush,pop
	);

#endif // !__DATATYPE_H__