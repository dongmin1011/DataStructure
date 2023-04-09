/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: Floyd의 최단 경로 알고리즘
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1000

typedef struct GraphType {
	int n;						//정점의 개수
	int **weight;				//가중치 그래프
}GraphType;
typedef struct Floyd {
	int A;						//가중치를 담을 변수
	int check;					//간선이 새로 생기면 TRUE
}Floyd;
Floyd **data;			//Floyd형 이중포인터를 최단경로 배열로 사용

void Init(GraphType *g, int n); //그래프 초기화 함수
void insert_vertex(GraphType*g, int num);	//정점을 삽입하는 함수
void insert_edge(GraphType* g, int start, int end, int weight);		//무방향 그래프로 간선을 삽입하는  함수
void printA(GraphType *g);		//data배열을 형식에 맞게 출력하는 함수
void floyd(GraphType*g);			//Floyd 알고리즘 함수
void Delete(GraphType*g);			//그래프 삭제함수

int main() {
	GraphType *g;		//그래프 변수
	FILE *fp;			//파일포인터
	int max = -1;		//가장 큰 정점을 담을 max변수
	int temp1, temp2, weight, i;	//파일로부터 값을 입력받을 temp와 weight
	char c;				//어떤 동작을 할지 파일로부터 입력받을 문자 c

	fp = fopen("data.txt", "r");		//data파일을 읽기 형식으로 open
	if (!fp) {
		printf("file not open");
		return 0;
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//그래프 동적할당 생성
	while (!feof(fp)) {					//파일 끝까지 값을 입력
		fscanf(fp, "%c", &c);			
		if (c == 'v') {					//입력받은 문자가 v라면 정점 삽입 동작
			fscanf(fp, "%d", &temp1);
			if (max < temp1) max = temp1;	//정점중에 가장 큰 값을 찾음
		}
	}
	max++;				//가장 큰값에서 1증가	
	Init(g, max);		//max값으로 그래프 초기화
	rewind(fp);			//파일포인터를 다시 앞으로 옮김
	for (i = 0; i < max; i++) {
		insert_vertex(g, max);		//정점 삽입
	}
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 'e') {				//입력받은 문자가 e라면 간선 삽입 동작
			fscanf(fp, "%d%d%d", &temp1, &temp2, &weight);	//시작과 끝값, 가중치 값을 입력
			insert_edge(g, temp1, temp2, weight);		//간선 삽입
		}
	}
	floyd(g);			//floyd함수 호출
	Delete(g);			//그래프 삭제
	fclose(fp);			//파일포인터 닫음
	return 0;
}
void Init(GraphType *g, int n) {
	int i, j;
	g->n = 0;				//정점의 개수 초기화
	g->weight = (int **)malloc(sizeof(int*)*n);	//가중치 그래프 n값으로 동적할당
	for (i = 0; i < n; i++) {
		g->weight[i] = (int*)malloc(sizeof(int)*n);
		for (j = 0; j < n; j++) {
			g->weight[i][j] = INF;		//가중치 그래프를 INF로 초기화
		}
	}
	data = (Floyd **)malloc(sizeof(Floyd*)*n);	//data이중포인터를 동적할당
	for (i = 0; i < n; i++) {
		data[i] = (Floyd*)malloc(sizeof(Floyd)*n);
	}
}
void insert_vertex(GraphType*g, int num) {	//정점을 삽입하는 함수
	if ((g->n) + 1 > num) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;		//정점의 개수 증가
}
void insert_edge(GraphType* g, int start, int end, int weight) {//무방향 그래프로 간선을 삽입하는  함수
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->weight[start][end] = weight;		//무방향 그래프이기 때문에 start행 end열
//	g->weight[end][start] = weight;		//end행 start열 둘 다 저장
	g->weight[start][start] = g->weight[end][end] = 0;	//자기 자신은 0으로 초기화
	data[start][end].check = data[end][start].check = TRUE;	//새롭게 생긴 간선의 check값을 TRUE
//	data[start][start].check = data[end][end].check = TRUE;	//새롭게 생긴 간선의 check값을 TRUE
}
void printA(GraphType *g) {			//data배열을 형식에 맞게 출력하는 함수
	int i, j;
	printf("  ");
	for (i = 0; i < g->n; i++) printf(" %3d ", i);	//열을 나타내는 정점 출력
	printf("\n");
	printf("---------------------------------------\n");
	for (i = 0; i < g->n; i++) {
		printf(" %d |", i);		//행을 나타내는 정점 출력
		for (j = 0; j < g->n; j++) {
			if (data[i][j].A == INF) {		//만약 간선이 존재하지 않는다면
				printf("%3c |", 'x');		//x출력
			}
			else {							//간선이 존재한다면
				if (data[i][j].check) {		//새롭게 생긴 간선이라면 *출력
					printf("*%2d |", data[i][j].A);
					data[i][j].check = FALSE;	//check값을 다시 FALSE로 바꿔줌
				}
				else printf("%3d |", data[i][j].A);	//원래 있던 간선이라면 그냥 출력
			}
		}
		printf("\n");
	}
	printf("---------------------------------------\n\n");
}

void floyd(GraphType*g) {			//Floyd 알고리즘 함수
	int i, j, k;
	for (i = 0; i < g->n; i++) {		//data의 초기값은 가중치 행렬인 weight값을 가짐
		for (j = 0; j < g->n; j++) {
			data[i][j].A = g->weight[i][j];
		}
	}
	printf("< 초기 상태 >\n");			//초기상태 출력
	printA(g);
	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				//만약 i에서 j로 바로 가는 길보다 k를 거쳐가는 길이 더 빠르다면
				if (data[i][k].A + data[k][j].A < data[i][j].A) {
					data[i][j].A = data[i][k].A + data[k][j].A;	//i에서 k, k에서 j로 가는 길의 합을 대신 삽입
					data[i][j].check = TRUE;		//새로운 길이 생겼으므로 check값을 TRUE
				}
				//k를 거쳐가지 않는 경우는 그대로
			}
		}
		printf("< %d번 정점 열림 >\n", k);			//몇번 정점을 지나는지 출력
		printA(g);							//floyd그래프 출력
	}
}

void Delete(GraphType*g) {			//그래프 삭제함수
	int i;
	for (i = 0; i < g->n; i++) {
		free(data[i]);			//floyd 그래프 data 열과
		free(g->weight[i]);		//가중치 그래프 weight열을 삭제
	}
	free(data);		//data와 weight 삭제
	free(g->weight);
	free(g);		//그래프 삭제
}
