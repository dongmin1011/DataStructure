/*
	�ۼ���: 2021.04.14
	�й�: 20184612
	�ۼ���: �赿��
	���α׷���: ���� �����͸� �Է¹޾� 2�������� �����Ҵ��ϰ� 
				����� ��������� ����ϴ� ���α׷�
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void Mul_Matrix(int **, int **,int **, int, int, int);			//����� ��	  int **ù��° ���, int ** �ι�°���,int **��� ���, int ù����� ��, int �ι�°����� ��,// int ù����� ��==�ι�°����� ��->�������� �ʿ�
void Plus_Matrix(int **, int **,int **, int, int);				//����� ��
void Sub_Matrix(int **, int **,int **, int, int);				//����� ��
void Matrix_Print(int **, int , int);							//��� ���
void Matrix_free(int **, int);

int main(){
	FILE *fp;
	int m_row, m_col;											//ù��° ����� ��, ��
	int **M_matrix;												//ù��° ��� 2�� ������
	int n_row, n_col;											//�ι�° ����� ��, ��
	int **N_matrix;												//�ι�° ��� 2�� ������
	int i,j;													//for�� ���� ����
	int **res_matrix;											//��� ���
	int g=0;													//��� ����� �����Ҵ� ���� �ʾ��� �� ���

	fp=fopen("data.txt", "r");
	if(fp == NULL){
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return 0;
	}
	fscanf(fp, "%d%d", &m_row, &m_col);					//ù��° ����� ��(m_row)�� ��(m_col)���� �Է¹���
	M_matrix = (int **)malloc(sizeof(int*)*m_row);		//ù��° ��� �����Ҵ�
	for(i=0; i<m_row; i++){
		M_matrix[i] = (int *)malloc(sizeof(int)*m_col);
	}

	for(i=0; i<m_row; i++){								//���� for���� ��� ������ŭ ���� ù��° ����� ���� data�κ��� �Է�
		for(j=0; j<m_col; j++){
			fscanf(fp,"%d",&M_matrix[i][j]);
		}
	}

	fscanf(fp, "%d%d", &n_row, &n_col);					//�ι�° ����� ��(n_row)�� ��(n_col)���� �Է¹���
	N_matrix = (int **)malloc(sizeof(int*)*n_row);		//�ι�° ��� �����Ҵ�
	for(i=0; i<n_row; i++){
		N_matrix[i] = (int *)malloc(sizeof(int)*n_col);
	}
	for(i=0; i<n_row; i++){								//���� for���� ��� ������ŭ ���� �ι�° ����� ���� data�κ��� �Է�
		for(j=0; j<n_col; j++){
			fscanf(fp,"%d",&N_matrix[i][j]);
		}
	}
	fclose(fp);				//���� �ݱ�

	printf("���1>>%d x %d\n",m_row, m_col);								//ù��° ��� ���
	Matrix_Print(M_matrix, m_row, m_col);
	
	printf("���2>>%d x %d\n",n_row, n_col);								//�ι�° ��� ���
	Matrix_Print(N_matrix, n_row, n_col);

	if(((m_row==n_row)&&(m_col==n_col))||(m_col==n_row)){						//�������� ��, �� ���� �����Ҷ��� �����Ҵ� �ϰ� �������� �������� �����Ҵ��� ���� ����(�޸� ���� ����)
		res_matrix = (int **)malloc(sizeof(int*)*m_row);							//��� ����� �ప�� 1������� �ప, ������ 2������� �������� �����Ҵ�
			for(i=0; i<m_row; i++){
				res_matrix[i] = (int *)malloc(sizeof(int)*n_col);
		}
		g=1;
	}
	if(((m_row==n_row)&&(m_col==n_col))&&(m_col==n_row)){							//��� ���� ���� m���� ���� ��������϶� (m*m)(m*m)  = ��� ��� ����
		Plus_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);				//����� �հ�� -> �Ű����� 1.1�����, 2.2�����, 3.������, 4.1����� �ప, 5.2����� ����
		Sub_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);					//����� �����														
		Mul_Matrix(M_matrix, N_matrix,res_matrix, m_row, n_col, m_col);		//����� �����
	}


	else if((m_row==n_row)&&(m_col==n_col)){									//1����� ��� 2������� ���� ���� ����, 1����� ���� 2������� ���� ���� �� (m*n)(m*n)->����, ��������					
		
		Plus_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);				//����� �հ�� -> �Ű����� 1.1�����, 2.2�����, 3.������, 4.1����� �ప, 5.2����� ����
		Sub_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);					//����� �����
		printf("����� ���� ��� �Ұ�\n");
	}
	else if(m_col==n_row){														//1����� ���� 2����� ���� ���� ���� �� (m*n)(n*p) -> ��������(��,�� �Ұ�) = (m*p)���
		
		printf("����� �հ� ���� ���Ұ�\n");									//m!=n, n!=p�̹Ƿ� ��,�� ���Ұ�
		Mul_Matrix(M_matrix, N_matrix,res_matrix, m_row, n_col, m_col);			//����� ����� -> �Ű����� 1.1�����, 2.2�����, 3.������, 4.1����� �ప, 5.2����� ����, 6.1������� ����(������ �ʿ�)
	
	}
	else{
		printf("����� ��,��,�� ��� ���Ұ�\n");								//��� ������ �������� ���ϸ� ��,��, �� ��� ���Ұ�			
		g=0;																	//g�� ���� 1�μ���
	}

	Matrix_free(M_matrix, m_row);												//1����� �����Ҵ� ����
	Matrix_free(N_matrix, n_row);												//2����� �����Ҵ� ����																	
	if(g==1) Matrix_free(res_matrix, m_row);									//g�� ���� ����� �����Ҵ翡�� 1���� ����. ���� ��,��,���� ��� �Ұ��� ������ ������� �����Ҵ����� �ʾ����Ƿ� g==0�� ��.�׷��� free�ʿ� x			
	return 0;
}

void Plus_Matrix(int **a, int **b,int **res, int row, int col){					//���������Ͱ� �������ڷ� �Ѿ���Ƿ� �Ű������� ���������ͺ����� �����Ѵ�.
	int i,j;
		for(i=0; i<row; i++){													//�Է¹��� ��� ����ŭ for������ �� ���
			for(j=0; j<col; j++){
				res[i][j] = a[i][j] + b[i][j];
			}
		}
		printf("����� ��>>%d x %d\n",row, col);
		Matrix_Print(res, row, col);											//��İ� ���
}
void Sub_Matrix(int **a, int **b,int **res, int row, int col){
	int i,j;
	printf("����� ��>>%d x %d\n",row, col);
	for(i=0; i<row; i++){													//�Է¹��� ��� ����ŭ for������ �� ���
		for(j=0; j<col; j++){
			res[i][j] = a[i][j] - b[i][j];
		}
	}
	Matrix_Print(res, row, col);
}
void Mul_Matrix(int **a, int **b,int **res, int row, int col, int m_col){
	int i,j;
	int k;
	printf("����� ��>>%d x %d\n",row, col);
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			res[i][j] = 0;													//��� ��� ���簪�� 0���� ����
			for(k=0; k<m_col; k++){
				res[i][j] += a[i][k]*b[k][j];								//k�� 1������� ����(2������� �ప)��ŭ for���� ������ (1������� ��*2������� ��)�� ���ϸ� �����Ŀ� ����
			}
		}
	}
	Matrix_Print(res, row, col);
}
void Matrix_Print(int **matrix, int row, int col){
	int i, j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%3d  ", matrix[i][j]);										//��İ� ���
		}
		printf("\n");
	}
	printf("\n");
}
void Matrix_free(int **matrix, int row){
	int i;
	for(i=0; i<row; i++) free(matrix[i]);
	free(matrix);
}


