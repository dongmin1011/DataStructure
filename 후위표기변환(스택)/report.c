/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과 
	이름 : 김동민 
	프로그램명 : 여러자리 수로 이루어진 중위표기식을 
				 후위표기로 변경하고 계산하는 프로그램
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

void init(StackType *s);									//스택초기화
int is_empty(StackType *s);									//스택empty 검사
int is_full(StackType *s);									//스택 full 검사
void push(StackType *s, element item);						//스택push
element pop(StackType *s);									//스택pop
element peek(StackType *s);									//스택peek
int prec(char op);											//연산자 우선순위 계산
int check_matching(char *in);								//괄호 검사 함수
void infix_to_postfix(char exp[], char *inpost);			//중위표기식을 후위표기식으로 변환
double eval(char exp[]);										//후위표기식을 계산하는 함수
double getValue(int *i, char exp[]);							//문자열을 숫자로 변환하는 함수
double dpop(StackType *s);									
void dpush(StackType *s, double item);

int main(){
	char *buf, temp;
	char *buf2;
	int i=0;
	FILE *fp = fopen("data.txt", "r");				//읽기 전용 파일 오픈
	if(fp==NULL){
		printf("파일이 열리지 않았습니다.\n");
		return 0;
	}
	while(!feof(fp)){
		fscanf(fp, "%c", &temp);					//%s로 입력받는다면 공백문자를 인식하지 못하기 때문에 문자 1개씩 입력받는다.
		i++;
	}
	buf = (char*) calloc(sizeof(char),i);
	buf2 = (char*) calloc(sizeof(char),i);
	rewind(fp);
	i=0;
	while(!feof(fp)){
		fscanf(fp, "%c", &buf[i]);					//%s로 입력받는다면 공백문자를 인식하지 못하기 때문에 문자 1개씩 입력받는다.
		i++;
	}
	printf("중위표기식 %s\n", buf);					//정상적으로 입력 받았는지 확인
	if(!check_matching(buf)){						//괄호의 개수가 맞는지 확인
		printf("괄호가 올바르지 않습니다.\n");		//만약 괄호의 개수가 맞지 않는다면 return
		return 0;
	}
	infix_to_postfix(buf, buf2);					//중위표기식 buf를 후위표기식 buf2에 작성
	printf("후위표기식 %s\n", buf2);				// 후위 표기식 확인 출력
	printf("결과값: %lf\n", eval(buf2));				// 후위표기식으로 계산한 결과값 출력
	fclose(fp);
	free(buf);
	free(buf2);
	return 0;
}

void init(StackType *s){
	s->top = -1;									//스택의 top 초기값을 -1로 설정
}
int is_empty(StackType *s){
	return (s->top == -1);							//만약 스택의 top이 -1이라면 스택이 비어있음
}
int is_full(StackType *s){
	return (s->top == (MAX_STACK_SIZE-1));			//만약 스택의 top이 전체 스택값 -1 이라면 스택이 꽉 찬것임을 나타냄
}
void push(StackType *s, element item){				//매개변수는 스택과 스택에 push할 값
	if(is_full(s)){									//스택이 다 차있는지 확인
		printf("stack overflow\n");
		return;
	}
	s->stack[++(s->top)] = item;					//스택에 자리가 있다면 top값을 ++하고 값을 넣음
}
element pop(StackType *s){
	if(is_empty(s)){								//스택이 비어있다면 더이상 pop을 할 수 없으므로 강제 종료
		printf("stack underflow\n");
		exit(1);
	}
	return s->stack[(s->top)--];					//스택의 top값을 pop하고 
}

element peek(StackType *s){
	if(is_empty(s)){
		printf("stack underflow\n");
		exit(1);
	}
	return s->stack[s->top];
}
double dpop(StackType *s){							//계산함수 수행시 소수 팝
	if(is_empty(s)){								
		printf("stack underflow\n");
		exit(1);
	}
	return s->dstack[(s->top)--];
}
void dpush(StackType *s, double item){				//계산함수 수행시 소수 push
	if(is_full(s)){									
		printf("stack overflow\n");
		return;
	}
	s->dstack[++(s->top)] = item;
}
int prec(char op){									//연산자의 우선순위 판별 */가 가장 우선순위가 높고 +-가 그다음, ()가 가장 낮다
	switch(op){
	case '(': case ')':								//()의 경우는 우선순위가 가장 낮으므로 0리턴
		return 0;
	case '+': case '-':								//+-의 경우는 우선순위가 2번째이므로 1리턴
		return 1;
	case '*': case '/':								//*/의 경우는 우선순위가 1번째이므로 2리턴
		return 2;
	}
	return -1;										//판별이 불가하다면 -1리턴
}
int check_matching(char *in){						//괄호 검사 함수
	StackType s;									//괄호를 넣을 스택변수
	char ch, open_ch;
	int i, n = strlen(in);
	init(&s);										//스택 초기화
	for(i=0; i<n; i++){
		ch = in[i];
		switch(ch){
		case '(':									//'('문자라면 push
			push(&s, ch);
			break;
		case ')':									//')'문자를 만나면 
			if(is_empty(&s))						//스택이 비어있다면 '(', ')'의 개수가 맞지 않으므로 오류
				return FALSE;	
			else{
				open_ch = pop(&s);					//스택에서 pop
				if(open_ch=='(' && ch != ')')		//ch와 open_ch가 같은 짝이 아니라면 오류
					return FALSE;
				break;
			}
		}
	}
	if(!is_empty(&s))								//괄호의 개수가 맞다면 스택이 비어있어야 함. 비어있지 않다면 오류
		return FALSE;
	return TRUE;
}
void infix_to_postfix(char exp[], char *inpost){							//중위표기식을 후위표기식으로 변환, 매개변수 1.중위, 2.후위를 담을 문자열
	int i=0;
	char ch, top_op;
	int len = strlen(exp);
	int cnt =0;
	StackType s;
	init(&s);
	
	for(i=0; i<len; i++){
		ch = exp[i];	
		if(ch!=' '){																	//ch가 공백문자가 아닐때만 후위에 출력
			switch(ch){																	//만약에 연산자라면 + - * / 
			case '-':
				if(isdigit(exp[i+1])){													//만약 -다음문자가 공백이 아니고 숫자라면 음수임을 나타내므로 출력
					inpost[cnt++] = ch;
					break;																//연산자가 아니므로 후위표기식에 출력하고 switch문 break
				}
			case '+':
			case '*':
			case '/':
				while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))){					//연산자는 기본적으로 스택에 push하지만
					inpost[cnt++] = pop(&s);											//스택에 있는 연산자의 우선순위가 더 크거나 같으면 pop해서 출력	
					inpost[cnt++] = ' ';
				}
				push(&s, ch);															//연산자 push
				break;
			case '(':																	//'('문자라면 스택에 push
				push(&s, ch);
				break;
			case ')':
				top_op = pop(&s);
				while(top_op!='('){										//왼쪽 괄호를 만날때까지 출력
					inpost[cnt++] = top_op;								//왼쪽괄호가 아니므로 후위표기식에 출력
					inpost[cnt++] = ' ';								//공백문자로 구분
					top_op = pop(&s);									//연산자 pop
				}
				break;
			default:													//피연산자(숫자)일 때
				while(1){										
					ch = exp[i];
					if(ch == ' '|| i == len)break;									//공백문자를 만났다면 피연산자 출력 종료
					inpost[cnt++] = ch;									//공백문자가 아니라면 피연산자이므로 후위표기식에 출력
					i++;		
				}
				inpost[cnt++] = ' ';										//공백문자로 구분
				break;
			}
		}
	}
	while(!is_empty(&s)){												//문자열의 끝에 도달했다면 스택에 남은 것들을 모두 pop
		inpost[cnt++] = pop(&s);
		inpost[cnt++] = ' ';
	}
}
double eval(char exp[]){											//후위표기식을 이용하여 계산하는 함수
	double op1, op2, value;
	int i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if(ch!=' '){
			if (ch != '+' && ch!= '-' && ch != '*' && ch != '/'){	// 입력이 피연산자이면
				value = getValue(&i, exp);							//피연산자를 문자열에 담아 숫자로 리턴하는 함수. i(exp의 index)의 주소를 보내 변수를 다른 함수에서도 참조할 수 있도록 한다.
				dpush(&s, value);									//값을 스택에 push
			}
			else if( ch == '-'){									//만약 문자가 -인 경우는 음수일때 또는 연산자-일때이다.
				if(isdigit(exp[i+1])){								//-문자 다음문자가 공백이 아니라 숫자라면 음수임을 나타내므로 숫자로 바꾸는 함수를 호출한다.
					value = getValue(&i, exp);						
					dpush(&s, value);								//값을 리턴받으면 push
				}
				else{												//-문자 다음 공백이라면 연산자 -이므로 스택을 pop하여 -연산한다.
					op2 = dpop(&s);
					op1 = dpop(&s);
					dpush(&s, op1 - op2);
				}
			}
			else{													//연산자이면 피연산자를 스택에서 제거
				op2 = dpop(&s);
				op1 = dpop(&s);
				switch (ch) {										//연산을 수행하고 스택에 저장 
				case '+': dpush(&s, op1 + op2); break;
			//	case '-': push(&s, op1 - op2); break;				//-일땐 위에서 처리
				case '*': dpush(&s, op1 * op2); break;
				case '/': dpush(&s, op1 / op2); break;
				}
			}
		}	
	}
	return dpop(&s);
}
double getValue(int *i, char exp[]){							//문자열을 숫자로 변환해주는 함수 매개변수 1.후위문자열배열의 index를 나타내는 i 포인터, 2.후위 문자열
	int j=0;												//j는 문자열의 index
	char ch;
	char str[50]={0};											
	while(1){
		ch = exp[*i];										//포인터 i의 값을 배열의 index로 하여 문자 ch에 담는다
		if(ch==' ')break;									//만약 ch가 공백문자라면 break
		str[j++]=ch;										//ch를 str문자열에 담고 j를 ++한다.
		(*i)++;												//i포인터의 값을 ++
	}
	return atof(str);										//만약 ch가 공백문자를 만나 break했다면 atoi함수를 이용해 str문자열을 숫자로 변환하여 이를 리턴한다.
}