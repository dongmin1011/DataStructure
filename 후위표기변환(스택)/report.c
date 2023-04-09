/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а� 
	�̸� : �赿�� 
	���α׷��� : �����ڸ� ���� �̷���� ����ǥ����� 
				 ����ǥ��� �����ϰ� ����ϴ� ���α׷�
*/
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 100

typedef int element;

typedef struct{
	element stack[MAX_STACK_SIZE];
	double dstack[MAX_STACK_SIZE];
	int top;
}StackType;

void init(StackType *s);									//�����ʱ�ȭ
int is_empty(StackType *s);									//����empty �˻�
int is_full(StackType *s);									//���� full �˻�
void push(StackType *s, element item);						//����push
element pop(StackType *s);									//����pop
element peek(StackType *s);									//����peek
int prec(char op);											//������ �켱���� ���
int check_matching(char *in);								//��ȣ �˻� �Լ�
void infix_to_postfix(char exp[], char *inpost);			//����ǥ����� ����ǥ������� ��ȯ
double eval(char exp[]);										//����ǥ����� ����ϴ� �Լ�
double getValue(int *i, char exp[]);							//���ڿ��� ���ڷ� ��ȯ�ϴ� �Լ�
double dpop(StackType *s);									
void dpush(StackType *s, double item);

int main(){
	char *buf, temp;
	char *buf2;
	int i=0;
	FILE *fp = fopen("data.txt", "r");				//�б� ���� ���� ����
	if(fp==NULL){
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return 0;
	}
	while(!feof(fp)){
		fscanf(fp, "%c", &temp);					//%s�� �Է¹޴´ٸ� ���鹮�ڸ� �ν����� ���ϱ� ������ ���� 1���� �Է¹޴´�.
		i++;
	}
	buf = (char*) calloc(sizeof(char),i);
	buf2 = (char*) calloc(sizeof(char),i);
	rewind(fp);
	i=0;
	while(!feof(fp)){
		fscanf(fp, "%c", &buf[i]);					//%s�� �Է¹޴´ٸ� ���鹮�ڸ� �ν����� ���ϱ� ������ ���� 1���� �Է¹޴´�.
		i++;
	}
	printf("����ǥ��� %s\n", buf);					//���������� �Է� �޾Ҵ��� Ȯ��
	if(!check_matching(buf)){						//��ȣ�� ������ �´��� Ȯ��
		printf("��ȣ�� �ùٸ��� �ʽ��ϴ�.\n");		//���� ��ȣ�� ������ ���� �ʴ´ٸ� return
		return 0;
	}
	infix_to_postfix(buf, buf2);					//����ǥ��� buf�� ����ǥ��� buf2�� �ۼ�
	printf("����ǥ��� %s\n", buf2);				// ���� ǥ��� Ȯ�� ���
	printf("�����: %lf\n", eval(buf2));				// ����ǥ������� ����� ����� ���
	fclose(fp);
	free(buf);
	free(buf2);
	return 0;
}

void init(StackType *s){
	s->top = -1;									//������ top �ʱⰪ�� -1�� ����
}
int is_empty(StackType *s){
	return (s->top == -1);							//���� ������ top�� -1�̶�� ������ �������
}
int is_full(StackType *s){
	return (s->top == (MAX_STACK_SIZE-1));			//���� ������ top�� ��ü ���ð� -1 �̶�� ������ �� �������� ��Ÿ��
}
void push(StackType *s, element item){				//�Ű������� ���ð� ���ÿ� push�� ��
	if(is_full(s)){									//������ �� ���ִ��� Ȯ��
		printf("stack overflow\n");
		return;
	}
	s->stack[++(s->top)] = item;					//���ÿ� �ڸ��� �ִٸ� top���� ++�ϰ� ���� ����
}
element pop(StackType *s){
	if(is_empty(s)){								//������ ����ִٸ� ���̻� pop�� �� �� �����Ƿ� ���� ����
		printf("stack underflow\n");
		exit(1);
	}
	return s->stack[(s->top)--];					//������ top���� pop�ϰ� 
}

element peek(StackType *s){
	if(is_empty(s)){
		printf("stack underflow\n");
		exit(1);
	}
	return s->stack[s->top];
}
double dpop(StackType *s){							//����Լ� ����� �Ҽ� ��
	if(is_empty(s)){								
		printf("stack underflow\n");
		exit(1);
	}
	return s->dstack[(s->top)--];
}
void dpush(StackType *s, double item){				//����Լ� ����� �Ҽ� push
	if(is_full(s)){									
		printf("stack overflow\n");
		return;
	}
	s->dstack[++(s->top)] = item;
}
int prec(char op){									//�������� �켱���� �Ǻ� */�� ���� �켱������ ���� +-�� �״���, ()�� ���� ����
	switch(op){
	case '(': case ')':								//()�� ���� �켱������ ���� �����Ƿ� 0����
		return 0;
	case '+': case '-':								//+-�� ���� �켱������ 2��°�̹Ƿ� 1����
		return 1;
	case '*': case '/':								//*/�� ���� �켱������ 1��°�̹Ƿ� 2����
		return 2;
	}
	return -1;										//�Ǻ��� �Ұ��ϴٸ� -1����
}
int check_matching(char *in){						//��ȣ �˻� �Լ�
	StackType s;									//��ȣ�� ���� ���ú���
	char ch, open_ch;
	int i, n = strlen(in);
	init(&s);										//���� �ʱ�ȭ
	for(i=0; i<n; i++){
		ch = in[i];
		switch(ch){
		case '(':									//'('���ڶ�� push
			push(&s, ch);
			break;
		case ')':									//')'���ڸ� ������ 
			if(is_empty(&s))						//������ ����ִٸ� '(', ')'�� ������ ���� �����Ƿ� ����
				return FALSE;	
			else{
				open_ch = pop(&s);					//���ÿ��� pop
				if(open_ch=='(' && ch != ')')		//ch�� open_ch�� ���� ¦�� �ƴ϶�� ����
					return FALSE;
				break;
			}
		}
	}
	if(!is_empty(&s))								//��ȣ�� ������ �´ٸ� ������ ����־�� ��. ������� �ʴٸ� ����
		return FALSE;
	return TRUE;
}
void infix_to_postfix(char exp[], char *inpost){							//����ǥ����� ����ǥ������� ��ȯ, �Ű����� 1.����, 2.������ ���� ���ڿ�
	int i=0;
	char ch, top_op;
	int len = strlen(exp);
	int cnt =0;
	StackType s;
	init(&s);
	
	for(i=0; i<len; i++){
		ch = exp[i];	
		if(ch!=' '){																	//ch�� ���鹮�ڰ� �ƴҶ��� ������ ���
			switch(ch){																	//���࿡ �����ڶ�� + - * / 
			case '-':
				if(isdigit(exp[i+1])){													//���� -�������ڰ� ������ �ƴϰ� ���ڶ�� �������� ��Ÿ���Ƿ� ���
					inpost[cnt++] = ch;
					break;																//�����ڰ� �ƴϹǷ� ����ǥ��Ŀ� ����ϰ� switch�� break
				}
			case '+':
			case '*':
			case '/':
				while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))){					//�����ڴ� �⺻������ ���ÿ� push������
					inpost[cnt++] = pop(&s);											//���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ pop�ؼ� ���	
					inpost[cnt++] = ' ';
				}
				push(&s, ch);															//������ push
				break;
			case '(':																	//'('���ڶ�� ���ÿ� push
				push(&s, ch);
				break;
			case ')':
				top_op = pop(&s);
				while(top_op!='('){										//���� ��ȣ�� ���������� ���
					inpost[cnt++] = top_op;								//���ʰ�ȣ�� �ƴϹǷ� ����ǥ��Ŀ� ���
					inpost[cnt++] = ' ';								//���鹮�ڷ� ����
					top_op = pop(&s);									//������ pop
				}
				break;
			default:													//�ǿ�����(����)�� ��
				while(1){										
					ch = exp[i];
					if(ch == ' '|| i == len)break;									//���鹮�ڸ� �����ٸ� �ǿ����� ��� ����
					inpost[cnt++] = ch;									//���鹮�ڰ� �ƴ϶�� �ǿ������̹Ƿ� ����ǥ��Ŀ� ���
					i++;		
				}
				inpost[cnt++] = ' ';										//���鹮�ڷ� ����
				break;
			}
		}
	}
	while(!is_empty(&s)){												//���ڿ��� ���� �����ߴٸ� ���ÿ� ���� �͵��� ��� pop
		inpost[cnt++] = pop(&s);
		inpost[cnt++] = ' ';
	}
}
double eval(char exp[]){											//����ǥ����� �̿��Ͽ� ����ϴ� �Լ�
	double op1, op2, value;
	int i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if(ch!=' '){
			if (ch != '+' && ch!= '-' && ch != '*' && ch != '/'){	// �Է��� �ǿ������̸�
				value = getValue(&i, exp);							//�ǿ����ڸ� ���ڿ��� ��� ���ڷ� �����ϴ� �Լ�. i(exp�� index)�� �ּҸ� ���� ������ �ٸ� �Լ������� ������ �� �ֵ��� �Ѵ�.
				dpush(&s, value);									//���� ���ÿ� push
			}
			else if( ch == '-'){									//���� ���ڰ� -�� ���� �����϶� �Ǵ� ������-�϶��̴�.
				if(isdigit(exp[i+1])){								//-���� �������ڰ� ������ �ƴ϶� ���ڶ�� �������� ��Ÿ���Ƿ� ���ڷ� �ٲٴ� �Լ��� ȣ���Ѵ�.
					value = getValue(&i, exp);						
					dpush(&s, value);								//���� ���Ϲ����� push
				}
				else{												//-���� ���� �����̶�� ������ -�̹Ƿ� ������ pop�Ͽ� -�����Ѵ�.
					op2 = dpop(&s);
					op1 = dpop(&s);
					dpush(&s, op1 - op2);
				}
			}
			else{													//�������̸� �ǿ����ڸ� ���ÿ��� ����
				op2 = dpop(&s);
				op1 = dpop(&s);
				switch (ch) {										//������ �����ϰ� ���ÿ� ���� 
				case '+': dpush(&s, op1 + op2); break;
			//	case '-': push(&s, op1 - op2); break;				//-�϶� ������ ó��
				case '*': dpush(&s, op1 * op2); break;
				case '/': dpush(&s, op1 / op2); break;
				}
			}
		}	
	}
	return dpop(&s);
}
double getValue(int *i, char exp[]){							//���ڿ��� ���ڷ� ��ȯ���ִ� �Լ� �Ű����� 1.�������ڿ��迭�� index�� ��Ÿ���� i ������, 2.���� ���ڿ�
	int j=0;												//j�� ���ڿ��� index
	char ch;
	char str[50]={0};											
	while(1){
		ch = exp[*i];										//������ i�� ���� �迭�� index�� �Ͽ� ���� ch�� ��´�
		if(ch==' ')break;									//���� ch�� ���鹮�ڶ�� break
		str[j++]=ch;										//ch�� str���ڿ��� ��� j�� ++�Ѵ�.
		(*i)++;												//i�������� ���� ++
	}
	return atof(str);										//���� ch�� ���鹮�ڸ� ���� break�ߴٸ� atoi�Լ��� �̿��� str���ڿ��� ���ڷ� ��ȯ�Ͽ� �̸� �����Ѵ�.
}