/*
	작성일: 2021.04.20
	학번: 20184612
	작성자: 김동민
	프로그램명: 2중포인터 동적할당하고 파일로부터 희소행렬을 입력받아 
				행렬의 연산수행과 전치행렬을 출력하는 프로그램
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void Matrix_Print(int **, int, int);								//출력함수 
void Sort_Matrix(int **, int);										//정렬함수 
void Trans_Matrix(int **, int, int*, int*);							//전치함수 
void Free_Matrix(int **, int);										//메모리 동적할당 해제함수 
void CAL_Matrix(int **, int **, int **, int, int, int, int);		//덧셈과 뺄셈 함수	
//void SUB_Matrix(int **, int **, int **, int, int, int);
void MUL_Matrix(int **, int **, int **, int, int, int);				//곱셈함수 
void ADD(int **,int**,int***,int,int, int);							//덧셈할때 필요한 함수들의 모음 
void SUB(int **,int**,int***,int,int, int);							//뺄셈 할때 필요한 함수들의 모음 
void MUL(int **,int**,int***,int,int, int);							//곱셈 할때 필요한 함수들의 모음
void attach(int *, int,int,int);									//결과행렬에 값을 전달하는 함수 
int GET_sparse(int **,int**,int,int, int);							//덧셈, 뺄셈행렬의 행을 반환하는 함수 
int MUL_sparse(int **,int**,int,int);								//곱셈행렬의 행을 반환하는 함수 
int **memory_allocation(int);										//동적할당을 반환하는 함수 

int main(){
	FILE *fp;														
	int tmp;	
	int a_row,a_col, b_row, b_col, res_row,res_col;					//full matrix의 행,열 
	char a_name, b_name, temp;										//행렬의 이름 
	int a_sparse=0, b_sparse=0;										//희소행렬의 행 
	int i, j;			
	int **A_matrix, **B_matrix;										//a희소행렬, b희소행렬 
	int **res_matrix, res_sparse=0;									//결과희소행렬과 결과 희소행렬의 행 

	fp=fopen("data.txt","r");
	if(fp==NULL){
		printf("파일이 열리지 않았습니다.\n");
		return 0;
	}
	fscanf(fp,"%c%d%d",&temp, &tmp, &tmp);							//A 행 열 입력(임시변수) 
	while(!feof(fp)){										
		fscanf(fp,"%d%d%d",&tmp, &tmp, &tmp);
		fscanf(fp, "%c",&temp);
		if(temp=='B')break;											//만약 temp가 B면 종료 
		a_sparse++;													//a희소행렬의 값++ 
	}
	fscanf(fp,"%d%d", &tmp, &tmp);									//b는 입력받음 >> 행과 열값만 임시변수에 
	
	while(!feof(fp)){												//data의 끝까지 반복 
		fscanf(fp,"%d%d%d",&tmp, &tmp, &tmp);			
		b_sparse++;													//b희소행렬의 값++ 
	}
	A_matrix = memory_allocation(a_sparse);							//a,b행렬 동적할당 
	B_matrix = memory_allocation(b_sparse);
	rewind(fp);														//첫값으로 되돌림 
	
	fscanf(fp,"%c%d%d",&a_name, &a_row, &a_col);					//행렬의 이름, 행렬의 행, 행렬의 열 
	for(i=0; i<a_sparse; i++){
		for(j=0; j<3; j++){
			fscanf(fp,"%d",&A_matrix[i][j]);						//a희소행렬을 data로부터 입력		
		}
	}
	fscanf(fp, "%c",&temp);											//'\n'값 패스 
	fscanf(fp,"%c%d%d",&b_name, &b_row, &b_col);					//행렬의 이름, 행렬의 행, 행렬의 열 
	
	for(i=0; i<b_sparse; i++){
		for(j=0; j<3; j++){
			fscanf(fp,"%d",&B_matrix[i][j]);						//b희소행렬을 data로부터 입력
		}	
	}
	fclose(fp);														//파일 닫음 

	printf("%c 행렬 = %d x %d\n", a_name, a_row, a_col);
	Matrix_Print(A_matrix, a_sparse, 3);							//a 희소행렬 출력 

	printf("%c 행렬 = %d x %d\n", b_name, b_row, b_col);
	Matrix_Print(B_matrix, b_sparse, 3);

	res_row = a_row;															//만약 덧셈시 (m*n)+(m*n) = m*n행렬 
	res_col = b_col;															//만약 곱셈시 (m*n)x(n*p) = m*p행렬 
																				//앞행렬의 행 * 뒤행렬의 열임을 알 수 있음 

	if((a_row==b_row)&&(a_col==b_col)&&(a_col==b_row)){												//m*m의 정방행렬일 경우 ->합,차,곱 모두 가능
		printf("행렬의 합 = %d x %d\n",res_row, res_col  );
		ADD(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);	
		printf("행렬의 차 = %d x %d\n",res_row, res_col  );
		SUB(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
		printf("행렬의 곱 = %d x %d\n", res_row, res_col);
		MUL(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
	}
	else if((a_row==b_row)&&(a_col==b_col)){														//(m*n)+(m*n)행렬일 경우 -> 합, 차만 가능 곱은 불가
		printf("행렬의 합 = %d x %d\n",res_row, res_col  );
		ADD(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);	
		printf("행렬의 차 = %d x %d\n",res_row, res_col  );
		SUB(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
		printf("행렬의 곱셈은 계산 불가\n");

	}
	else if(a_col==b_row){																			//(m*n)*(n*p)행렬일 경우 -> 곱만 가능 합,차는 불가
		printf("행렬의 곱 = %d x %d\n", res_row, res_col);
		MUL(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
		printf("행렬의 덧셈, 뺄셈은 계산 불가\n");
	}
	else{																							//나머지는 모두 계산 불가
		printf("행렬의 덧셈, 뺄셈, 곱셈 모두 계산 불가\n");
	}
	printf("\n");
	
	Trans_Matrix(A_matrix, a_sparse, &a_row, &a_col);				//전치행렬(a희소행렬, 행값, 원래행의 주소, 원래 열의 주소)=>행과 열이 뒤바뀜 
	printf("%c의 전치>>%d x %d\n",a_name,a_row, a_col);
	Matrix_Print(A_matrix, a_sparse, 3);							//행렬 출력(전치확인) 

	Trans_Matrix(B_matrix, b_sparse, &b_row, &b_col);
	printf("%c의 전치>>%d x %d\n",b_name,b_row, b_col);
	Matrix_Print(B_matrix, b_sparse, 3);

	Free_Matrix(A_matrix, a_sparse);								//메모리 동적할당 해제 
	Free_Matrix(B_matrix, b_sparse);

	return 0;
}
void ADD(int **a, int **b,int ***res_matrix, int a_sparse, int b_sparse, int res_sparse){	//매개변수(a희소, b희소, 결과희소의 주소(3중포인터),a희소 행, b희소 행, 결과 희소 행) 
	
	res_sparse = GET_sparse( a, b, a_sparse, b_sparse, 1);							//행의 값 계산후 반환받음(덧셈일땐 마지막값1) 
	*res_matrix = memory_allocation(res_sparse);									//결과 행렬 동적할당(res_matrix의 값에 반환) 
	CAL_Matrix(a, b, *res_matrix, a_sparse, b_sparse, res_sparse,1);				//덧셈행렬 계산(덧셈일땐 마지막값 1) 
	Matrix_Print(*res_matrix, res_sparse, 3);										
	Free_Matrix(*res_matrix, res_sparse);											//결과 행렬 출력 후 동적할당 해제 
}
void SUB(int **a, int **b,int ***res_matrix, int a_sparse, int b_sparse, int res_sparse){
	
	res_sparse = GET_sparse( a, b, a_sparse, b_sparse,2);							//행의 값 계산후 반환받음(뺄셈일땐 마지막값2) 
	*res_matrix = memory_allocation(res_sparse);
	//SUB_Matrix(a, b, res_matrix, a_sparse, b_sparse, res_sparse);
	CAL_Matrix(a, b, *res_matrix, a_sparse, b_sparse, res_sparse,2);				//뺄셈행렬 계산(뺄셈일땐 마지막값 2) 
	Matrix_Print(*res_matrix, res_sparse, 3);
	Free_Matrix(*res_matrix, res_sparse);
}
void MUL(int **a, int **b,int ***res_matrix, int a_sparse, int b_sparse, int res_sparse){
	res_sparse = MUL_sparse( a, b, a_sparse, b_sparse);
	*res_matrix = memory_allocation(res_sparse);
	MUL_Matrix(a, b, *res_matrix, a_sparse, b_sparse, res_sparse);
	Matrix_Print(*res_matrix, res_sparse, 3);
	Free_Matrix(*res_matrix, res_sparse);
}

int GET_sparse(int **a,int**b,int a_sparse,int b_sparse, int flag){
	int i,j;
	int temp =  a_sparse + b_sparse;
	for(i=0;i<a_sparse; i++){
		for(j=0; j<b_sparse; j++){
			if((a[i][0]==b[j][0])&&(a[i][1]==b[j][1])){								//a행렬과 b행렬의 위치가 같을때 
				if(flag==1&&(a[i][2]+b[j][2])==0) temp-=2;							//flag값이 1일때(행렬의 합 연산)
				else if(flag==2&&(a[i][2]-b[j][2])==0) temp-=2;						//flag값이 2일때(행렬의 차 연산)
				else temp--;
			}
		}
	}
	return temp;																	//희소행렬의 행반환
}

int MUL_sparse(int **a, int**b, int a_sparse, int b_sparse){
	int i,j,s;
	int temp = 0, count=0;
	int **ary;
	for(i=0; i<a_sparse; i++){
		for(j=0; j<b_sparse; j++){
			if(a[i][1]==b[j][0]){
				temp++;
			}		
		}
	}
	ary = memory_allocation(temp);
	
	for(i=0; i<a_sparse; i++){
		for(j=0; j<b_sparse; j++){
			if(a[i][1]==b[j][0]){
				for(s=0; s<count; s++){
					if(ary[s][0]==a[i][0]&&ary[s][1]==b[j][1]){
						ary[s][2]+=a[i][2]*b[j][2];
						
						break;
					}
				}
				if(s==count){	
					ary[count][0]=a[i][0];
					ary[count][1]=b[j][1];
					ary[count][2]=a[i][2]*b[j][2];
					count++;
				}
			}
		}
	}
	count=0;
	for(i=0; i<temp; i++){
		if(ary[i][2]==0)count++;
	}
	Free_Matrix(ary, temp);
	temp-=count;
	return temp;
}


void MUL_Matrix(int **a, int **b, int **res, int a_row, int b_row, int res_row){
	int i,j;
	int s=0, count=0;
	int temp=0;
	int **ary;
	
	for(i=0; i<a_row; i++){
		for(j=0; j<b_row; j++){
			if(a[i][1]==b[j][0]){
				temp++;
			}		
		}
	}
	ary = memory_allocation(temp);
	for(i=0; i<a_row; i++){
		for(j=0; j<b_row; j++){
			if(a[i][1]==b[j][0]){
				for(s=0; s<count; s++){
					if(ary[s][0]==a[i][0]&&ary[s][1]==b[j][1]){
						ary[s][2]+=a[i][2]*b[j][2];
						break;
					}
				}
				if(s==count){	
					ary[count][0]=a[i][0];
					ary[count][1]=b[j][1];
					ary[count][2]=a[i][2]*b[j][2];
					count++;
				}
			}
		}
	}
	i=0;
	s=0;
	while(s<res_row){
		if(ary[i][2]!=0){
			attach(res[s],ary[i][0],ary[i][1],ary[i][2]);
			s++;			
		}
		i++;
	}
	Free_Matrix(ary, temp);
	Sort_Matrix(res, res_row);

}
void CAL_Matrix(int **a, int **b, int **res, int a_row, int b_row, int res_row, int flag){	//매개변수(a희소, b희소, 결과희소, a희소 행, b희소 행, 결과 희소 행, flag값(1일땐 덧셈, 2일땐 뺄셈)) 
	int i=0,j=0;																			//i= a행렬의 행변수,  j = b행렬의 행변수 
	int s=0;																				//결과 행렬의 행변수 
	int temp;																				//덧셈 혹은 뺄셈을 저장하는 임시변수 
	while((i<a_row)&&(j<b_row)){			 
			
		if(a[i][0]==b[j][0]){																//a행렬의 행과 b행렬의 행이 같을때
			if(a[i][1]>b[j][1]){															//a행렬 열보다 b행렬 열이 더 작을 때 -> b행렬이 더 앞에 있음
				if(flag==1) temp = b[j][2];													//1일 땐 덧셈이므로 그냥 b값 대입, 2일땐 뺄셈이므로 -b값 대입
				else if(flag==2) temp = -b[j][2]; 
				attach(res[s], b[j][0],b[j][1],temp);										//결과행렬에 대입
				s++;
				j++;
			}
			else if(a[i][1]==b[j][1]){														//a행렬의 행,열과 b행렬의 행,열이 모두 같을 때
				if(flag==1&&a[i][2]+b[j][2]!=0){											//flag값이 1이고 더했을때 0이 아닐때 덧셈수행 
					temp=a[i][2]+b[j][2];
					attach(res[s], a[i][0],b[j][1],temp);									//결과 행렬에 저장 
					s++;
					i++;
					j++;					
				}
				else if(flag==2&&a[i][2]-b[j][2]!=0){										//flag값이 2이고 뺐을때 0이 아닐때 뺄셈 수행 
					temp=a[i][2]-b[j][2];
					attach(res[s], a[i][0],b[j][1],temp);
					s++;
					i++;
					j++;
				}
				else{																		//행렬의 합 또는 차가 0이므로 결과행렬에 할당하지 않음.
					i++;
					j++;
				}	
			}
			else{																			//a행렬 열보다 b행렬 열이 더 클 때 -> a행렬이 더 앞에 있음
				attach(res[s], a[i][0],a[i][1],a[i][2]);									//a행렬 결과행렬에 대입
				s++;
				i++;	
			}
		}
		else if(a[i][0]<b[j][0]){															//a행렬의 행이 더 작을때 ->a행렬이 더 앞에 있음. a행렬 대입
			attach(res[s], a[i][0],a[i][1],a[i][2]);						
			s++;
			i++;	
		}
		else{																				//a행렬의 행이 더 클때 ->b행렬이 더 앞에 있음 b행렬 대입
			if(flag==1) temp = b[j][2]; 													//1일 땐 덧셈이므로 그냥 b값 대입, 2일땐 뺄셈이므로 -b값 대입
			else if(flag==2) temp = -b[j][2]; 
			attach(res[s], b[j][0],b[j][1],temp);
			s++;
			j++;	
			
		}
	
	}
	while(i<a_row){																			//a의 나머지 항들을 이동
		attach(res[s], a[i][0],a[i][1],a[i][2]);
		s++;
		i++;
	}
	while(j<b_row){																			//b의 나머지 항들을 이동
		if(flag==1) temp = b[j][2]; 
		else if(flag==2) temp = -b[j][2];  													//1일 땐 덧셈이므로 그냥 b값 대입, 2일땐 뺄셈이므로 -b값 대입
		attach(res[s], b[j][0],b[j][1],temp);
		s++;
		j++;
	}
}
/*
void SUB_Matrix(int **a, int **b, int **res, int a_row, int b_row, int res_row){
	int i=0,j=0;
	int s=0;
	int temp;
	while(i<a_row&&j<b_row){
		

		switch(Compare(a[i][0],b[j][0])){
		case'=':
			if(a[i][1]>b[j][1]){
				attach(res[s], b[j][0],b[j][1],-b[j][2]);
				s++;
				j++;
			}
			else if(a[i][1]==b[j][1]){
				temp=a[i][2]-b[j][2];
				if(temp){
					attach(res[s], a[i][0],a[i][1],temp);
					s++;
					i++;
					j++;
				}
				else{
					i++;
					j++;
				}		
			}
			else{
				attach(res[s], a[i][0],a[i][1],a[i][2]);
				s++;
				i++;	
			}
			break;
		case'<':
			attach(res[s], a[i][0],a[i][1],a[i][2]);
			s++;
			i++;	
			break;
		case '>':
			attach(res[s], b[j][0],b[j][1],-b[j][2]);
			s++;
			j++;	
			break;
		}
	}
	while(i<a_row){
		attach(res[s], a[i][0],a[i][1],a[i][2]);
		s++; i++;
	}
	while(j<b_row){
		attach(res[s], b[j][0],b[j][1],-b[j][2]);
		s++;
	}
}*/

void attach(int *s, int a, int b, int c){
	s[0]=a;																					//s는 결과행렬, s[0]값에 a, s[1]값에 b, s[2]값에 c대입
	s[1]=b;
	s[2]=c;
}

int **memory_allocation(int sparse){														//동적할당 함수(매개변수-희소행렬의 행)
	int i,j;
	int **a;
	if(sparse<0){																			//만약 매개변수 희소행렬의 행이 0보다 작으면 동적할당 불가
		printf("메모리가 존재하지 않습니다.\n");
		return 0;
	}
	
	a = (int **)malloc(sizeof(int*)*sparse);												//이중포인터 a를 희소행렬의 행으로 동적할당
	for(i=0; i<sparse; i++){																//희소행렬의 열값은 3이므로 for문을 돌며 a[i]를 3으로 동적할당
		a[i] = (int*)malloc(sizeof(int)*3);
		for(j=0; j<3; j++){																	//동적할당과 함께 0으로 초기화
			a[i][j]=0;
		}
	}
	return a;																				//동적할당한 이중포인터 a를 반환
}

void Sort_Matrix(int **matrix, int row){													//정렬함수(매개변수 - 희소행렬, 희소행렬의 행값)
	int i,r,tmp,k;
	for(i=0; i<row; i++){
		for(r=0; r<row; r++){
			if(matrix[i][0]<matrix[r][0]){													//만약 현재 행렬의 행값보다 뒤에 있는 행렬이 더 크다면 정렬
				for(k=0; k<3; k++){
					tmp=matrix[i][k];
					matrix[i][k] = matrix[r][k];
					matrix[r][k]=tmp;
				}		
			}
			if((matrix[i][0]==matrix[r][0]) && (matrix[i][1]<matrix[r][1]) ){				//정렬을 모두 마친 후 행렬의 열에 대하여 정렬, 만약 행값이 같고 열값이 뒤가 더 크다면 다시 정렬
				for(k=0; k<3; k++){
					tmp=matrix[i][k];
					matrix[i][k] = matrix[r][k];
					matrix[r][k]=tmp;
				}
			}
		}	
	}
}
void Trans_Matrix(int **matrix, int sparse_row, int* row, int *col){						//전치 함수(매개변수 - 희소행렬, 희소행렬의 행값, full-matrix의 행과 열의 주소)
	int i, tmp;
	tmp = *row;																				//full-matrix행 열값을 전치
	*row = *col;
	*col = tmp;

	for(i=0; i<sparse_row; i++){															//희소행렬의 행, 열값을 전치
		tmp=matrix[i][1];
		matrix[i][1] = matrix[i][0];
		matrix[i][0]=tmp;
	}
	Sort_Matrix(matrix, sparse_row);														//전치행렬을 정렬 -> 정렬함수
}

void Matrix_Print(int **matrix, int row, int col){											//출력함수(매개변수-희소 행렬, 희소행렬의 행, 열값) 
	int i,j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			if(j==2) printf(" :");															//j가 2일때 :를 출력하여 위치와 데이터 구분
			printf("%3d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void Free_Matrix(int **matrix, int row){													//메모리 동적할당 해제 함수(매개변수 - 희소행렬, 희소행렬 행값)
	int i;
	for(i=0; i<row; i++){																	//행만큼 for문을 돌며 free
		free(matrix[i]);
	}
	free(matrix);																			//행값 free
}
