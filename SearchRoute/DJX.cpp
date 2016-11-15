#include "DJX.h"
#include <iomanip>
#include <algorithm>
void DJX(std::vector<std::vector<MatrixNode>>& Matrix, std::vector<MatrixNode>&  Re)
{
// 	Matrix.clear();     //��������
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
	Matrix[0][0].RealValue = Matrix[0][0].value = MAX;//��㲻��ֱ�ӵ��յ�
	std::vector<std::vector<MatrixNode>> M(Matrix);
	std::vector<MatrixNode> U;//���е��¼����
	std::vector< UINT > R;		//����ǰ�к�
	std::vector< UINT > L;		//����ǰ�к�
	std::vector< UINT > afa(Matrix.size(),1);   //�м�¼ ��С���� ��ԭʼ������ȡС����
	std::vector< UINT > bta(Matrix.size(), 1);	//�м�¼

	std::vector<UINT> Roade;//�洢·��
	MatrixNode NewNode;//��ʱ�ڵ�
	UINT i(0);//ѭ������
	bool flag(1), flag1(0);//

	for (UINT i = 0; i < Matrix.size();++i)//RL ��Сһ�� ����*����ʱ ��Ҫ����   ��U���º���U����R ��R����L   ʹ��*λ�ڶԽ���
	{
		R.push_back(i);
		L.push_back(i);
	}

	Call(Matrix,//ԭʼ����
		M,//ʹ�þ���
		U,//���е��¼����
		R,//����ǰ�к�
		L,//����ǰ�к�
		afa,//�м�¼
		bta,//�м�¼
		Re//���
		);


	while (flag)
	{
		flag = 0;//0��û�ҵ����
		flag1 = 1;//1���ҵ�����һ��·����
		//�����
		for (i = 0; i < U.size(); ++i)
		{
			if (U.at(i).X == 0 && U.at(i).star == 1)//* ��1��û����ȡ
			{
				flag = 1;
				NewNode = U.at(i);
				U.at(i).star = 0;
				break;
			}
		}
		while (flag1 && flag)//��������һ·����
		{
			Roade.push_back(NewNode.X);//�洢·���㵽 Roade
			//Roade.push_back(NewNode.Y);//�洢·���㵽 Roade
			flag1 = 0;//û�ҵ���һ·����
			for (i = 0; i < U.size(); ++i)
			{
				if (U.at(i).star == 1 && U.at(i).X == NewNode.Y)  //û����ȡ����ѡ��һ��
				{
					U.at(i).star = 0;
					NewNode = U.at(i);//�ҵ���һ��·����
					flag1 = 1;
					break;
				}
			}
		}
	}

	if (U.empty())//�޽�
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
//���±���	
void UpdateVar(std::vector<std::vector<MatrixNode>>& M, //��ʱ����M      
	MatrixNode_QUEUE& ZeroQueue,//��Ԫ�����ȶ���
	std::vector< UINT >& afa,   //�м�¼
	std::vector< UINT >& bta,	//�м�¼
	std::vector< UINT >& A,		//�з���
	std::vector< UINT >& B		//�з���
	)
{

	std::cout << "��ȥ��Сֵǰ����" << std::endl;
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

	//ÿ�м�ȥ��С
	std::for_each(M.begin(), M.end(), [&](std::vector<MatrixNode> & MLine){
		TmpValue = *std::min_element(MLine.begin(), MLine.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){
			return lhs.value < rhs.value;
		});//�ҳ�ÿ����Сֵ
		std::for_each(MLine.begin(), MLine.end(), [&](MatrixNode& Nod){
			Nod.value =( Nod.value == MAX ? MAX : Nod.value-TmpValue.value);//ÿ�м�ȥ��Сֵ
		});
	});

	std::cout << "��ȥÿ����Сֵ����" << std::endl;
	show(M);

	//ÿ�м�ȥ��С
	for (i = 0; i < M[0].size(); ++i)//ÿһ��
	{
		TmpValue = M[0][i];
		for (j = 0; j < M.size(); ++j)
		{
			if (M[j][i].value < TmpValue.value)
				TmpValue = M[j][i];//�ҳ���Сֵ
		}

		for (j = 0; j < M.size(); ++j)
			M[j][i].value =( M[j][i].value == MAX ? MAX : M[j][i].value-TmpValue.value);//��ȥ��Сֵ
	}

	std::cout << "��ȥÿ����Сֵ����" << std::endl;
	show(M);
	
// ��ֻ�е���Ԫ��ʱ������ȷ���㷣��
// ����ÿ�з���
	std::vector<MatrixNode> TmpM;//��ʱ������/��
	for (i = 0; i < M.size(); ++i)
	{
		TmpM.assign(M[i].begin(),M[i].end());
		std::sort(TmpM.begin(), TmpM.end(), [](const MatrixNode& lhs, const MatrixNode& rhs){ return lhs.value < rhs.value; });
		A[i] = TmpM[1].value - TmpM[0].value;
	}
	//����ÿ�з���
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
	//��ZeroQueue
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
//���Ϸ���
bool Check(std::vector<MatrixNode> U,//���е��¼����
	std::vector<std::vector<MatrixNode>>& Matrix, //ԭʼ����M      ��ȡ��С
	MatrixNode&	CheckNode    //���������
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
	std::vector<UINT> T;//ͳ�ƽڵ���ִ������飺�������  ��·��飺���ǰ���+��Ӻ���
	MatrixNode  StartNode, tmpNode;
	UINT i(0), j(0);//ѭ������
	bool flag(0);//�ҵ���־1 / ����ȡ��·��0


	for (i = 0; i < U.size(); ++i)//X�������
	{
		if (U.at(i).X==CheckNode.X)
		{
			return false;
		}
	}
	for (i = 0; i < U.size(); ++i)//Y�������
	{
		if (U.at(i).Y == CheckNode.Y)
		{
			return false;
		}
	}

	for (i = 0; i < U.size();++i)//����µ�ǰ���
	{
		std::vector<UINT>swtmp(Matrix.size(), 0);
		T.swap(swtmp);//���T
		StartNode = U.at(i);
		++T.at(StartNode.X);
		++T.at(StartNode.Y);
		tmpNode = StartNode;
		
		while (1)//���Ե�ǰstart��·��
		{
			flag = 0;
			for (j = 0; j < U.size();++j)
			{
				if (U.at(j).X == tmpNode.Y && U.at(j).X!=StartNode.X)//����һ���� �Ҳ����ǳ�����
				{
					tmpNode = U.at(j);
					flag = true;//�ҵ�����һ��
					break;
				}
			}
			if (!flag)//��û����һ����
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
					flag = 1;//�ҵ�1
				}
				if (T.at(j) == 2)
				{
					++NodeNum;//���Ͻڵ����
				}
			}
			if (!flag)//��û�ҵ�1
			{
				if (NodeNum == Matrix.size())//���γ������Ļ����Ұ������еĵ� �򷵻ؿ������
				{
					return true;
				}
				return false;
			}
		}
	}
	U.push_back(CheckNode);//����µ����
	for (i = 0; i < U.size(); ++i)
	{
		std::vector<UINT>swtmp(Matrix.size(), 0);
		T.swap(swtmp);//���T
		StartNode = U.at(i);
		++T.at(StartNode.X);
		++T.at(StartNode.Y);
		tmpNode = StartNode;

		while (1)//���Ե�ǰstart��·��
		{
			flag = 0;
			for (j = 0; j < U.size(); ++j)
			{
				if ((U.at(j).X == tmpNode.Y) && (U.at(j).X != StartNode.X))
				{
					tmpNode = U.at(j);
					flag = true;//�ҵ�����һ��
					break;
				}
			}
			if (!flag)//��û����һ����
			{
				break;
			}
			++T.at(tmpNode.X);
			++T.at(tmpNode.Y);
		}

		//����µ�� �Ƿ��л�·
			flag = 0;
			for (j = 0; j < T.size(); ++j)
			{
				if (T.at(j) == 1)
				{
					flag = 1;//�ҵ�1
				}
			}
			if (!flag)//��û�ҵ�1
			{
				return false;
			}
	}
	return true;


}

//�ݹ麯��
void Call(std::vector<std::vector<MatrixNode>>& Matrix,//ԭʼ����
	std::vector<std::vector<MatrixNode>>& M,//ʹ�þ���
	std::vector<MatrixNode>& U,//���е��¼������
	std::vector< UINT >& R,		//����ǰ�к�
	std::vector< UINT >& L,	//����ǰ�к�
	std::vector< UINT >& afa,   //�м�¼
	std::vector< UINT >& bta,	//�м�¼
	std::vector<MatrixNode>&  Re//���
	)
{
	MatrixNode_QUEUE ZeroQueue;//��Ԫ�����ȶ���
	std::vector< UINT > A;		//�з���
	std::vector< UINT > B;		//�з���
	
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

	UpdateVar(M,  //��ʱ����M      
				ZeroQueue,//��Ԫ�����ȶ���
				afa,     //�м�¼
				bta,	//�м�¼
				A,		//�з���
				B		//�з���
				);

	if (ZeroQueue.size()==0)
	{
		U.clear();//�޽�
		return;
	}

/*	show(M);*/
	std::vector<MatrixNode> TmpU;//���е��¼��ǰ����  �������еĵ��ڵݹ�ǰ����ΪMAX ����������ȶ���
	std::vector<UINT> Roade;//�洢·��
	MatrixNode NewNode, StartNode;//��ʱ�ڵ�
	UINT i(0), j(0),k(0);//ѭ������
	bool flag(1),flag1(0);//

	while (!ZeroQueue.empty())
	{
		NewNode = ZeroQueue.top();
		if (Check(TmpU, Matrix, NewNode))
		{
			NewNode = ZeroQueue.top();
			NewNode.star = 1;
			TmpU.push_back(NewNode);
			Matrix.at(NewNode.X).at(NewNode.Y).star = 1;//���* Ϊ1
		}
		ZeroQueue.pop();
	}
	U.insert(U.end(), TmpU.begin(), TmpU.end());//��ǰTmpU ��ӵ��ܵ�U
	if (U.size() == Matrix.size())
	{
		return;
	}
	//��U���Ƶ�TmpU  ��ȡ����·��ֱ��TmpU*��־ȫΪ0
	TmpU.assign(U.begin(), U.end());//��ʱTmpU�� *���Ϊ1  ��ʱ*�����ڱ����Ƿ��Ѿ���ȡ��·����:0�� �Ѿ���ȡ 1�� û����ȡ
	Roade.clear();
	while (flag) 
	{
		flag = 0;//0��û�ҵ����
		flag1 = 1;//1���ҵ�����һ��·����
		//�����
		for (i = 0; i < TmpU.size();++i)
		{
			if (TmpU.at(i).star == 1 )//* ��1��û����ȡ
			{
				flag = 1;            
				StartNode = TmpU.at(i);
				NewNode = StartNode;
				TmpU.at(i).star = 0;
				break;
			}
		}
		while (flag1 && flag)//��������һ·����
		{
			Roade.push_back(NewNode.X);//�洢·���㵽 Roade
			//Roade.push_back(NewNode.Y);//�洢·���㵽 Roade
			flag1 = 0;//û�ҵ���һ·����
			for (i = 0; i < TmpU.size();++i)
			{
				if (TmpU.at(i).star == 1 && TmpU.at(i).X == NewNode.Y && TmpU.at(i).X != StartNode.X )  //û����ȡ����ѡ��һ��
				{
					TmpU.at(i).star = 0;
					NewNode = TmpU.at(i);//�ҵ���һ��·����
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
	for (i = 0; i < Roade.size();++i)//����·�� ����R
	{
		R.at(i) = Roade.at(i);
		R.at(Roade.at(i)) = i;
	}

	for (i = 0; i < U.size();++i) //����U R ����L
	{
		//k = 0;
		for (j = 0; j < R.size();++j)
		{
			if (R.at(j) == U.at(i).X)
			{
				k = j;//U��Ԫ�أ�M,N��M��R��λ�� K
				break;
			}
		}
		L.at(k) = U.at(i).Y;
		L.at(U.at(i).Y) = k;
	}

	//����R L ����¾���
	for (i = 0; i < Matrix.size();++i)
	{
		if (Matrix.at(R.at(i)).at(L.at(i)).star ==1)//Matrix(R L) *Ϊ1�� 
		{
			afa.at(R.at(i)) = 0;
			bta.at(L.at(i)) = 0;
		}
	}

	//����M
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
		return; ///////////������
	}



	for (i = 0; i < M.size();++i)
	{
		for (j = 0; j < M.front().size();++j)
		{
			if (!Check(U, Matrix, M.at(i).at(j)))
				M.at(i).at(j).value = MAX;
		}
	}
	for (i = 0; i < M.front().size();++i)//������˳�� ʹ��MAX�ڶԽ�����
	{
		k = 0;//��¼��ǰ�е�max����
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
	
	Call(Matrix,//ԭʼ����
		M,//ʹ�þ���
		U,//���е��¼����
		R,//����ǰ�к�
		L,//����ǰ�к�
		afa,//�м�¼
		bta,//�м�¼
		Re//���
		);

}