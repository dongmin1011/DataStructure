/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 인접 행렬을 이용한 그래프 추상 데이터 타입의 구현
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
typedef struct Element {
	char start[10];							//삽입 연산을 할 때 값을 전달
	char end[10];
}Element;                
typedef struct GraphType {
	int n;									//정점의 개수
	char **ary;								//정점의 정보
	int **adj_mat;							//그래프 배열
}GraphType;

void init(GraphType*g, int num);				//그래프 초기화 함수
void insert_vertex(GraphType*g, int count, char* temp);		//정점 삽입 연산 함수
void insert_undirected_edge(GraphType*g, Element data);	//무방향그래프 삽입함수
void insert_directed_edge(GraphType*g, Element data);	//방향그래프 삽입함수
void print_adj_mat(GraphType*g);							//형식에 맞게 그래프를 출력하는 함수
int Check_Same_String(char** ary, int num, char *s);				//배열에 같은 정점이 있는지 확인하는 함수
void Delete(GraphType*g);											//그래프의 포인터를 해제하는 함수

int main() {
	FILE *fp;							//파일포인터
	Element data;						//파일로부터 입력받는 변수
	Element *insert_data;				//파일에 있는 데이터를 저장
	int count = 0, num = 0;				//count는 파일에 있는 데이터의 개수, num은 정점의 개수
	char  **temp;					//temp는 정점의 이름을 임시로 저장하는 문자열 포인터 변수
	GraphType * g, *g2;					//g는 무방향그래프, g2는 방향 그래프
	int i=0;
	fp = fopen("data.txt", "r");		
	if (!fp) {
		printf("file not open");
		return;
	}
	while (!feof(fp)) {								//파일을 끝까지 읽으며 데이터의 개수 증가
		fscanf(fp, "%s%s", data.start, data.end);
		count++;
	}
	g = (GraphType*)malloc(sizeof(GraphType));		//무방향 그래프 생성
	g2 = (GraphType*)malloc(sizeof(GraphType));		//방향 그래프 생성
	temp = (char**)malloc(sizeof(char*)*(count*2));		//파일의 개수에 맞게 temp문자열 배열 할당
	insert_data = (Element*)malloc(sizeof(Element)*count);

	rewind(fp);										//파일포인터를 처음으로 되돌림
	while (!feof(fp)) {
		fscanf(fp, "%s%s", data.start, data.end);
		insert_data[i++] = data;					//파일 개수로 동적할당한 배열에 파일 데이터의 값 삽입
	//	printf("%s, %s\n", data.start, data.end);											//(파일포인터를 계속 되돌리고 입력받는 동작을 줄임) 
		if (Check_Same_String(temp, num, data.start)) {		//temp에 같은 정점이 있는지 파악 같은 정점이 없다면 TRUE리턴
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.start) + 1));	//start의 개수로 temp의 문자열을 동적할당하여 temp에 저장
			strcpy(temp[num++], data.start);
		}
		if (Check_Same_String(temp, num, data.end)) {							//temp에 end와 같은 정점이 있는지 파악
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));		//같은 정점이 없다면 temp를 동적할당 후 저장
			strcpy(temp[num++], data.end);					//num에는 중복을 제외한 정점의 개수가 담겨있음
		}	
	}
/*
	printf("count = %d, num = %d\n", count, num);
	for (i = 0; i < num; i++) {
		printf("%s  ", temp[i]);
	}
	printf("\n\n\n");
*////////////////////////////////////////////////////////////////
	init(g, num);											//무방향 그래프 g와 g2를 초기화
	init(g2, num);
	for (i = 0; i < num; i++) {
		insert_vertex(g, num, temp[i]);		//그래프에 정점을 삽입(정점의 최대 개수는 num개이므로 num을 전달)
		insert_vertex(g2, num, temp[i]);
	}
	for(i=0; i<count; i++){
		insert_undirected_edge(g, insert_data[i]);		//그래프에 간선 삽입
		insert_directed_edge(g2, insert_data[i]);		//방향 그래프에 간선삽입
	}
	for (i = 0; i < count; i++) printf("(%s, %s), ", insert_data[i].start, insert_data[i].end);	
	printf("\n-Undirected Graph-\n");
	print_adj_mat(g);									//무방향 그래프 출력
	for (i = 0; i < count; i++) printf("<%s, %s>, ", insert_data[i].start, insert_data[i].end);
	printf("\n-Directed Graph-\n");
	print_adj_mat(g2);									//방향 그래프 출력
//	printf("%d, %d", count, num);
	for (i = 0; i < num; i++) 	free(temp[i]);	//temp의 문자열은 그래프 정점 문자열과 같은 주소를 가지므로 메인에서 한번만 해제함
	free(temp);					//만약 Delete함수에서 ary를 해제하면 무방향, 방향에서 두번 해제하는 것이 되버림
	free(insert_data);					//파일의 데이터 배열을 담은 insert_data 해제
	Delete(g);								//Delete함수로 그래프 동적할당 해제
	Delete(g2);
	fclose(fp);							//파일포인터 닫음
	return 0;
}
int Check_Same_String(char** ary, int num, char *s) {	//정점을 찾을 때 같은 문자열이 있는지 확인하는 함수
	int i;
	for (i = 0; i < num; i++) {						//문자열 배열을 처음부터 끝까지 돌며 입력받은 문자열과 같은지 확인
		if (strcmp(ary[i], s) == 0)return FALSE;	//만약 같은 문자열이 존재한다면 FALSE리턴
	}
	return TRUE;
}
void init(GraphType*g, int num) {							//그래프를 초기화하는 함수
	int r;
	g->n = 0;												//정점의 개수 초기화
	g->adj_mat = (int**)calloc(num, sizeof(int*));			//이중포인터 adj_mat를 calloc을 이용해 초기화(0으로 초기화됨)
	g->ary = (char**)malloc(sizeof(char*)*num);				//ary를 num크기만큼 동적할당(num은 정점의 개수와 같음)
	for (r = 0; r < num; r++) {
		g->adj_mat[r] = (int*)calloc(num, sizeof(int));
	}
}
void insert_vertex(GraphType*g, int count, char *temp) {//정점을 삽입하는 함수 count는 메인에서의 num값(정점의 개수)
	if (((g->n) + 1) > count) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->ary[g->n] = temp;									//ary정점 문자열 배열에 temp값 삽입
	g->n++;													//정점의 개수 증가
}
void insert_undirected_edge(GraphType*g, Element data) {	//무방향그래프 삽입함수
	int i, start, end;

	for (i = 0; i < g->n; i++) {
		if (strcmp(g->ary[i], data.start) == 0) start = i;	//시작문자열의 인덱스값과 도착 문자열의 인덱스 값을 찾음
		if (strcmp(g->ary[i], data.end) == 0)end = i;
	}
	if (start >= g->n || end >= g->n) {						//만약 인덱스 값이 그래프 값보다 크다면 종료
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;								//무방향그래프이므로 서로 반대 인덱스에 저장
	g->adj_mat[end][start] = 1;
}
void insert_directed_edge(GraphType*g, Element data) {	//방향그래프 삽입함수
	int i, start, end;
	for (i = 0; i < g->n; i++) {							//시작문자열의 인덱스값과 도착 문자열의 인덱스 값을 찾음
		if (strcmp(g->ary[i], data.start) == 0) start = i;
		if (strcmp(g->ary[i], data.end) == 0) end = i;
	}
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;							//방향그래프이므로 한쪽 인덱스에만 저장
}
void print_adj_mat(GraphType*g) {			//그래프 출력함수
	int i, j;

	printf(" %6c | ", ' ');
	for (i = 0; i < g->n; i++) {
		printf("%7s", g->ary[i]);					//ary배열의 정점 출력
	}
	printf("\n--------|-");
	for (i = 0; i < g->n; i++) printf("-------");	//정점의 수에 맞게 표길이가 달라짐
	
	for (i = 0; i < g->n; i++) {
		printf("\n %-6s |", g->ary[i]);				//행 값에 정점 출력
		for (j = 0; j < g->n; j++) {
			printf("%6d ", g->adj_mat[i][j]);		//길이 있으면 1, 없으면 0 출력
		}
	}
	printf("\n\n");
}

void Delete(GraphType*g) {			//그래프 정보를 삭제하는 함수
	int i;
	for (i = 0; i < g->n; i++) {//정점의 개수만큼 반복하며 2차원 배열 동적할당을 해제
		free(g->adj_mat[i]);	//ary문자열 배열은 메인함수에서 temp로 해제완료
	}
	free(g->ary);				//ary포인터 해제
	free(g->adj_mat);			//2차원 배열 adj_mat해제
	free(g);					//그래프 해제
}
