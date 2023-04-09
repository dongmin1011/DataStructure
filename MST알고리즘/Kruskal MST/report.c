/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: Kruskal의 MST알고리즘 프로그램
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1000		//간선이 없을 때 길이
int *parent;			//부모노드

struct Edge {	//간선을 나타내는 구조체
	int start, end, weight;	//시작, 끝, 가중치
};
typedef struct GraphType {
	int n;		//간선의 개수
	struct Edge *edges;	//간선 배열
}GraphType;

void set_init(int n);	//부모노드 초기화 함수
int set_find(int curr);	//curr가 속하는 집합 반환 함수
void set_union(int a, int b);	//두개의 원소가 속한 집합을 합치는 함수 

void Graph_init(GraphType*g, int num);		//그래프를 초기화하는 함수
void insert_edge(GraphType*g, struct Edge e);	//간선을 삽입하는 함수
int compare(const void*a, const void*b);	//qsort에 사용되는 함수
int kruskal(GraphType*g);		//kruskal 최소 비용 신장 트리 함수
void Delete(GraphType*g);		//그래프 삭제 함수
int main() {
	FILE *fp;
	struct Edge e;		//데이터를 입력받을 임시변수
	GraphType *g;		//그래프 변수
	int cost;			//kruskal로 구한 최소 비용
	int count = 0;		//파일 데이터의 개수

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open\n");
		return 0;
	}
	while (!feof(fp)) {			//파일의 데이터 개수를 구함
		fscanf(fp, "%d%d%d", &e.start, &e.end, &e.weight);	
		count++;				//데이터 개수 증가
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//그래프 생성
	Graph_init(g, count);			//그래프 초기화
	rewind(fp);		
	while (!feof(fp)) {
		fscanf(fp, "%d%d%d", &e.start, &e.end, &e.weight);
		insert_edge(g, e);		//그래프에 간선 삽입
	}
	cost = kruskal(g);			//kruskal로 최소 비용을 구함
	printf("필요한 최소 비용 : %d\n", cost);	//최소 비용 출력
	
	Delete(g);				//그래프 삭제
	fclose(fp);				//파일포인터 닫음
	return 0;
}

void set_init(int n) {	//부모노드 초기화
	int i;
	parent = (int*)malloc(sizeof(int)*n);	//부모 노드를 n값으로 동적할당
	for (i = 0; i < n; i++)			
		parent[i] = -1;		//부모노드를 -1로 초기화
}
int set_find(int curr) {	//curr가 속하는 집합을 반환
	if (parent[curr] == -1)	//만약 부모노드가 -1이라면
		return curr;		//curr리턴
	while (parent[curr] != -1)curr = parent[curr];	//부모노드가 -1이 될때까지 반복
	return curr;			//부모 노드의 값을 curr에 담음
}
void set_union(int a, int b) {	//두개의 원소가 속한 집합을 함침
	int root1 = set_find(a);	//노드 a의 루트를 찾음
	int root2 = set_find(b);	//노드 b의 루트를 찾음
	if (root1 != root2)			//두 루트를 합함
		parent[root1] = root2;	
}
//////////////////////////

void Graph_init(GraphType*g, int num) {	//그래프 초기화
	int i;
	g->n = 0;
	g->edges = (struct Edge*)malloc(sizeof(struct Edge)*(num * 2));	//num값의 2배로 간선 배열 동적할당
	for (i = 0; i < num * 2; i++) {	//초기화
		g->edges[i].start = 0;		
		g->edges[i].end = 0;
		g->edges[i].weight = INF;	//가중치 값을 INF로 초기화
	}
}
void insert_edge(GraphType*g, struct Edge e) {	//간선 삽입
	int i;
	for (i = 0; i < g->n; i++) {		//배열에 간선이 이미 존재하는지 확인
		if ((g->edges[i].end == e.start && g->edges[i].start == e.end) 
			|| (g->edges[i].start == e.start && g->edges[i].end == e.end)) {
			printf("간선 %d - %d은 이미 추가된 간선입니다.-- 제외 \n", e.start, e.end);
			return;						//만약 존재한다면 함수 리턴
		}
	}	
	g->edges[g->n].start = e.start;		//존재하지 않는다면 간선 삽입
	g->edges[g->n].end = e.end;
	g->edges[g->n].weight = e.weight;
	printf("간선 %d - %d 추가완료\n", e.start, e.end);
	g->n++;								//간선의 개수 증가
}
int compare(const void*a, const void*b) { //qsort에 사용되는 함수
	struct Edge *x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
int kruskal(GraphType*g) {	//kruskal 최소 비용 신장 트리 함수
	int edge_accepted = 0;	//현재까지 선택된 간선의 수
	int uset, vset;			//정점 u와 정점 v의 집합 번호
	struct Edge e;			//반환 받은 값을 저장할 변수
	int sum = 0;			//최소 비용을 합할 변수

	set_init(g->n);			//집합 초기화
	
	qsort(g->edges, g->n, sizeof(struct Edge), compare);		//퀵 정렬 함수
	
	printf("\n크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;
	int j;
	while (edge_accepted < (g->n)) {	//선택된 간선의 수가 정점의 개수보다 작다면 반복
		e = g->edges[i];
		uset = set_find(e.start);	//정점 u의 집합 번호
		vset = set_find(e.end);		//정점 v의 집합 번호

		for (j = 0; j < g->n; j++) {
			printf("%d ", parent[j]);
		}

		if (uset != vset) {		//서로 속한 집합이 다르다면
			printf("간선 %d - %d : %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	//두 집합을 합친다.
			sum += e.weight;		//가중치를 더함
		}
		else {		//만약 간선이 사이클을 형성한다면
			edge_accepted++;
			printf("간선 %d - %d : %d - 사이클 생성으로 제외\n", e.start, e.end, e.weight);
		}


		
		i++;
	}
	return sum;		//최소 비용 반환
}
void Delete(GraphType*g) {		//그래프 삭제 함수
	free(parent);			//부모 노드 삭제
	free(g->edges);			//간선 변수 삭제
	free(g);				//그래프 변수 삭제
}