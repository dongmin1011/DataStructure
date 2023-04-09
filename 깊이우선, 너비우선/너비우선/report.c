/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 그래프 너비 우선 탐색 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
	int Qsize;					//큐의 크기
	int *queue;					//큐 배열
	int front, rear;			//큐의 처음과 끝
}QueueType;

void error(char*message) {		//에러 출력 함수
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void queue_init(QueueType *q, int num) {	//큐 초기화 함수
	q->Qsize = num;							//큐의 크기에 num삽입
	q->queue = (int*)malloc(sizeof(int)*num);	//큐를 num값으로 동적할당
	q->front = q->rear = 0;					//front와 rear을 0으로 설정
}
int is_empty(QueueType *q) {	//큐가 비었는지 확인하는 함수
	return (q->front == q->rear);	//같으면 1, 다르면 0 반환
}
int is_full(QueueType *q) {		//큐가 모두 차있는지 확인
	return ((q->rear + 1) % q->Qsize == q->front);	//rear+1을 큐의 크기로 modulo연산
}
void enqueue(QueueType *q, int item) {		//큐에 삽입하는 함수
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
	}
	q->rear = (q->rear + 1) % q->Qsize;		//rear+1을 modulo연산하여 삽입
	q->queue[q->rear] = item;
}
int dequeue(QueueType*q) {			//큐의 가장 앞을 반환하는 함수
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % q->Qsize;	//front+1을 modulo연산하여 반환
	return q->queue[q->front];
}

typedef struct {		//그래프 구조체 선언
	int n;				//정점의 개수
	int **adj_mat;		//이중포인터 행렬
}GraphType;

int *visited;			//정점이 방문되었는지 확인하는 변수
	
void init(GraphType*g, int num);		//그래프를 초기화하는 함수
void insert_vertex(GraphType*g, int num);	//정점 삽입함수
void insert_edge(GraphType* g, int start, int end);	//간선삽입함수
void bfs_mat(GraphType*g, int v, int);		//너비 우선 탐색함수
void Delete_Graph(GraphType*g);			//그래프 삭제 함수

int main() {
	FILE *fp;
	int max = INT_MIN;			//max에 int의 가장 작은 값 삽입
	char ctemp;					//문자를 입력받는 임시변수
	int itemp1, itemp2, i;			//정수를 입력받는 임시변수2개
	GraphType *g;				//그래프 변수
	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {		//파일끝까지 반복하며 최대값을 찾음
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'v') {	//v를 입력받았을 때 정수 하나 더 입력받음
			fscanf(fp, "%d", &itemp1);
			if (max < itemp1) max = itemp1;	//입력받은 정수가 max보다 클때 max에 값을 삽입
		}
	}
	g = (GraphType*)malloc(sizeof(GraphType));
	max++;	
	init(g, max);					//max를 1 증가시키고 그래프 초기화
	for(i=0; i<max; i++){
		insert_vertex(g, max);		//그래프에 간선을 삽입
	}
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'e') {	//e를 입력받았을 때 간선 삽입
			fscanf(fp, "%d%d", &itemp1, &itemp2);	//정수 2개를 입력받고
			insert_edge(g, itemp1, itemp2);	//무방향 그래프에 삽입
		}
	}
	printf("너비 우선 탐색 : ");

	bfs_mat(g, 0, max);			//너비 우선 탐색 함수 호출
	Delete_Graph(g);		//그래프 삭제 함수
	fclose(fp);			//파일포인터 닫음
	return 0;
}
void init(GraphType*g, int num) {			//그래프를 초기화 하는 함수
	int r;
	g->n = 0;
	g->adj_mat = (int**)calloc(sizeof(int*), num);	//calloc을 이용하여 행 초기화
	for (r = 0; r < num; r++) {
		g->adj_mat[r] = (int*)calloc(sizeof(int), num);	//calloc을 이용해여 열 초기화
	}
	visited = (int*)calloc(sizeof(int), num);		//visited변수를 num값에 맞게 초기화
}
void insert_vertex(GraphType*g, int num) {	//정점을 삽입하는 함수
	if ((g->n) + 1 > num) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;		//정점의 개수 증가
}
void insert_edge(GraphType* g, int start, int end) {//무방향 그래프로 간선을 삽입하는  함수
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;		//무방향 그래프이기 때문에 start행 end열
	g->adj_mat[end][start] = 1;		//end행 start열 둘 다 저장
}
void bfs_mat(GraphType*g, int v, int num) {	//너비 우선 탐색 함수
	int w;
	QueueType q;					//큐 선언

	queue_init(&q, num);			//큐 초기화
	visited[v] = TRUE;
	printf("%d ", v);
	enqueue(&q, v);			//큐에 현재 정점 삽입
	while (!is_empty(&q)) {			//큐가 빌때까지 반복
		v = dequeue(&q);		//큐 가장 앞에 있는 값을 dequeue
		for (w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {	//정점으로 가는 길이 있고 방문되어 있지 않다면
				visited[w] = TRUE;	//현재 정점을 방문되었다고 표시
				printf("%d ", w);	//정점을 출력
				enqueue(&q, w);		//정점을 큐에 삽입
			}
		}
	}
	printf("\n");
}
void Delete_Graph(GraphType*g) {	//그래프를 삭제하는 함수
	int i = 0;
	for (i = 0; i < g->n; i++) {	//그래프의 열 메모리 해제
		free(g->adj_mat[i]);
	}
	free(g->adj_mat);			//그래프의 행 메모리 해제
	free(g);			//그래프 메모리 해제
	free(visited);		//visited변수 메모리 해제
}
