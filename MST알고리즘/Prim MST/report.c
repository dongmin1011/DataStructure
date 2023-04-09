/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: Prim의 MST프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

#define TRUE 1
#define FALSE 0

#define INF 1000

typedef struct GraphType{
	int  n;			//정점의 개수
	int **weight;	// 인접 행렬 그래프 포인터
}GraphType;

int *selected;		//정점이 방문되었는지 담아놓는 변수
int *distance;		//가중치가 저장되어있는 변수

void init(GraphType*g, int num);		//그래프, selected, distance 변수 초기화 함수

void insert_vertex(GraphType*g, int num);	//정점 삽입 함수
void insert_edge(GraphType* g, int start, int end, int weight);	//간선 삽입 함수(무방향그래프)

int get_min_vertex(int n);		//최소 dist[v] 값을 갖는 정점 반환함수
void prim(GraphType*g, int s);	//Prim 최소 비용 신장 트리 함수
void Delete(GraphType*g);		//그래프 삭제 함수

int main() {
	FILE *fp;
	GraphType *g;
	int max = INT_MIN;			//max에 int의 최소값 삽입
	int start, end, weight;		//데이터를 입력받을 임시변수
	int i;

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0; 
	}
	while (!feof(fp)) {
		fscanf(fp, "%d%d%d", &start, &end, &weight);
		if (max < start)max = start;	//start와 end중에서 가장 큰 정점의 값을 찾음
		if (max < end)max = end;
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//그래프 생성
	max++;
	init(g, max);		//max값으로 초기화

	for (i = 0; i < max; i++) {	//정점 삽입
		insert_vertex(g, max);
	}
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%d%d%d", &start, &end, &weight);
		insert_edge(g, start, end, weight);	//그래프에 간선 삽입
	}
	prim(g, 0);	//prim 최소 비용 신장트리 함수 호출 (0부터 시작)

	Delete(g);	//그래프 삭제 함수 
	fclose(fp);
	return 0;
}
void init(GraphType*g, int num) {		//초기화 함수
	int i, j;
	g->n = 0;
	g->weight = (int**)malloc(sizeof(int*)*num);	//num값으로 weight동적할당
	selected = (int*)malloc(sizeof(int)*num);		//num값으로 selected동적할당
	distance = (int*)malloc(sizeof(int)*num);		//num값으로 distance동적할당
	for (i = 0; i < num; i++) {
		g->weight[i] = (int*)malloc(sizeof(int)*num);	//그래프 열 동적할당
		selected[i] = 0;
		distance[i] = 0;
		for (j = 0; j < num; j++) {
			g->weight[i][j] = INF;	//그래프의 값을 INF로 초기화
		}
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
	g->weight[end][start] = weight;		//end행 start열 둘 다 저장
}

int get_min_vertex(int n) {	//최소 dist[v] 값을 갖는 정점을 반환하는 함수
	int v, i;

	for (i = 0; i < n; i++) {	//0부터 정점의 개수까지 반복
		if (!selected[i]) { //만약 방문되지 않았다면 
			v = i;			//현재 인덱스를 v에 담고 break;
			break;
		}
	}
	for (i = 0; i < n; i++) {	//0부터 정점의 개수까지 반복
		//정점이 방문되지 않았고, 현재 가중치보다 더 작은 가중치가 있다면 v를 업데이트
		if (!selected[i] && (distance[i] < distance[v]))v = i;	//가능한 간선중에 최소 distance를 찾음
	}
	return v;	//v리턴
}
void prim(GraphType*g, int s) {	//Prim 최소 비용 신장 트리 함수
	int i, u, v;
	int *ary;
	int sum = 0;

	ary = (int*)malloc(sizeof(int)*g->n);	//순서를 저장할 ary변수 동적할당
	printf("-Prim의 최소 비용 신장 트리 프로그램-\n\n");
	printf(">> 과정\n");
	for (u = 0; u < g->n; u++)
		distance[u] = INF;	//모든 distance값을 INF로 초기화
	distance[s] = 0;		//시작 정점의 distance값에 0 삽입
	
	for (i = 0; i < g->n; i++) {

		u = get_min_vertex(g->n);	//최소 distance를 u에 저장

		selected[u] = TRUE;	//현재 정점을 방문되었다고 표시
		if (distance[u] == INF) return;	//distance값이 INF이면 return

		ary[i] = u;			//ary에 최소 값을 가진 u를 삽입
		sum += distance[u];	//sum에 disance값을 더해나감
		
		
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {	//weight값이 INF가 아니라면
				//현재 정점이 방문되지 않았고 weight값이 distance보다 작다면
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];	//distance값을 wegiht로 업데이트

				}
			}
		}
		
		
		printf("%d >> ", i+1);
		for (v = 0; v <= i; v++) {
			printf("%d ", ary[v]);	//i의 개수만큼 정점 출력
		}
		printf(": %d\n", sum);	//길이 출력

	}
	printf("\n<필요한 최소 비용 : %d>", sum);
	free(ary);
}
void Delete(GraphType*g) {		//메모리 삭제 함수
	int i;
	for (i = 0; i < g->n; i++) {
		free(g->weight[i]);		//그래프 열 삭제
	}
	free(g->weight);		//그래프 행 삭제
	free(g);				//그래프 삭제
	free(distance);		//distance변수 메모리 해제
	free(selected);		//selected변수 메모리 해제
}