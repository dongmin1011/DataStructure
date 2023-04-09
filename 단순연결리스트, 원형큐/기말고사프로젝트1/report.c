/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과 
	이름 : 김동민 
	프로그램명 : 단순연결리스트의 곱셈 프로그램
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct{
	int coef;									//밑
	int expon;									//지수
}element;
typedef struct ListNode{
	element data;								//밑과 지수 구조체
	struct ListNode *link;				
}ListNode;
typedef struct ListType{
	int size;
	ListNode *head;								//처음를 가리키는 head포인터
	ListNode *tail;								//끝을 가리키는 tail포인터
}ListType;

void error(char *message);												//에러메시지 출력 함수
ListType* create();														//연결리스트 생성 함수
void insert_last(ListType* plist, int coef, int expon);					//리스트의 마지막에 리스트를 추가하는 함수
void poly_print(ListType *plist, const char* formula);					//다항식을 출력하는 함수
void sort(ListType *plist);												//다항식을 내림차순 정렬하는 함수
void delete_zero(ListType* plist);										//곱셈 계산에서 밑이 0일때의 리스트를 제거하는 함수
void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3);	//곱셈계산 함수
void get_result(char *result, char*poly1, char *poly2);					//결과 다항식의 이름을 저장하는 함수

int main(){
	FILE *fp;
	ListType *list1, *list2, *list3;
	int tmp1, tmp2;
	char ch;
	char poly1[20], poly2[20], result[20];

	list1 = create();												//다항식1생성
	list2 = create();												//다항식2생성
	list3 = create();												//다항식3생성

	fp=fopen("data.txt", "r");										//data를 읽기 전용으로 오픈
	if(fp==NULL){
		error("파일이 열리지 않습니다.\n");
	}
	fscanf(fp, "%s", poly1);										//data로부터 다항식 1의 이름 저장
	while(!feof(fp)){
		fscanf(fp, "%d%d", &tmp1, &tmp2);						//data로부터 임시변수1,2에 값을 받아옴
		fscanf(fp, "%c", &ch);							//만약 ch가 공백문자이면 계속 입력을 받는다는 신호이고 줄바꿈 문자이면 다항식 입력이 끝났다는 의미
		insert_last(list1, tmp1, tmp2);				//tmp1값과 tmp2값을 첫번째 다항식 리스트에 저장
		if(ch == '\n')break;						//ch가 줄바꿈 문자이면 반복문 종료
	}
	fscanf(fp, "%s", poly2);						//data로부터 다항식 2의 이름 저장
	while(!feof(fp)){
		fscanf(fp, "%d%d", &tmp1, &tmp2);
		fscanf(fp, "%c", &ch);
		insert_last(list2, tmp1, tmp2);
		if(ch == '\n')break;
	}
	poly_mul(list1, list2, list3);					//다항식의 곱셈 함수
	get_result(result, poly1, poly2);				//poly1과 poly2를 합하여 result문자열에 저장하는 함수

	poly_print(list1,  poly1);						//list1다항식 출력 다항식의 이름은 poly1에 저장
	poly_print(list2,  poly2);						//list2다항식 출력 다항식의 이름은 poly2에 저장
	poly_print(list3, result);						//list3다항식 출력 다항식의 이름은 result에 저장
	
	free(list1); free(list2); free(list3);
	fclose(fp); return 0;
}
void error(char *message){										//오류메시지 출력함수
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListType* create(){												//리스트 헤더 생성 함수
	ListType *plist= (ListType*) malloc(sizeof(ListType));		//ListType을 동적할당 생성
	plist->size = 0;											
	plist->head = plist->tail = NULL;							//리스트의 헤더값과 테일 값을 NULL로 설정
	return plist;												//동적할당한 값을 리턴
}
void insert_last(ListType* plist, int coef, int expon){			//리스트의 맨 끝에 삽입하는 함수
	ListNode *temp = (ListNode*) malloc(sizeof(ListNode));		//리스트 노드 동적할당
	if(temp==NULL) error("메모리 할당 에러");
	temp->data.coef = coef;										//temp에 값 저장
	temp->data.expon = expon;
	temp->link = NULL;
	if(plist->tail == NULL)										//만약 tail이 NULL이라면 가장 처음 값을 나타냄.
		plist->head = plist->tail = temp;						//리스트의 헤드와 테일에 temp를 저장
	else{
		plist->tail->link = temp;								//가장 처음 값이 아니라면
		plist->tail = temp;										//tail에 temp저장
	}
	plist->size++;
}

void poly_print(ListType *plist, const char* formula){			//다항식을 출력하는 함수 매개변수는 연결리스트의 헤더를 가리키는 포인터와 다항식의 이름
	ListNode *p = plist->head;

	printf("%s = ", formula);									//다항식의 이름 출력
	for(; p; p = p->link){
		if(p->data.coef>0){										//만약 밑의 값이 0이상이면 양수임
			if(p!=plist->head) printf(" + ");					//만약 p가 head값과 같다면 가장 첫 항임을 말하므로 head값과 다를때만 +출력
			if(p->data.expon==0)								//지수(expon)값이 0이라면 상수임을 나타내므로 밑만 출력
				printf("%d", p->data.coef);
			else 
				printf("%dX^%d", p->data.coef, p->data.expon);	//지수가 0이 아니라면 밑X^지수 형태로 출력
		}
		else{													//밑의 값이 양수가 아니므로 음수임을 나타냄
			printf(" - ");										//만약 p가 head값과 같다면 가장 첫 항임을 말하므로 head값과 다를때만 -출력
			if(p->data.expon==0)
				printf("%d", -p->data.coef);					//-는 위에서 출력했고, 밑(coef)에 -를 붙여 양수형으로 출력, 지수가 0이므로 밑만 출력
			else 
				printf("%dX^%d", -p->data.coef, p->data.expon); //밑(coef)에 -를 붙여 양수형으로 출력, 지수가 0이 아니므로 -밑X^지수 형태로 출력
		}
		
	}
	printf("\n");
}
void sort(ListType *plist){									//다항식을 정렬하는 함수
	ListNode *p, *q;										//ListNode 자료형으로 2개의 포인터변수 선언
	element temp;											//정렬할때 사용하는 element형 임시 변수
	for(p=plist->head; p!=NULL; p=p->link){
		for(q=p; q!=NULL; q=q->link){
			if(p->data.expon < q->data.expon){				//만약 p의 지수보다 q의 지수보다 크다면
				temp = q->data;								//q의 데이터 값을 임시변수에 담음
				q->data = p->data;							//p의 데이터 값을 q의 데이터 값에 저장
				p->data = temp;								//temp의 값을 p의 데이터 값에 저장 
			}												//정렬 완료
		}
	}
}
void delete_zero(ListType* plist){							//결과 다항식에서 밑이 0일때를 제거하는 함수
	ListNode *p = plist->head;
	ListNode *remove;										//삭제할 리스트를 담을 변수
	while(p!=NULL){											//p가 null을 만날때까지 반복
		if(p->link->data.coef == 0){						//p의 다음 노드의 밑이 0이라면 제거
			remove = p->link;								//remove에 p의 링크 저장
			p->link = remove->link;							//p의 링크에 remove의 링크 저장(p의 다음노드 다음노드)
			plist->size--;
			free(remove);									//remove제거
		}	
		p = p->link;										//p를 다음노드로 이동
		if(p->link == NULL)break;							//p의 다음노드가 NULL이라면 반복 종료
	}
}
void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3){									//다항식 리스트의 곱셈 함수
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	ListNode* c;
	while(a!=NULL){
		b=plist2->head;																					//가장 바깥의 반복문을 돌때마다 b의 값을 head로 초기화
		while(b!=NULL){
			c=plist3->head;																				//가장 바깥의 반복문을 돌때마다 c의 값을 head로 초기화
			while(c!=NULL){
				if(c->data.expon == a->data.expon + b->data.expon){										//만약 c의 반복문을 도는 도중 지수값이 같은것을 만나게 되면
					c->data.coef += a->data.coef * b->data.coef;										//같은 지수값끼리 계산하고 반복 종료
					break;
				}
				c=c->link;																				//다음 노드로 이동
			}	
			if(c==NULL) insert_last(plist3, a->data.coef*b->data.coef, a->data.expon + b->data.expon);	//만약 c가 NULL이면 같은 지수값을 만나지 못한 경우를 나타냄																								//같은 지수를 만나지 못하였으므로 리스트의 마지막에 삽입
			b = b->link;
		}
		a = a->link;
	}
	delete_zero(plist3);																				//곱셈계산을 하면 중간에 밑이 0이되는 경우가 생김. 이 부분을 리스트에서 제거하는 함수
	sort(plist3);																						//지수의 크기에 따라 내림차순 정렬하는 함수
}
void get_result(char *result, char*poly1, char *poly2){						//결과식의 이름을 저장하는 함수
	strcpy(result, poly1);													//result문자배열에 poly1의 문자열 복사
	strcat(result, " * ");													//result문자열에 * 추가 strcat은 2개의 문자열을 붙이는 함수
	strcat(result, poly2);													//result문자열에 poly2문자열 복사 
}

