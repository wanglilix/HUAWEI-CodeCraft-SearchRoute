#include "DataType.h"
void SingleSourceSearch(
						GRAPH& Graph, //图
						PATH_TREE& PathTree,//DJ算法路径树
						std::vector<PATH>& PathTableLine,//路径表对应源节点的行引用
						NODEDEMAND& NodeDemand, //起点+终点+必经点：新增必经点位于最后一位
						DIJ_VD_QUEUE& Queue,    //Dijkstra算法的VD优先队列，不修改队列，只push,pop
						USHORT SourceID         //单源节点ID
						);