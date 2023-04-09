/*
	�ۼ���: 2021.04.20
	�й�: 20184612
	�ۼ���: �赿��
	���α׷���: 2�������� �����Ҵ��ϰ� ���Ϸκ��� �������� �Է¹޾� 
				����� �������� ��ġ����� ����ϴ� ���α׷�
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void Matrix_Print(int **, int, int);								//����Լ� 
void Sort_Matrix(int **, int);										//�����Լ� 
void Trans_Matrix(int **, int, int*, int*);							//��ġ�Լ� 
void Free_Matrix(int **, int);										//�޸� �����Ҵ� �����Լ� 
void CAL_Matrix(int **, int **, int **, int, int, int, int);		//������ ���� �Լ�	
//void SUB_Matrix(int **, int **, int **, int, int, int);
void MUL_Matrix(int **, int **, int **, int, int, int);				//�����Լ� 
void ADD(int **,int**,int***,int,int, int);							//�����Ҷ� �ʿ��� �Լ����� ���� 
void SUB(int **,int**,int***,int,int, int);							//���� �Ҷ� �ʿ��� �Լ����� ���� 
void MUL(int **,int**,int***,int,int, int);							//���� �Ҷ� �ʿ��� �Լ����� ����
void attach(int *, int,int,int);									//�����Ŀ� ���� �����ϴ� �Լ� 
int GET_sparse(int **,int**,int,int, int);							//����, ��������� ���� ��ȯ�ϴ� �Լ� 
int MUL_sparse(int **,int**,int,int);								//��������� ���� ��ȯ�ϴ� �Լ� 
int **memory_allocation(int);										//�����Ҵ��� ��ȯ�ϴ� �Լ� 

int main(){
	FILE *fp;														
	int tmp;	
	int a_row,a_col, b_row, b_col, res_row,res_col;					//full matrix�� ��,�� 
	char a_name, b_name, temp;										//����� �̸� 
	int a_sparse=0, b_sparse=0;										//�������� �� 
	int i, j;			
	int **A_matrix, **B_matrix;										//a������, b������ 
	int **res_matrix, res_sparse=0;									//��������İ� ��� �������� �� 

	fp=fopen("data.txt","r");
	if(fp==NULL){
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return 0;
	}
	fscanf(fp,"%c%d%d",&temp, &tmp, &tmp);							//A �� �� �Է�(�ӽú���) 
	while(!feof(fp)){										
		fscanf(fp,"%d%d%d",&tmp, &tmp, &tmp);
		fscanf(fp, "%c",&temp);
		if(temp=='B')break;											//���� temp�� B�� ���� 
		a_sparse++;													//a�������� ��++ 
	}
	fscanf(fp,"%d%d", &tmp, &tmp);									//b�� �Է¹��� >> ��� ������ �ӽú����� 
	
	while(!feof(fp)){												//data�� ������ �ݺ� 
		fscanf(fp,"%d%d%d",&tmp, &tmp, &tmp);			
		b_sparse++;													//b�������� ��++ 
	}
	A_matrix = memory_allocation(a_sparse);							//a,b��� �����Ҵ� 
	B_matrix = memory_allocation(b_sparse);
	rewind(fp);														//ù������ �ǵ��� 
	
	fscanf(fp,"%c%d%d",&a_name, &a_row, &a_col);					//����� �̸�, ����� ��, ����� �� 
	for(i=0; i<a_sparse; i++){
		for(j=0; j<3; j++){
			fscanf(fp,"%d",&A_matrix[i][j]);						//a�������� data�κ��� �Է�		
		}
	}
	fscanf(fp, "%c",&temp);											//'\n'�� �н� 
	fscanf(fp,"%c%d%d",&b_name, &b_row, &b_col);					//����� �̸�, ����� ��, ����� �� 
	
	for(i=0; i<b_sparse; i++){
		for(j=0; j<3; j++){
			fscanf(fp,"%d",&B_matrix[i][j]);						//b�������� data�κ��� �Է�
		}	
	}
	fclose(fp);														//���� ���� 

	printf("%c ��� = %d x %d\n", a_name, a_row, a_col);
	Matrix_Print(A_matrix, a_sparse, 3);							//a ������ ��� 

	printf("%c ��� = %d x %d\n", b_name, b_row, b_col);
	Matrix_Print(B_matrix, b_sparse, 3);

	res_row = a_row;															//���� ������ (m*n)+(m*n) = m*n��� 
	res_col = b_col;															//���� ������ (m*n)x(n*p) = m*p��� 
																				//������� �� * ������� ������ �� �� ���� 

	if((a_row==b_row)&&(a_col==b_col)&&(a_col==b_row)){												//m*m�� ��������� ��� ->��,��,�� ��� ����
		printf("����� �� = %d x %d\n",res_row, res_col  );
		ADD(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);	
		printf("����� �� = %d x %d\n",res_row, res_col  );
		SUB(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
		printf("����� �� = %d x %d\n", res_row, res_col);
		MUL(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
	}
	else if((a_row==b_row)&&(a_col==b_col)){														//(m*n)+(m*n)����� ��� -> ��, ���� ���� ���� �Ұ�
		printf("����� �� = %d x %d\n",res_row, res_col  );
		ADD(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);	
		printf("����� �� = %d x %d\n",res_row, res_col  );
		SUB(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
		printf("����� ������ ��� �Ұ�\n");

	}
	else if(a_col==b_row){																			//(m*n)*(n*p)����� ��� -> ���� ���� ��,���� �Ұ�
		printf("����� �� = %d x %d\n", res_row, res_col);
		MUL(A_matrix, B_matrix,&res_matrix, a_sparse, b_sparse, res_sparse);
		printf("����� ����, ������ ��� �Ұ�\n");
	}
	else{																							//�������� ��� ��� �Ұ�
		printf("����� ����, ����, ���� ��� ��� �Ұ�\n");
	}
	printf("\n");
	
	Trans_Matrix(A_matrix, a_sparse, &a_row, &a_col);				//��ġ���(a������, �ప, �������� �ּ�, ���� ���� �ּ�)=>��� ���� �ڹٲ� 
	printf("%c�� ��ġ>>%d x %d\n",a_name,a_row, a_col);
	Matrix_Print(A_matrix, a_sparse, 3);							//��� ���(��ġȮ��) 

	Trans_Matrix(B_matrix, b_sparse, &b_row, &b_col);
	printf("%c�� ��ġ>>%d x %d\n",b_name,b_row, b_col);
	Matrix_Print(B_matrix, b_sparse, 3);

	Free_Matrix(A_matrix, a_sparse);								//�޸� �����Ҵ� ���� 
	Free_Matrix(B_matrix, b_sparse);

	return 0;
}
void ADD(int **a, int **b,int ***res_matrix, int a_sparse, int b_sparse, int res_sparse){	//�Ű�����(a���, b���, �������� �ּ�(3��������),a��� ��, b��� ��, ��� ��� ��) 
	
	res_sparse = GET_sparse( a, b, a_sparse, b_sparse, 1);							//���� �� ����� ��ȯ����(�����϶� ��������1) 
	*res_matrix = memory_allocation(res_sparse);									//��� ��� �����Ҵ�(res_matrix�� ���� ��ȯ) 
	CAL_Matrix(a, b, *res_matrix, a_sparse, b_sparse, res_sparse,1);				//������� ���(�����϶� �������� 1) 
	Matrix_Print(*res_matrix, res_sparse, 3);										
	Free_Matrix(*res_matrix, res_sparse);											//��� ��� ��� �� �����Ҵ� ���� 
}
void SUB(int **a, int **b,int ***res_matrix, int a_sparse, int b_sparse, int res_sparse){
	
	res_sparse = GET_sparse( a, b, a_sparse, b_sparse,2);							//���� �� ����� ��ȯ����(�����϶� ��������2) 
	*res_matrix = memory_allocation(res_sparse);
	//SUB_Matrix(a, b, res_matrix, a_sparse, b_sparse, res_sparse);
	CAL_Matrix(a, b, *res_matrix, a_sparse, b_sparse, res_sparse,2);				//������� ���(�����϶� �������� 2) 
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
			if((a[i][0]==b[j][0])&&(a[i][1]==b[j][1])){								//a��İ� b����� ��ġ�� ������ 
				if(flag==1&&(a[i][2]+b[j][2])==0) temp-=2;							//flag���� 1�϶�(����� �� ����)
				else if(flag==2&&(a[i][2]-b[j][2])==0) temp-=2;						//flag���� 2�϶�(����� �� ����)
				else temp--;
			}
		}
	}
	return temp;																	//�������� ���ȯ
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
void CAL_Matrix(int **a, int **b, int **res, int a_row, int b_row, int res_row, int flag){	//�Ű�����(a���, b���, ������, a��� ��, b��� ��, ��� ��� ��, flag��(1�϶� ����, 2�϶� ����)) 
	int i=0,j=0;																			//i= a����� �ຯ��,  j = b����� �ຯ�� 
	int s=0;																				//��� ����� �ຯ�� 
	int temp;																				//���� Ȥ�� ������ �����ϴ� �ӽú��� 
	while((i<a_row)&&(j<b_row)){			 
			
		if(a[i][0]==b[j][0]){																//a����� ��� b����� ���� ������
			if(a[i][1]>b[j][1]){															//a��� ������ b��� ���� �� ���� �� -> b����� �� �տ� ����
				if(flag==1) temp = b[j][2];													//1�� �� �����̹Ƿ� �׳� b�� ����, 2�϶� �����̹Ƿ� -b�� ����
				else if(flag==2) temp = -b[j][2]; 
				attach(res[s], b[j][0],b[j][1],temp);										//�����Ŀ� ����
				s++;
				j++;
			}
			else if(a[i][1]==b[j][1]){														//a����� ��,���� b����� ��,���� ��� ���� ��
				if(flag==1&&a[i][2]+b[j][2]!=0){											//flag���� 1�̰� �������� 0�� �ƴҶ� �������� 
					temp=a[i][2]+b[j][2];
					attach(res[s], a[i][0],b[j][1],temp);									//��� ��Ŀ� ���� 
					s++;
					i++;
					j++;					
				}
				else if(flag==2&&a[i][2]-b[j][2]!=0){										//flag���� 2�̰� ������ 0�� �ƴҶ� ���� ���� 
					temp=a[i][2]-b[j][2];
					attach(res[s], a[i][0],b[j][1],temp);
					s++;
					i++;
					j++;
				}
				else{																		//����� �� �Ǵ� ���� 0�̹Ƿ� �����Ŀ� �Ҵ����� ����.
					i++;
					j++;
				}	
			}
			else{																			//a��� ������ b��� ���� �� Ŭ �� -> a����� �� �տ� ����
				attach(res[s], a[i][0],a[i][1],a[i][2]);									//a��� �����Ŀ� ����
				s++;
				i++;	
			}
		}
		else if(a[i][0]<b[j][0]){															//a����� ���� �� ������ ->a����� �� �տ� ����. a��� ����
			attach(res[s], a[i][0],a[i][1],a[i][2]);						
			s++;
			i++;	
		}
		else{																				//a����� ���� �� Ŭ�� ->b����� �� �տ� ���� b��� ����
			if(flag==1) temp = b[j][2]; 													//1�� �� �����̹Ƿ� �׳� b�� ����, 2�϶� �����̹Ƿ� -b�� ����
			else if(flag==2) temp = -b[j][2]; 
			attach(res[s], b[j][0],b[j][1],temp);
			s++;
			j++;	
			
		}
	
	}
	while(i<a_row){																			//a�� ������ �׵��� �̵�
		attach(res[s], a[i][0],a[i][1],a[i][2]);
		s++;
		i++;
	}
	while(j<b_row){																			//b�� ������ �׵��� �̵�
		if(flag==1) temp = b[j][2]; 
		else if(flag==2) temp = -b[j][2];  													//1�� �� �����̹Ƿ� �׳� b�� ����, 2�϶� �����̹Ƿ� -b�� ����
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
	s[0]=a;																					//s�� ������, s[0]���� a, s[1]���� b, s[2]���� c����
	s[1]=b;
	s[2]=c;
}

int **memory_allocation(int sparse){														//�����Ҵ� �Լ�(�Ű�����-�������� ��)
	int i,j;
	int **a;
	if(sparse<0){																			//���� �Ű����� �������� ���� 0���� ������ �����Ҵ� �Ұ�
		printf("�޸𸮰� �������� �ʽ��ϴ�.\n");
		return 0;
	}
	
	a = (int **)malloc(sizeof(int*)*sparse);												//���������� a�� �������� ������ �����Ҵ�
	for(i=0; i<sparse; i++){																//�������� ������ 3�̹Ƿ� for���� ���� a[i]�� 3���� �����Ҵ�
		a[i] = (int*)malloc(sizeof(int)*3);
		for(j=0; j<3; j++){																	//�����Ҵ�� �Բ� 0���� �ʱ�ȭ
			a[i][j]=0;
		}
	}
	return a;																				//�����Ҵ��� ���������� a�� ��ȯ
}

void Sort_Matrix(int **matrix, int row){													//�����Լ�(�Ű����� - ������, �������� �ప)
	int i,r,tmp,k;
	for(i=0; i<row; i++){
		for(r=0; r<row; r++){
			if(matrix[i][0]<matrix[r][0]){													//���� ���� ����� �ప���� �ڿ� �ִ� ����� �� ũ�ٸ� ����
				for(k=0; k<3; k++){
					tmp=matrix[i][k];
					matrix[i][k] = matrix[r][k];
					matrix[r][k]=tmp;
				}		
			}
			if((matrix[i][0]==matrix[r][0]) && (matrix[i][1]<matrix[r][1]) ){				//������ ��� ��ģ �� ����� ���� ���Ͽ� ����, ���� �ప�� ���� ������ �ڰ� �� ũ�ٸ� �ٽ� ����
				for(k=0; k<3; k++){
					tmp=matrix[i][k];
					matrix[i][k] = matrix[r][k];
					matrix[r][k]=tmp;
				}
			}
		}	
	}
}
void Trans_Matrix(int **matrix, int sparse_row, int* row, int *col){						//��ġ �Լ�(�Ű����� - ������, �������� �ప, full-matrix�� ��� ���� �ּ�)
	int i, tmp;
	tmp = *row;																				//full-matrix�� ������ ��ġ
	*row = *col;
	*col = tmp;

	for(i=0; i<sparse_row; i++){															//�������� ��, ������ ��ġ
		tmp=matrix[i][1];
		matrix[i][1] = matrix[i][0];
		matrix[i][0]=tmp;
	}
	Sort_Matrix(matrix, sparse_row);														//��ġ����� ���� -> �����Լ�
}

void Matrix_Print(int **matrix, int row, int col){											//����Լ�(�Ű�����-��� ���, �������� ��, ����) 
	int i,j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			if(j==2) printf(" :");															//j�� 2�϶� :�� ����Ͽ� ��ġ�� ������ ����
			printf("%3d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void Free_Matrix(int **matrix, int row){													//�޸� �����Ҵ� ���� �Լ�(�Ű����� - ������, ������ �ప)
	int i;
	for(i=0; i<row; i++){																	//�ุŭ for���� ���� free
		free(matrix[i]);
	}
	free(matrix);																			//�ప free
}
