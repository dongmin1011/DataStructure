/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 위상정렬 알고리즘 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct GraphNode {	//그래프 노드 구조체 선언
	char *subject;			//정점 문자열 변수
	int vertex;				//정점 정수 변수
	struct GraphNode *link;	//다음 노드를 가리키는 링크
}GraphNode;
typedef struct Vertex {		//정점의 정보를 저장할 구조체
	int num;				//정점 정수 변수
	char *str;				//정점 문자열 변수
}Vertex;
typedef struct GraphType {	//그래프 타입 구조체 선언
	int n;					//정점의 개수 n선언
	Vertex *ary;			//정점의 정보를 저장할 Vertex자료형 포인터 선언
	GraphNode **adj_list;	//링크리스트를 저장할 그래프 노드 포인터 선언
}GraphType;

int Find_index(Vertex list[], int find, int count);	//정점 배열에서 인덱스 값을 찾는 함수
void graph_init(GraphType *g, int n);	//그래프 초기화 함수
void insert_vertex(GraphType*g, int v, int index, char *str);	//정점 삽입함수
void insert_edge(GraphType*g, int start, int end);		//간선 삽입함수, 인접 리스트에 삽입
int topo_sort(GraphType *g);			//위상정렬 함수
void Delete(GraphType *g);			//그래프 삭제 함수
 void print_adj_list(GraphType*g) {							//그래프를 형식에 맞게 출력하는 함수
	int i;
	for (i = 0; i < g->n; i++) {
		GraphNode*p = g->adj_list[i];						//리스트 배열의 값을 p에 저장
		printf("정점 %6s의 인접 리스트 ", g->ary[i].str);	//현재 정점 출력
		while (p != NULL) {								//p리스트의 끝까지 반복하며 출력
			printf("-> %d ", p->vertex);
			printf(" %s ", p->subject);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}

typedef int element;
typedef struct {						//스택 타입 구조체 선언
	element *stack;						//element형 스택 포인터
	int Stack_size;						//스택 사이즈 변수
	int top;							//현재 스택의 위치 변수
}StackType;

void init(StackType *s, int n) {		//스택 초기화 함수
	s->top = -1;						//top값을 -1로 초기화
	s->stack = (element*)malloc(sizeof(element)*n);	//n값으로 스택 배열 동적할당
	s->Stack_size = n;					//스택의 크기를 n값으로 저장
}
int is_empty(StackType *s) {			//스택이 공백상태인지 확인
	return (s->top == -1);				//top값이 -1이면 TRUE리턴
}
int is_full(StackType*s) {				//스택이 포화상태인지 확인
	return(s->top == (s->Stack_size - 1));	//top값이 size-1이면 TRUE리턴
}
void push(StackType*s, element item) {		//스택에 값을 삽입하는 함수
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	s->stack[++(s->top)] = item;		//top을 증가시키고 item변수를 스택에 삽입
}
element pop(StackType*s) {			//스택에서 pop하는 함수
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러");
		exit(1);
	}
	return s->stack[s->top--];		//top값 인덱스를 리턴하고 감소
}


int main() {
	FILE *fp;				//파일포인터
	GraphType *g;			//그래프 변수
	char str[20], *stemp;	//파일로부터 문자열을 입력받을 변수
	int temp1, temp2;		//파일로부터 정수를 입력받을 변수
	char c;					//어떤 동작을 할지 입력
	int count = 0, i;

	fp = fopen("data.txt", "r");	//파일을 읽기형식으로 open
	if (!fp) {
		printf("file not opne");
		return 0;
	}
	while (!feof(fp)) {				//파일끝까지 반복
		fscanf(fp, "%c", &c);
		if (c == 'v') {				//v는 정점삽입을 나타냄
			fscanf(fp, "%d%s", &temp1, str);
			count++;				//정점의 개수 증가
		}
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//그래프 동적할당 생성
	rewind(fp);					//파일포인터를 처음으로 옮김
	graph_init(g, count);		//count개로 그래프 초기화
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);	//파일 데이터 입력
		if (c == 'v') {			//v면 정점 삽입 동작 수행
			fscanf(fp, "%d%s", &temp1, str);
			stemp = (char*)malloc(sizeof(char)*(strlen(str)+1));//stemp를 str의 길이로 동적할당	
			strcpy(stemp, str);		//str값을 stemp에 복사
			insert_vertex(g, count, temp1, stemp);	//정점 삽입
		}
	}

	rewind(fp);				//파일포인터를 처음으로 옮김
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 'e') {		//e면 간선 삽입 동작 수행
			fscanf(fp, "%d%d", &temp1, &temp2);
			insert_edge(g, temp1, temp2);	//간선 삽입 insert_edge호출
		}
	}
	printf("< 데이터 >\n");
	printf("------------------\n");
	for (i = 0; i < count; i++) {
		printf("%-2d - %s\n", g->ary[i].num, g->ary[i].str);	//위상정렬 전 정점 정보 출력
	}
	printf("------------------\n\n");
	topo_sort(g);				//위상정렬 함수 호출
	Delete(g);					//그래프 삭제
	fclose(fp);					//파일 포인터 닫음
	return 0;
}
int Find_index(Vertex list[], int find, int count) {	//정점 배열에서 인덱스 값을 찾는 함수
	int i;
	for (i = 0; i < count; i++) {
		if (list[i].num == find) return i;	//정점 정수가 같은 값을 찾으면 현재 인덱스 리턴
	}
	return -1;		//만약 같은 인덱스가 없다면 -1리턴
}

void graph_init(GraphType *g, int n) {	//그래프 초기화 함수
	int v;
	g->n = 0;			//정점의 개수 초기화
	g->adj_list = (GraphNode**)malloc(sizeof(GraphNode*)*n);	//링크리스트 초기화
	for (v = 0; v < n; v++) {
		g->adj_list[v] = NULL;	//초기값에 NULL삽입
	}
	g->ary = (Vertex*)malloc(sizeof(Vertex)*n);		//정점 ary배열 초기화
}
void insert_vertex(GraphType*g, int v, int index, char *str) {	//정점 삽입함수
	if (((g->n) + 1) > v) {
		fprintf(stderr, "그래프 : 정점의 개수 초과");
		return;
	}
	g->ary[g->n].num = index;	//ary정점 배열에 정점 값 삽입
	g->ary[g->n].str = str;
	g->n++;		//정점의 개수 증가
}

void insert_edge(GraphType*g, int start, int end) {		//간선 삽입함수, 인접 리스트에 삽입
	GraphNode *node;
	int u = 0, v = 0;						//배열의 시작 값과 끝값 인덱스 저장 변수

	u = Find_index(g->ary, start, g->n); //ary에서 Find_index함수를 통해 인덱스값을 찾음
	v = Find_index(g->ary, end, g->n);
	//	printf("%d, %d\n", u, v);
	if (u >= g->n || v >= g->n) {			//만약 인덱스 값이 정점 개수보다 크다면 종료
		fprintf(stderr, "그래프 : 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode)); //노드를 새로 생성

	node->vertex = g->ary[v].num;		//노드의 vertex값에 ary값 삽입
	node->subject = g->ary[v].str;

	node->link = g->adj_list[u];		//insert_first연산 수행
	g->adj_list[u] = node;				//첫 노드의 링크가 원래 리스트를 가리키고
}											//리스트의 처음이 node가 됨

int topo_sort(GraphType *g) {			//위상정렬 함수
	int i;
	StackType s;						//스택 변수
	GraphNode *node;					//임시 노드 변수
	int count = 0, n = 0;
	int *in_degree = (int *)malloc(g->n * sizeof(int));
	//모든 정점의 진입 차수를 계산
	for (i = 0; i < g->n; i++) {
		in_degree[i] = 0;			//in_degree를 0으로 초기화
	}
	
	for (i = 0; i < g->n; i++) {
		GraphNode *node = g->adj_list[i];	//정점 i에서 나오는 간선들
		while (node != NULL) {
			n = Find_index(g->ary, node->vertex, g->n);	//정점배열에서 인덱스 값을 찾음
			in_degree[n]++;					//그 인덱스에 맞는 in_degree를 증가
			node = node->link;
		}
	}
	/*	for (i = 0; i < g->n; i++) {
			printf("%d ", in_degree[i]);
		}
		printf("\n\n");
		*/
	init(&s, g->n);						//스택 초기화
	for (i = 0; i < g->n; i++) {	//진입 차수가 0인 정점을 스택에 삽입
		if (in_degree[i] == 0)push(&s, i);
	}
	printf("< 위상 순서 출력 >\n");
	printf("------------------\n");
	while (!is_empty(&s)) {			//스택이 공백상태가 될때까지 반복
		int w;
		
		w = pop(&s);				//가장 마지막으로 삽입된 인덱스 값을 pop
		printf("%d. %-2d  - %s\n", ++count, g->ary[w].num, g->ary[w].str);	//pop된 인덱스 값에 맞는 정점 출력
		node = g->adj_list[w];		//각 정점의 진입 차수를 변경
		while (node != NULL) {
			n = Find_index(g->ary, node->vertex, g->n);	//정점배열에서 인덱스 값을 찾음
			in_degree[n]--;			//찾은 인덱스 값의 진입 차수를 감소
			if (in_degree[n] == 0)push(&s, n);	//진입 차수가 0인 정점인덱스를 삽입
			node = node->link;

		}
		
	}
	printf("------------------\n");
	free(in_degree);		//in_degree배열 삭제
	free(s.stack);			//스택 삭제
	printf("\n");
	return (i == g->n);
}
void Delete(GraphType *g) {			//그래프 삭제 함수
	int i;
	GraphNode *p, *q;
	for (i = 0; i < g->n; i++) {
		free(g->ary[i].str);		//ary배열의 str문자열 삭제
		p = g->adj_list[i];
		q = p;
		if (p != NULL) {
			while (p != NULL) {
				q = q->link;
				free(p);		//링크리스트 삭제 
				p = q;
			}
		}
		
	}
	//리스트의 노드들은 str과 같은 공간을 가지므로 삭제 x
	free(g->ary);			//ary포인터 삭제
	free(g->adj_list);		//adj_list삭제
	free(g);				//그래프 삭제
}