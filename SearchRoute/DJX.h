#include "DataType.h"
#include <vector>
#include <iostream>
void DJX(std::vector<std::vector<MatrixNode>>& Matrix, std::vector<MatrixNode>& Re);
void show(std::vector<std::vector<MatrixNode>>& M);
//递归函数
void Call(std::vector<std::vector<MatrixNode>>& Matrix,//原始矩阵
		  std::vector<std::vector<MatrixNode>>& M,//使用矩阵
		  std::vector<MatrixNode>& U,//可行点记录数组
		  std::vector< UINT >& R,		//更新前行号
		  std::vector< UINT >& L,	//更新前列号
		  std::vector< UINT >& afa,   //行记录
		  std::vector< UINT >& bta,	//列记录
		  std::vector<MatrixNode>&  Re//结果
			);
//更新变量	
void UpdateVar(std::vector<std::vector<MatrixNode>>& M, //临时矩阵M      
			    MatrixNode_QUEUE& ZeroQueue,//零元素优先队列
				std::vector< UINT >& afa,   //行记录
				std::vector< UINT >& bta,	//列记录
				std::vector< UINT >& A,		//行罚数
				std::vector< UINT >& B		//列罚数

				);  
//检查合法性
bool Check(std::vector<MatrixNode> U,//可行点记录数组
			std::vector<std::vector<MatrixNode>>& Matrix, //临时矩阵M :获取矩阵大小     
			MatrixNode&	CheckNode    //待检查矩阵点
	);

