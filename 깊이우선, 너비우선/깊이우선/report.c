/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 그래프 깊이 우선 탐색 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

#define TRUE 1
#define FALSE 0

typedef struct {					//그래프 구조체 선언
	int n;
	int **adj_mat;					//인접행렬을 이용한 그래프
}GraphType;

int *visited;						//방문되었는지 확인하는 변수

void init(GraphType*g, int num);	//그래프 초기화 함수
void insert_vertex(GraphType*g, int num);	//정점 삽입 함수
void insert_edge(GraphType* g, int start, int end);	//간선 삽입 함수
void dfs_mat(GraphType*g, int v);	//깊이 우선 탐색 함수
void Delete_Graph(GraphType*g);		//그래프 삭제 함수

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
	while (!feof(fp)) {			//파일끝까지 반복하며 최대값을 찾음
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'v') {		//v를 입력받았을 때 정수 하나 더 입력받음
			fscanf(fp, "%d", &itemp1);
			if (max < itemp1) max = itemp1;	//입력받은 정수가 max보다 클때 max에 값을 삽입
		}
	}
	g = (GraphType*)malloc(sizeof(GraphType));
	max++;							//max를 1 증가시키고 초기화해야함
	init(g, max);					//그래프 초기화

	for (i = 0; i < max; i++) {		//max값만큼 정점삽입
		insert_vertex(g, max);		//간선 삽입 함수호출
	}
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%c", &ctemp);
		if (ctemp == 'e') {		//e를 입력받았을 때 간선 삽입
			fscanf(fp, "%d%d", &itemp1, &itemp2);	//간선 두 정수를 입력받고
			insert_edge(g, itemp1, itemp2);		//방향 그래프로 삽입
		}
	}
	printf("-깊이 우선 그래프 탐색 결과-\n<");

	dfs_mat(g, 0);				//깊이 우선탐색함수 호출
	printf(">\n");
	Delete_Graph(g);			//그래프 삭제
	fclose(fp);					//파일 닫음
	return 0;
}
void init(GraphType*g, int num) {		//그래프 초기화 함수
	int r;
	g->n = 0;							//정점의 개수를 0으로 초기화
	g->adj_mat = (int**)calloc(sizeof(int*), num);	//calloc으로 행렬의 행 동적할당
	for (r = 0; r < num; r++) {
		g->adj_mat[r] = (int*)calloc(sizeof(int), num);	//calloc으로 행렬의 열 동적할당
	}
	visited = (int*)calloc(sizeof(int), num);//visited변수를 num값에 맞게 동적할당
}
void insert_vertex(GraphType*g, int num) {		//정점 삽입함수
	if ((g->n) + 1 > num) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;				//정점의 개수 증가
}
void insert_edge(GraphType* g, int start, int end) {	//방향그래프로 삽입하는 함수
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;			//입력받은 start행 end열을 1을 삽입
}
void dfs_mat(GraphType*g, int v) {		//깊이 우선탐색 함수
	int w;

	visited[v] = TRUE;					//현재 정점을 방문했다고 표시
	printf("%d ", v);
	for (w = 0; w < g->n; w++) {		//정점의 개수만큼 반복
		if (g->adj_mat[v][w] && !visited[w])	//adj_mat[v][w]가 1이고 visited[w]가 방문되지 않았다면
			dfs_mat(g, w);	//순환을 통해 정점 w에서 새로 시작
	}
}
void Delete_Graph(GraphType*g) {		//그래프를 삭제하는 함수
	int i = 0;
	for (i = 0; i < g->n; i++) {		//행렬의 열 메모리 해제
		free(g->adj_mat[i]);
	}
	free(g->adj_mat);				//행렬의 행 메모리해제
	free(g);					//그래프 메모리 해제
	free(visited);				//visited변수 메모리 해제
}
