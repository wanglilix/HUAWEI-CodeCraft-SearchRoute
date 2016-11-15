#ifndef __DATATYPE_H__
#define __DATATYPE_H__



#include <vector>
#include <queue>

//#define NodeNum 500//题目的最大结点数
#define MAX      0xffffffff//最大路径
#define MAX_COST static_cast<unsigned char>(0xff)//最大连接权重
typedef unsigned char UCHAR;//权重cost[1 20]:一个字节0-255
typedef unsigned short USHORT;//结点ID[1 600]:两个字节0-65535，有向边编号（目前题目给出的数据类型）
typedef unsigned int UINT;//路径估计vd:四个字节
typedef struct 
{
	bool isDominators = { false };//是否是必经点
	bool isInPathTree = { false };//是否位于路径树
	UCHAR cost;//权重
	USHORT ID;//DestinationID
	USHORT edge;//有向边编号
	UINT vd = { MAX };//路径估计
} NODE_UNIT;//一个节点struct
typedef std::vector<std::vector<NODE_UNIT>> GRAPH;//图
typedef struct
{
	USHORT curID;//CurrentID
	USHORT fatID;//临时FatherID
	UINT vd;//路径估计
} DIJ_VD;//Dijkstra的优先队列结点ID

struct CompareVd :public std::binary_function<const DIJ_VD, const DIJ_VD, bool>
{
	bool operator()(const DIJ_VD& lhs, const DIJ_VD& rhs) const
	{
		return lhs.vd > rhs.vd;
	}
};//Compare VD
typedef std::priority_queue<DIJ_VD, std::vector<DIJ_VD>, CompareVd> DIJ_VD_QUEUE;//Dijkstra的VD优先队列

// typedef struct BRANCH
// {
// 	BRANCH* pFather;//指向父结点
// 	USHORT curID;//CurrentID
// } BRANCH;//路径树的一个结点
typedef std::vector<USHORT> NODEDEMAND;//{S,E,V'}
typedef std::vector<USHORT> PATH_TREE;//Dijkstra路径树:下标为当前节点序号，存储为父节点序号: 初始化为本节点序号
typedef std::vector<UINT> PATH;//路径：权+起+终+路
typedef std::vector<std::vector<PATH>> PATH_TABLE;//路径表

typedef struct
{
	USHORT X;//行坐标
	USHORT Y;//列坐标
	UINT value;//值
	UINT RealValue;//不变值
	UINT panish;//罚数
	UINT star;//*标
}MatrixNode;//对角线算法矩阵节点
struct CompareMatrixNode :public std::binary_function<const MatrixNode, const MatrixNode, bool>
{
	bool operator()(const MatrixNode& lhs, const MatrixNode& rhs) const
	{
		return lhs.panish < rhs.panish;
	}
};
typedef std::priority_queue<MatrixNode, std::vector<MatrixNode>, CompareMatrixNode> MatrixNode_QUEUE;//Dijkstra的Vd优先队列

//接口初始化函数
void InitialInterface(
	char *topo[5000], int edge_num, char *demand,
	GRAPH& Graph, //图
	PATH_TREE& PathTree,//DJ算法路径树
	PATH_TABLE& PathTable,//路径表
	NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
	DIJ_VD_QUEUE& Queue    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
	);

#endif // !__DATATYPE_H__