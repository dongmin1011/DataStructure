/*
	작성일: 2021.04.14
	학번: 20184612
	작성자: 김동민
	프로그램명: 파일 데이터를 입력받아 2중포인터 동적할당하고 
				행렬의 연산수행을 출력하는 프로그램
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void Mul_Matrix(int **, int **,int **, int, int, int);			//행렬의 곱	  int **첫번째 행렬, int ** 두번째행렬,int **결과 행렬, int 첫행렬의 행, int 두번째행렬의 열,// int 첫행렬의 열==두번째행렬의 행->곱에서만 필요
void Plus_Matrix(int **, int **,int **, int, int);				//행렬의 합
void Sub_Matrix(int **, int **,int **, int, int);				//행렬의 차
void Matrix_Print(int **, int , int);							//행렬 출력
void Matrix_free(int **, int);

int main(){
	FILE *fp;
	int m_row, m_col;											//첫번째 행렬의 행, 열
	int **M_matrix;												//첫번째 행렬 2중 포인터
	int n_row, n_col;											//두번째 행렬의 행, 열
	int **N_matrix;												//두번째 행렬 2중 포인터
	int i,j;													//for문 돌릴 변수
	int **res_matrix;											//결과 행렬
	int g=0;													//결과 행렬을 동적할당 하지 않았을 때 사용

	fp=fopen("data.txt", "r");
	if(fp == NULL){
		printf("파일이 열리지 않았습니다.\n");
		return 0;
	}
	fscanf(fp, "%d%d", &m_row, &m_col);					//첫번째 행렬의 행(m_row)과 열(m_col)값을 입력받음
	M_matrix = (int **)malloc(sizeof(int*)*m_row);		//첫번째 행렬 동적할당
	for(i=0; i<m_row; i++){
		M_matrix[i] = (int *)malloc(sizeof(int)*m_col);
	}

	for(i=0; i<m_row; i++){								//이중 for문을 행과 열값만큼 돌려 첫번째 행렬의 값을 data로부터 입력
		for(j=0; j<m_col; j++){
			fscanf(fp,"%d",&M_matrix[i][j]);
		}
	}

	fscanf(fp, "%d%d", &n_row, &n_col);					//두번째 행렬의 행(n_row)과 열(n_col)값을 입력받음
	N_matrix = (int **)malloc(sizeof(int*)*n_row);		//두번째 행렬 동적할당
	for(i=0; i<n_row; i++){
		N_matrix[i] = (int *)malloc(sizeof(int)*n_col);
	}
	for(i=0; i<n_row; i++){								//이중 for문을 행과 열값만큼 돌려 두번째 행렬의 값을 data로부터 입력
		for(j=0; j<n_col; j++){
			fscanf(fp,"%d",&N_matrix[i][j]);
		}
	}
	fclose(fp);				//파일 닫기

	printf("행렬1>>%d x %d\n",m_row, m_col);								//첫번째 행렬 출력
	Matrix_Print(M_matrix, m_row, m_col);
	
	printf("행렬2>>%d x %d\n",n_row, n_col);								//두번째 행렬 출력
	Matrix_Print(N_matrix, n_row, n_col);

	if(((m_row==n_row)&&(m_col==n_col))||(m_col==n_row)){						//결과행렬은 합, 차 곱이 가능할때만 동적할당 하고 가능하지 않을때는 동적할당을 하지 않음(메모리 낭비 방지)
		res_matrix = (int **)malloc(sizeof(int*)*m_row);							//결과 행렬의 행값은 1번행렬의 행값, 열값은 2번행렬의 열값으로 동적할당
			for(i=0; i<m_row; i++){
				res_matrix[i] = (int *)malloc(sizeof(int)*n_col);
		}
		g=1;
	}
	if(((m_row==n_row)&&(m_col==n_col))&&(m_col==n_row)){							//행과 열의 수가 m으로 같은 정방행렬일때 (m*m)(m*m)  = 모두 계산 가능
		Plus_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);				//행렬의 합계산 -> 매개변수 1.1번행렬, 2.2번행렬, 3.결과행렬, 4.1번행렬 행값, 5.2번행렬 열값
		Sub_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);					//행렬의 차계산														
		Mul_Matrix(M_matrix, N_matrix,res_matrix, m_row, n_col, m_col);		//행렬의 곱계산
	}


	else if((m_row==n_row)&&(m_col==n_col)){									//1번행렬 행과 2번행렬의 행의 값이 같고, 1번행렬 열과 2번행렬의 열의 값을 때 (m*n)(m*n)->덧셈, 뺄셈가능					
		
		Plus_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);				//행렬의 합계산 -> 매개변수 1.1번행렬, 2.2번행렬, 3.결과행렬, 4.1번행렬 행값, 5.2번행렬 열값
		Sub_Matrix(M_matrix,N_matrix,res_matrix, m_row, n_col);					//행렬의 차계산
		printf("행렬의 곱은 계산 불가\n");
	}
	else if(m_col==n_row){														//1번행렬 열과 2번행렬 행의 값이 같을 때 (m*n)(n*p) -> 곱셈가능(합,차 불가) = (m*p)행렬
		
		printf("행렬의 합과 차는 계산불가\n");									//m!=n, n!=p이므로 합,차 계산불가
		Mul_Matrix(M_matrix, N_matrix,res_matrix, m_row, n_col, m_col);			//행렬의 곱계산 -> 매개변수 1.1번행렬, 2.2번행렬, 3.결과행렬, 4.1번행렬 행값, 5.2번행렬 열값, 6.1번행렬의 열값(곱에서 필요)
	
	}
	else{
		printf("행렬의 합,차,곱 모두 계산불가\n");								//모든 조건을 만족하지 못하면 합,차, 곱 모두 계산불가			
		g=0;																	//g의 값을 1로설정
	}

	Matrix_free(M_matrix, m_row);												//1번행렬 동적할당 해제
	Matrix_free(N_matrix, n_row);												//2번행렬 동적할당 해제																	
	if(g==1) Matrix_free(res_matrix, m_row);									//g의 값을 결과값 동적할당에서 1으로 설정. 만약 합,차,곱이 모두 불가능 했을땐 결과값을 동적할당하지 않았으므로 g==0이 됨.그래서 free필요 x			
	return 0;
}

void Plus_Matrix(int **a, int **b,int **res, int row, int col){					//이중포인터가 전달인자로 넘어오므로 매개변수로 이중포인터변수를 선언한다.
	int i,j;
		for(i=0; i<row; i++){													//입력받은 행과 열만큼 for문으로 합 계산
			for(j=0; j<col; j++){
				res[i][j] = a[i][j] + b[i][j];
			}
		}
		printf("행렬의 합>>%d x %d\n",row, col);
		Matrix_Print(res, row, col);											//행렬값 출력
}
void Sub_Matrix(int **a, int **b,int **res, int row, int col){
	int i,j;
	printf("행렬의 차>>%d x %d\n",row, col);
	for(i=0; i<row; i++){													//입력받은 행과 열만큼 for문으로 차 계산
		for(j=0; j<col; j++){
			res[i][j] = a[i][j] - b[i][j];
		}
	}
	Matrix_Print(res, row, col);
}
void Mul_Matrix(int **a, int **b,int **res, int row, int col, int m_col){
	int i,j;
	int k;
	printf("행렬의 곱>>%d x %d\n",row, col);
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			res[i][j] = 0;													//결과 행렬 현재값을 0으로 설정
			for(k=0; k<m_col; k++){
				res[i][j] += a[i][k]*b[k][j];								//k를 1번행렬의 열값(2번행렬의 행값)만큼 for문을 돌리며 (1번행렬의 열*2번행렬의 행)을 더하며 결과행렬에 저장
			}
		}
	}
	Matrix_Print(res, row, col);
}
void Matrix_Print(int **matrix, int row, int col){
	int i, j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			printf("%3d  ", matrix[i][j]);										//행렬값 출력
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


