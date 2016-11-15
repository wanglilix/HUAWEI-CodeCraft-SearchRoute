#include "XYL.h"
#include <algorithm>
#include <iomanip>///////////////////

void XYL(std::vector<std::vector<MatrixNode>>& Matrix, std::vector<MatrixNode>& Re)
{
	Matrix[0][0].RealValue = Matrix[0][0].value = MAX;//��㲻��ֱ�ӵ��յ�
	Re.clear();


	std::cout << "ԭʼ����" << std::endl;
	show(Matrix);


	MatrixNode TmpValue;
	UINT i(0), j(0), Flag(1), Zero(0), ZX(0), ZY(0),ZX1(0),ZY1(0);//Z:�����  x(i)  y(j)       ZX1:ZX'  ZY1:ZY'

//ÿ�м�ȥ��С
	std::for_each(Matrix.begin(), Matrix.end(), [&](std::vector<MatrixNode> & MLine){
		TmpValue = *std::min_element(MLine.begin(), MLine.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){
												return lhs.value < rhs.value;
									});//�ҳ�ÿ����Сֵ
		std::for_each(MLine.begin(), MLine.end(), [&](MatrixNode& Nod){
			Nod.value -= TmpValue.value;//ÿ�м�ȥ��Сֵ
		});
	});

	std::cout << "��ȥÿ����Сֵ����" << std::endl;
	show(Matrix);

//ÿ�м�ȥ��С
	for (i = 0; i <Matrix[0].size(); ++i)//ÿһ��
	{
		TmpValue = Matrix[0][i];
		for (j = 0; j < Matrix.size(); ++j)
		{
			if (Matrix[j][i].value < TmpValue.value)
			TmpValue = Matrix[j][i];//�ҳ���Сֵ
		}
		
			for (j = 0; j < Matrix.size(); ++j)
				Matrix[j][i].value -= TmpValue.value;//��ȥ��Сֵ
	}

	std::cout << "��ȥÿ����Сֵ����" << std::endl;
	show(Matrix);


	while (1)
	{
		std::vector<UINT> A(Matrix.size(), 1), B(Matrix.size(), 0); //A��  B��
		Re.clear();
		std::vector<std::vector<MatrixNode>> M(Matrix);//������ʱ����

		Flag = 1;
		while (Flag)//ѭ�����ҵ�������,ֱ���Ҳ����µ�Ϊֹ  Flag ==1:�ҵõ��µĶ�����
		{
			Flag = 0;
			for (i = 0; i < M.size(); ++i)//ÿһ�� ��ֻ��һ����
			{
				Zero = 0;
				for (j = 0; j < M[0].size(); ++j)
				{
					if (0 == M[i][j].value)
					{
						++Zero;
						ZX = i;
						ZY = j;//�������λ��
					}
				}
				if (1 == Zero)
				{
					Flag = 1;
					Re.push_back(M[ZX][ZY]);//��¼��λ��
					B[M[ZX][ZY].Y] = 1;      //B����
					for (j = 0; j < M.size(); ++j)
					{
						M[j].erase(M[j].begin() + ZY);
					}
				}
				if (M.empty() || M[0].empty() || (Re.size() == Matrix.size())) // ����Ϊ�ջ����Ѿ��ҵ� �㹻������
				{
					return; //M�գ�����
				}

			}

			std::cout << "ɾ��ÿ�е���������" << std::endl;
			show(M);

			for (i = 0; i < M[0].size(); ++i)//ÿһ�� ��ֻ��һ����
			{
				Zero = 0;
				for (j = 0; j < M.size(); ++j)
				{
					if (0 == M[j][i].value)
					{
						++Zero;
						ZX = j;
						ZY = i;//�������λ��
					}
				}
				if (1 == Zero)
				{
					Flag = 1;
					Re.push_back(M[ZX][ZY]);//��¼��λ��
					A[M[ZX][ZY].X] = 0;    //A����
					M.erase(M.begin() + ZX);
				}
				if (M.empty() || M[0].empty()|| (Re.size()==Matrix.size())) // ����Ϊ�ջ����Ѿ��ҵ� �㹻������
				{
					return; //M�գ�����
				}
			}

			std::cout << "ɾ��ÿ�е���������" << std::endl;
			show(M);
		}

		std::cout << "ɾ������������" << std::endl;
		show(M);

		if (M.empty() || M[0].empty() || (Re.size() == Matrix.size()))
		{
			break;
		}

		Flag = 0;
		TmpValue = MatrixNode{1,0,0};

		for (i = 0; i < M.size(); ++i) //�ҵ���һ����,�����ڣ����浽TmpValue
		{
			for (j = 0; j < M[0].size(); ++j)
			{
				if (M[i][j].value == 0)
				{
					Flag = 1;
					ZX1=ZX = i;
					ZY1=ZY = j;//��¼��һ�����λ��
					TmpValue = M[i][j];//�ҵ���һ����
					break;
				}
			}
			if (Flag)
				break;
		}
	
		if (TmpValue.value == 0)//�ҵ�����ڣ�ִ�л�·����
		{
			Flag = 1;//�������ʱ
			while (Flag && !M.empty())//�ǿվ��󣬼�������Ԫ��
			{
				Flag = 0;
				ZX = ZX1; ZY = ZY1;

				for (i = 0; i < M.size();++i) //Ѱ�ҵ�һ��ͬ�е���
				{
					if ((M[i][ZY].value == 0 )&& (i != ZX))
					{
						ZX1 = i;
						Flag = 1;//�ҵ�ͬ�����־
						break;
					}
				}
				if (Flag)//�ҵ���ͬ�е��� ������������ͬ����
				{
					for (j = 0; j < M[0].size(); ++j) //Ѱ�ҵ�һ��ͬ�е���
					{
						if ((M[ZX1][j].value == 0) && (j != ZY))
						{
							ZY1 = j;
							//Flag = 1;//һ�����ҵ�
							break;
						}
					}
				}

				std::cout << "��·ɾ������ǰ����" << std::endl;
				show(M);

				Re.push_back(M[ZX][ZY]);
				B[M[ZX][ZY].Y] = 1;      //B
				A[M[ZX][ZY].X] = 0;    //A
				M.erase(M.begin()+ZX);//ɾ��ZX�� 


				for (i = 0; i < M.size();++i)
				{
					M[i].erase(M[i].begin() + ZY);//ɾ��ZY��
				}
				if (ZX1 > ZX)
					--ZX1;
				if (ZY1 > ZY)
					--ZY1;			//ɾ�����к�Ҫ��������

				if (M.empty() || M[0].empty() || (Re.size() == Matrix.size()))
				{
					return; //M�գ�����
				}

				std::cout << "��·ɾ����������" << std::endl;
				show(M);

// 				if (!Flag)//û�ҵ�ͬ�е���  ��ͬ�е���
// 				{
// 					for (j = 0; j < M[0].size; ++j) //Ѱ�ҵ�һ��ͬ�е���
// 					{
// 						if ((M[ZX][ZY].value == 0) && (i != ZX))
// 						{
// 							ZY1 = i;
// 							Flag = 1;//�ҵ����־
// 							break;
// 						}
// 					}
// 				}
			}
		}


		if (M.empty() || M[0].empty() || (Re.size() == Matrix.size()))//��·�����Ƿ�㶨
		{
			break;
		}else  //�ǿ���û�������
		{
			TmpValue = M[0][0];
			for (i = 0; i < M.size(); ++i) //�ҵ�ʣ�µ���Сֵ�����浽TmpValue
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

			std::cout << "��ȥA B ǰ����" << std::endl;
			show(Matrix);

			for (i = 0; i < Matrix.size(); ++i) //�ҵ�ʣ�µ���Сֵ�����浽TmpValue
			{
				for (j = 0; j < Matrix[0].size(); ++j)
				{
					Matrix[i][j].value =(Matrix[i][j].value==MAX)? MAX: Matrix[i][j].value - A[i] + B[j];
				}
			}

			std::cout << "��ȥA B �����" << std::endl;
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