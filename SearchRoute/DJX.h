#include "DataType.h"
#include <vector>
#include <iostream>
void DJX(std::vector<std::vector<MatrixNode>>& Matrix, std::vector<MatrixNode>& Re);
void show(std::vector<std::vector<MatrixNode>>& M);
//�ݹ麯��
void Call(std::vector<std::vector<MatrixNode>>& Matrix,//ԭʼ����
		  std::vector<std::vector<MatrixNode>>& M,//ʹ�þ���
		  std::vector<MatrixNode>& U,//���е��¼����
		  std::vector< UINT >& R,		//����ǰ�к�
		  std::vector< UINT >& L,	//����ǰ�к�
		  std::vector< UINT >& afa,   //�м�¼
		  std::vector< UINT >& bta,	//�м�¼
		  std::vector<MatrixNode>&  Re//���
			);
//���±���	
void UpdateVar(std::vector<std::vector<MatrixNode>>& M, //��ʱ����M      
			    MatrixNode_QUEUE& ZeroQueue,//��Ԫ�����ȶ���
				std::vector< UINT >& afa,   //�м�¼
				std::vector< UINT >& bta,	//�м�¼
				std::vector< UINT >& A,		//�з���
				std::vector< UINT >& B		//�з���

				);  
//���Ϸ���
bool Check(std::vector<MatrixNode> U,//���е��¼����
			std::vector<std::vector<MatrixNode>>& Matrix, //��ʱ����M :��ȡ�����С     
			MatrixNode&	CheckNode    //���������
	);

