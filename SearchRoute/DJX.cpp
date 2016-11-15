#include "DJX.h"
#include <iomanip>
#include <algorithm>
void DJX(std::vector<std::vector<MatrixNode>>& Matrix, std::vector<MatrixNode>&  Re)
{
// 	Matrix.clear();     //测试数据
// 	Matrix.push_back(std::vector<MatrixNode>{});
// 	Matrix.push_back(std::vector<MatrixNode>{});
// 	Matrix.push_back(std::vector<MatrixNode>{});
// 	Matrix.push_back(std::vector<MatrixNode>{});
// 
// 	Matrix.at(0).push_back(MatrixNode{ 0, 0, 2, 2, 0, 0 });
// 	Matrix.at(0).push_back(MatrixNode{ 0, 1, 1, 1, 0, 0 });
// 	Matrix.at(0).push_back(MatrixNode{ 0, 2, 3, 3, 0, 0 });
// 	Matrix.at(0).push_back(MatrixNode{ 0, 3, 2, 2, 0, 0 });
// 
// 	Matrix.at(1).push_back(MatrixNode{ 1, 0, 1, 1, 0, 0 });
// 	Matrix.at(1).push_back(MatrixNode{ 1, 1, 3, 3, 0, 0 });
// 	Matrix.at(1).push_back(MatrixNode{ 1, 2, 3, 3, 0, 0 });
// 	Matrix.at(1).push_back(MatrixNode{ 1, 3, 3, 3, 0, 0 });
// 
// 	Matrix.at(2).push_back(MatrixNode{ 2, 0, 2, 2, 0, 0 });
// 	Matrix.at(2).push_back(MatrixNode{ 2, 1, 2, 2, 0, 0 });
// 	Matrix.at(2).push_back(MatrixNode{ 2, 2, 3, 3, 0, 0 });
// 	Matrix.at(2).push_back(MatrixNode{ 2, 3, 1, 1, 0, 0 });
// 
// 	Matrix.at(3).push_back(MatrixNode{ 3, 0, 2, 2, 0, 0 });
// 	Matrix.at(3).push_back(MatrixNode{ 3, 1, 2, 2, 0, 0 });
// 	Matrix.at(3).push_back(MatrixNode{ 3, 2, 1, 1, 0, 0 });
// 	Matrix.at(3).push_back(MatrixNode{ 3, 3, 2, 2, 0, 0 });
	Matrix[0][0].RealValue = Matrix[0][0].value = MAX;//起点不能直接到终点
	std::vector<std::vector<MatrixNode>> M(Matrix);
	std::vector<MatrixNode> U;//可行点记录数组
	std::vector< UINT > R;		//更新前行号
	std::vector< UINT > L;		//更新前列号
	std::vector< UINT > afa(Matrix.size(),1);   //行记录 大小不变 从原始矩阵提取小矩阵
	std::vector< UINT > bta(Matrix.size(), 1);	//列记录

	std::vector<UINT> Roade;//存储路径
	MatrixNode NewNode;//临时节点
	UINT i(0);//循环变量
	bool flag(1), flag1(0);//

	for (UINT i = 0; i < Matrix.size();++i)//RL 大小一定 当有*产生时 需要更新   ：U更新后由U更新R 有R更新L   使得*位于对角线
	{
		R.push_back(i);
		L.push_back(i);
	}

	Call(Matrix,//原始矩阵
		M,//使用矩阵
		U,//可行点记录数组
		R,//更新前行号
		L,//更新前列号
		afa,//行记录
		bta,//列记录
		Re//结果
		);


	while (flag)
	{
		flag = 0;//0：没找到起点
		flag1 = 1;//1：找到了下一个路径点
		//找起点
		for (i = 0; i < U.size(); ++i)
		{
			if (U.at(i).X == 0 && U.at(i).star == 1)//* ：1：没有提取
			{
				flag = 1;
				NewNode = U.at(i);
				U.at(i).star = 0;
				break;
			}
		}
		while (flag1 && flag)//不断找下一路径点
		{
			Roade.push_back(NewNode.X);//存储路径点到 Roade
			//Roade.push_back(NewNode.Y);//存储路径点到 Roade
			flag1 = 0;//没找到下一路径点
			for (i = 0; i < U.size(); ++i)
			{
				if (U.at(i).star == 1 && U.at(i).X == NewNode.Y)  //没被提取点中选下一点
				{
					U.at(i).star = 0;
					NewNode = U.at(i);//找到下一个路径点
					flag1 = 1;
					break;
				}
			}
		}
	}

	if (U.empty())//无解
	{
		return;
	}
	for (i = 0; i < Roade.size()-1;++i)
	{
		Re.push_back(Matrix.at(Roade.at(i)).at(Roade.at(i + 1)));
	}
	Re.push_back(Matrix.at(Roade.back()).at(Roade.front()));


}

void show(std::vector<std::vector<MatrixNode>>& M)
{
	std::for_each(M.begin(), M.end(), [](std::vector<MatrixNode> & MLine){
		std::for_each(MLine.begin(), MLine.end(), [](MatrixNode& Nod){
			if (Nod.value == MAX)
			{
				std::cout << std::setw(5) << "*";
			}
			else{
				std::cout <<std::setw(5)<< Nod.value;
			}
		});
		std::cout << std::endl;
	});
	std::cout << std::endl;
}
//更新变量	
void UpdateVar(std::vector<std::vector<MatrixNode>>& M, //临时矩阵M      
	MatrixNode_QUEUE& ZeroQueue,//零元素优先队列
	std::vector< UINT >& afa,   //行记录
	std::vector< UINT >& bta,	//列记录
	std::vector< UINT >& A,		//行罚数
	std::vector< UINT >& B		//列罚数
	)
{

	std::cout << "减去最小值前矩阵" << std::endl;
	show(M);

	afa.assign(afa.size(),1);
	bta.assign(bta.size(), 1);
	std::vector< UINT >swtmp1(M.size(), 0), swtmp2(M.size(), 0);
	MatrixNode_QUEUE mqtmp;
	A.swap(swtmp1);
	B.swap(swtmp2);
	ZeroQueue.swap(mqtmp);


	MatrixNode TmpValue;
	UINT i(0), j(0);

	//每行减去最小
	std::for_each(M.begin(), M.end(), [&](std::vector<MatrixNode> & MLine){
		TmpValue = *std::min_element(MLine.begin(), MLine.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){
			return lhs.value < rhs.value;
		});//找出每行最小值
		std::for_each(MLine.begin(), MLine.end(), [&](MatrixNode& Nod){
			Nod.value =( Nod.value == MAX ? MAX : Nod.value-TmpValue.value);//每行减去最小值
		});
	});

	std::cout << "减去每行最小值矩阵" << std::endl;
	show(M);

	//每列减去最小
	for (i = 0; i < M[0].size(); ++i)//每一列
	{
		TmpValue = M[0][i];
		for (j = 0; j < M.size(); ++j)
		{
			if (M[j][i].value < TmpValue.value)
				TmpValue = M[j][i];//找出最小值
		}

		for (j = 0; j < M.size(); ++j)
			M[j][i].value =( M[j][i].value == MAX ? MAX : M[j][i].value-TmpValue.value);//减去最小值
	}

	std::cout << "减去每列最小值矩阵" << std::endl;
	show(M);
	
// 当只有单个元素时不能正确计算罚数
// 计算每行罚数
	std::vector<MatrixNode> TmpM;//临时矩阵行/列
	for (i = 0; i < M.size(); ++i)
	{
		TmpM.assign(M[i].begin(),M[i].end());
		std::sort(TmpM.begin(), TmpM.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){ return lhs.value < rhs.value; });
		A[i] = TmpM[1].value - TmpM[0].value;
	}
	//计算每列罚数
	for (i = 0; i < M[0].size(); ++i)
	{
		TmpM.clear();
		for (j = 0; j < M.size(); ++j)
		{
			TmpM.push_back(M[j][i]);
		}
		std::sort(TmpM.begin(), TmpM.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){ return lhs.value < rhs.value; });
		B[i] = TmpM[1].value - TmpM[0].value;
	}
	//求ZeroQueue
	for (i = 0; i < M.size(); ++i)
	{
		for (j = 0; j < M[0].size(); ++j)
		{
			if (M.at(i).at(j).value == 0)
			{
				M.at(i).at(j).panish = A.at(i) + B.at(j);
				ZeroQueue.push(M.at(i).at(j));
			}
		}
	}


}
//检查合法性
bool Check(std::vector<MatrixNode> U,//可行点记录数组
	std::vector<std::vector<MatrixNode>>& Matrix, //原始矩阵M      获取大小
	MatrixNode&	CheckNode    //待检查矩阵点
	)
{
	if (U.size() == Matrix.size())
	{
		return false;
	}
	if (U.empty())
	{
		return true;
	}
	std::vector<UINT> T;//统计节点出现次数数组：次数检查  环路检查：添加前检查+添加后检查
	MatrixNode  StartNode, tmpNode;
	UINT i(0), j(0);//循环变量
	bool flag(0);//找到标志1 / 已提取到路径0


	for (i = 0; i < U.size(); ++i)//X次数检查
	{
		if (U.at(i).X==CheckNode.X)
		{
			return false;
		}
	}
	for (i = 0; i < U.size(); ++i)//Y次数检查
	{
		if (U.at(i).Y == CheckNode.Y)
		{
			return false;
		}
	}

	for (i = 0; i < U.size();++i)//添加新点前检查
	{
		std::vector<UINT>swtmp(Matrix.size(), 0);
		T.swap(swtmp);//清空T
		StartNode = U.at(i);
		++T.at(StartNode.X);
		++T.at(StartNode.Y);
		tmpNode = StartNode;
		
		while (1)//找以当前start的路径
		{
			flag = 0;
			for (j = 0; j < U.size();++j)
			{
				if (U.at(j).X == tmpNode.Y && U.at(j).X!=StartNode.X)//找下一个点 且不能是出发点
				{
					tmpNode = U.at(j);
					flag = true;//找到了下一点
					break;
				}
			}
			if (!flag)//若没有下一点了
			{
				break;
			}
			++T.at(tmpNode.X);
			++T.at(tmpNode.Y);
		}

		if (T.at(CheckNode.X) >=2 || T.at(CheckNode.Y)>=2 )
		{
			return false;
		}
		else
		{
			++T.at(CheckNode.X);
			++T.at(CheckNode.Y);
			flag = 0;
			UINT NodeNum(0);
			for (j = 0; j < T.size();++j)
			{
				if (T.at(j)==1)
				{
					flag = 1;//找到1
				}
				if (T.at(j) == 2)
				{
					++NodeNum;//环上节点计数
				}
			}
			if (!flag)//若没找到1
			{
				if (NodeNum == Matrix.size())//若形成完整的环，且包含所有的点 则返回可以添加
				{
					return true;
				}
				return false;
			}
		}
	}
	U.push_back(CheckNode);//添加新点后检查
	for (i = 0; i < U.size(); ++i)
	{
		std::vector<UINT>swtmp(Matrix.size(), 0);
		T.swap(swtmp);//清空T
		StartNode = U.at(i);
		++T.at(StartNode.X);
		++T.at(StartNode.Y);
		tmpNode = StartNode;

		while (1)//找以当前start的路径
		{
			flag = 0;
			for (j = 0; j < U.size(); ++j)
			{
				if ((U.at(j).X == tmpNode.Y) && (U.at(j).X != StartNode.X))
				{
					tmpNode = U.at(j);
					flag = true;//找到了下一点
					break;
				}
			}
			if (!flag)//若没有下一点了
			{
				break;
			}
			++T.at(tmpNode.X);
			++T.at(tmpNode.Y);
		}

		//添加新点后 是否有回路
			flag = 0;
			for (j = 0; j < T.size(); ++j)
			{
				if (T.at(j) == 1)
				{
					flag = 1;//找到1
				}
			}
			if (!flag)//若没找到1
			{
				return false;
			}
	}
	return true;


}

//递归函数
void Call(std::vector<std::vector<MatrixNode>>& Matrix,//原始矩阵
	std::vector<std::vector<MatrixNode>>& M,//使用矩阵
	std::vector<MatrixNode>& U,//可行点记录总数组
	std::vector< UINT >& R,		//更新前行号
	std::vector< UINT >& L,	//更新前列号
	std::vector< UINT >& afa,   //行记录
	std::vector< UINT >& bta,	//列记录
	std::vector<MatrixNode>&  Re//结果
	)
{
	MatrixNode_QUEUE ZeroQueue;//零元素优先队列
	std::vector< UINT > A;		//行罚数
	std::vector< UINT > B;		//列罚数
	
	if (M.empty())
	{
		return;
	}
	if (M.size() == 1)
	{
		M.front().front().star = 1;
		U.push_back(M.front().front());
		return;
	}

	UpdateVar(M,  //临时矩阵M      
				ZeroQueue,//零元素优先队列
				afa,     //行记录
				bta,	//列记录
				A,		//行罚数
				B		//列罚数
				);

	if (ZeroQueue.size()==0)
	{
		U.clear();//无解
		return;
	}

/*	show(M);*/
	std::vector<MatrixNode> TmpU;//可行点记录当前数组  ：不可行的点在递归前就设为MAX 不会进入优先队列
	std::vector<UINT> Roade;//存储路径
	MatrixNode NewNode, StartNode;//临时节点
	UINT i(0), j(0),k(0);//循环变量
	bool flag(1),flag1(0);//

	while (!ZeroQueue.empty())
	{
		NewNode = ZeroQueue.top();
		if (Check(TmpU, Matrix, NewNode))
		{
			NewNode = ZeroQueue.top();
			NewNode.star = 1;
			TmpU.push_back(NewNode);
			Matrix.at(NewNode.X).at(NewNode.Y).star = 1;//标记* 为1
		}
		ZeroQueue.pop();
	}
	U.insert(U.end(), TmpU.begin(), TmpU.end());//当前TmpU 添加到总的U
	if (U.size() == Matrix.size())
	{
		return;
	}
	//从U复制到TmpU  提取所有路径直到TmpU*标志全为0
	TmpU.assign(U.begin(), U.end());//此时TmpU的 *标记为1  此时*表用于表明是否已经提取到路径中:0： 已经提取 1： 没有提取
	Roade.clear();
	while (flag) 
	{
		flag = 0;//0：没找到起点
		flag1 = 1;//1：找到了下一个路径点
		//找起点
		for (i = 0; i < TmpU.size();++i)
		{
			if (TmpU.at(i).star == 1 )//* ：1：没有提取
			{
				flag = 1;            
				StartNode = TmpU.at(i);
				NewNode = StartNode;
				TmpU.at(i).star = 0;
				break;
			}
		}
		while (flag1 && flag)//不断找下一路径点
		{
			Roade.push_back(NewNode.X);//存储路径点到 Roade
			//Roade.push_back(NewNode.Y);//存储路径点到 Roade
			flag1 = 0;//没找到下一路径点
			for (i = 0; i < TmpU.size();++i)
			{
				if (TmpU.at(i).star == 1 && TmpU.at(i).X == NewNode.Y && TmpU.at(i).X != StartNode.X )  //没被提取点中选下一点
				{
					TmpU.at(i).star = 0;
					NewNode = TmpU.at(i);//找到下一个路径点
					flag1 = 1;
					break;
				}
			}
		}
		if (flag != 0 && NewNode.Y == StartNode.X)
		{
			Roade.push_back(NewNode.Y);
		}
	}
	for (i = 0; i < Roade.size();++i)//根据路径 调整R
	{
		R.at(i) = Roade.at(i);
		R.at(Roade.at(i)) = i;
	}

	for (i = 0; i < U.size();++i) //根据U R 调整L
	{
		//k = 0;
		for (j = 0; j < R.size();++j)
		{
			if (R.at(j) == U.at(i).X)
			{
				k = j;//U中元素（M,N）M在R中位置 K
				break;
			}
		}
		L.at(k) = U.at(i).Y;
		L.at(U.at(i).Y) = k;
	}

	//根据R L 组合新矩阵
	for (i = 0; i < Matrix.size();++i)
	{
		if (Matrix.at(R.at(i)).at(L.at(i)).star ==1)//Matrix(R L) *为1？ 
		{
			afa.at(R.at(i)) = 0;
			bta.at(L.at(i)) = 0;
		}
	}

	//更新M
	M.clear();
	std::vector<MatrixNode> TmpVectorMatrixNode;
	MatrixNode TmpMatrixNode;

	for (i = 0; i < afa.size();++i)
	{
		if (afa.at(i) == 1)
		{
			M.push_back(TmpVectorMatrixNode);
		}
		for (j = 0; j < bta.size();++j)
		{
			if ((afa.at(i)==1) && (bta.at(j)==1))
			{
				TmpMatrixNode = Matrix.at(i).at(j);
				M.back().push_back(TmpMatrixNode);
			}
		}
	}
	if (M.empty())
	{
		return; ///////////待商讨
	}



	for (i = 0; i < M.size();++i)
	{
		for (j = 0; j < M.front().size();++j)
		{
			if (!Check(U, Matrix, M.at(i).at(j)))
				M.at(i).at(j).value = MAX;
		}
	}
	for (i = 0; i < M.front().size();++i)//调整行顺序 使得MAX在对角线上
	{
		k = 0;//记录当前列的max行数
		for (j = 0; j < M.size();++j)
		{
			if (M.at(j).at(i).value == MAX)
			{
				k = j;
				break;
			}
		}
		//M.at(i).swap(M.at(k));
		TmpVectorMatrixNode = M.at(k);
		M.at(k) = M.at(i);
		M.at(i) = TmpVectorMatrixNode;

	}
/*	show(M);*/
	
	Call(Matrix,//原始矩阵
		M,//使用矩阵
		U,//可行点记录数组
		R,//更新前行号
		L,//更新前列号
		afa,//行记录
		bta,//列记录
		Re//结果
		);

}