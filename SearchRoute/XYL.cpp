#include "XYL.h"
#include <algorithm>
#include <iomanip>///////////////////

void XYL(std::vector<std::vector<MatrixNode>>& Matrix, std::vector<MatrixNode>& Re)
{
	Matrix[0][0].RealValue = Matrix[0][0].value = MAX;//起点不能直接到终点
	Re.clear();


	std::cout << "原始矩阵" << std::endl;
	show(Matrix);


	MatrixNode TmpValue;
	UINT i(0), j(0), Flag(1), Zero(0), ZX(0), ZY(0),ZX1(0),ZY1(0);//Z:零个数  x(i)  y(j)       ZX1:ZX'  ZY1:ZY'

//每行减去最小
	std::for_each(Matrix.begin(), Matrix.end(), [&](std::vector<MatrixNode> & MLine){
		TmpValue = *std::min_element(MLine.begin(), MLine.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){
												return lhs.value < rhs.value;
									});//找出每行最小值
		std::for_each(MLine.begin(), MLine.end(), [&](MatrixNode& Nod){
			Nod.value -= TmpValue.value;//每行减去最小值
		});
	});

	std::cout << "减去每行最小值矩阵" << std::endl;
	show(Matrix);

//每列减去最小
	for (i = 0; i <Matrix[0].size(); ++i)//每一列
	{
		TmpValue = Matrix[0][i];
		for (j = 0; j < Matrix.size(); ++j)
		{
			if (Matrix[j][i].value < TmpValue.value)
			TmpValue = Matrix[j][i];//找出最小值
		}
		
			for (j = 0; j < Matrix.size(); ++j)
				Matrix[j][i].value -= TmpValue.value;//减去最小值
	}

	std::cout << "减去每列最小值矩阵" << std::endl;
	show(Matrix);


	while (1)
	{
		std::vector<UINT> A(Matrix.size(), 1), B(Matrix.size(), 0); //A列  B行
		Re.clear();
		std::vector<std::vector<MatrixNode>> M(Matrix);//拷贝临时矩阵

		Flag = 1;
		while (Flag)//循环查找单独的零,直到找不到新的为止  Flag ==1:找得到新的独立零
		{
			Flag = 0;
			for (i = 0; i < M.size(); ++i)//每一行 若只有一个零
			{
				Zero = 0;
				for (j = 0; j < M[0].size(); ++j)
				{
					if (0 == M[i][j].value)
					{
						++Zero;
						ZX = i;
						ZY = j;//零个数与位置
					}
				}
				if (1 == Zero)
				{
					Flag = 1;
					Re.push_back(M[ZX][ZY]);//记录零位置
					B[M[ZX][ZY].Y] = 1;      //B向量
					for (j = 0; j < M.size(); ++j)
					{
						M[j].erase(M[j].begin() + ZY);
					}
				}
				if (M.empty() || M[0].empty() || (Re.size() == Matrix.size())) // 矩阵为空或者已经找到 足够的零了
				{
					return; //M空，返回
				}

			}

			std::cout << "删除每行单独零后矩阵" << std::endl;
			show(M);

			for (i = 0; i < M[0].size(); ++i)//每一列 若只有一个零
			{
				Zero = 0;
				for (j = 0; j < M.size(); ++j)
				{
					if (0 == M[j][i].value)
					{
						++Zero;
						ZX = j;
						ZY = i;//零个数与位置
					}
				}
				if (1 == Zero)
				{
					Flag = 1;
					Re.push_back(M[ZX][ZY]);//记录零位置
					A[M[ZX][ZY].X] = 0;    //A矩阵
					M.erase(M.begin() + ZX);
				}
				if (M.empty() || M[0].empty()|| (Re.size()==Matrix.size())) // 矩阵为空或者已经找到 足够的零了
				{
					return; //M空，返回
				}
			}

			std::cout << "删除每列单独零后矩阵" << std::endl;
			show(M);
		}

		std::cout << "删除单独零后矩阵" << std::endl;
		show(M);

		if (M.empty() || M[0].empty() || (Re.size() == Matrix.size()))
		{
			break;
		}

		Flag = 0;
		TmpValue = MatrixNode{1,0,0};

		for (i = 0; i < M.size(); ++i) //找到第一个零,若存在，保存到TmpValue
		{
			for (j = 0; j < M[0].size(); ++j)
			{
				if (M[i][j].value == 0)
				{
					Flag = 1;
					ZX1=ZX = i;
					ZY1=ZY = j;//记录第一个零的位置
					TmpValue = M[i][j];//找到第一个零
					break;
				}
			}
			if (Flag)
				break;
		}
	
		if (TmpValue.value == 0)//找到零存在，执行回路操作
		{
			Flag = 1;//有零可找时
			while (Flag && !M.empty())//非空矩阵，假设有零元素
			{
				Flag = 0;
				ZX = ZX1; ZY = ZY1;

				for (i = 0; i < M.size();++i) //寻找第一个同列的零
				{
					if ((M[i][ZY].value == 0 )&& (i != ZX))
					{
						ZX1 = i;
						Flag = 1;//找到同列零标志
						break;
					}
				}
				if (Flag)//找到了同列的零 接着找这个零的同行零
				{
					for (j = 0; j < M[0].size(); ++j) //寻找第一个同行的零
					{
						if ((M[ZX1][j].value == 0) && (j != ZY))
						{
							ZY1 = j;
							//Flag = 1;//一定能找到
							break;
						}
					}
				}

				std::cout << "回路删除步骤前矩阵" << std::endl;
				show(M);

				Re.push_back(M[ZX][ZY]);
				B[M[ZX][ZY].Y] = 1;      //B
				A[M[ZX][ZY].X] = 0;    //A
				M.erase(M.begin()+ZX);//删除ZX行 


				for (i = 0; i < M.size();++i)
				{
					M[i].erase(M[i].begin() + ZY);//删除ZY列
				}
				if (ZX1 > ZX)
					--ZX1;
				if (ZY1 > ZY)
					--ZY1;			//删除行列后，要调整坐标

				if (M.empty() || M[0].empty() || (Re.size() == Matrix.size()))
				{
					return; //M空，返回
				}

				std::cout << "回路删除步骤后矩阵" << std::endl;
				show(M);

// 				if (!Flag)//没找到同列的零  找同行的零
// 				{
// 					for (j = 0; j < M[0].size; ++j) //寻找第一个同行的零
// 					{
// 						if ((M[ZX][ZY].value == 0) && (i != ZX))
// 						{
// 							ZY1 = i;
// 							Flag = 1;//找到零标志
// 							break;
// 						}
// 					}
// 				}
			}
		}


		if (M.empty() || M[0].empty() || (Re.size() == Matrix.size()))//回路操作是否搞定
		{
			break;
		}else  //非空且没有零存在
		{
			TmpValue = M[0][0];
			for (i = 0; i < M.size(); ++i) //找到剩下的最小值，保存到TmpValue
			{
				for (j = 0; j < M[0].size(); ++j)
				{
					if (TmpValue.value>M[i][j].value)
					{
						TmpValue = M[i][j];
					}
				}
			}
			for_each(A.begin(), A.end(), [&](UINT & a){ a = (a*TmpValue.value); });
			for_each(B.begin(), B.end(), [&](UINT & b){ b = (b*TmpValue.value); });

			std::cout << "减去A B 前矩阵" << std::endl;
			show(Matrix);

			for (i = 0; i < Matrix.size(); ++i) //找到剩下的最小值，保存到TmpValue
			{
				for (j = 0; j < Matrix[0].size(); ++j)
				{
					Matrix[i][j].value =(Matrix[i][j].value==MAX)? MAX: Matrix[i][j].value - A[i] + B[j];
				}
			}

			std::cout << "减去A B 后矩阵" << std::endl;
			show(Matrix);


		}
	}



}

void show(std::vector<std::vector<MatrixNode>>& M)
{
	std::for_each(M.begin(), M.end(), [](std::vector<MatrixNode> & MLine){
		 		std::for_each(MLine.begin(), MLine.end(), [](MatrixNode& Nod){ 
					if (Nod.value>MAX - 3000)
					{
						std::cout << std::setw(5) << "*";
					}
					else
					{
						std::cout << std::setw(5) <<Nod.value;
					}
		 			
		 		});
		 		std::cout << std::endl;
	});
	std::cout << std::endl;
}