/*
	학번 : 20184612
	학과 : 컴퓨터소프트웨어공학과
	이름 : 김동민
	파일 명: 인접 리스트를 이용한 그래프 추상 데이터 타입의 구현
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Element {
	char start[10];					//삽입 연산을 할 때 값을 전달하는 구조체||데이터 파일을 저장
	char end[10];
}Element;

typedef struct GraphNode {			//간선 리스트를 저장하는 노드
	char *vertex;
	struct GraphNode *link;
}GraphNode;
typedef struct GraphType {			//간선 리스트 타입
	int n;							//정점의 개수
	char **ary;						//정점의 정보
	GraphNode ** adj_list;			//간선 리스트 정보
}GraphType;

void init(GraphType*, int );			//그래프를 초기화하는 함수
void insert_vertex(GraphType*, int, char* );	//정점을 삽입하는 함수
void insert_undirected_edge(GraphType*, Element);//무방향 그래프 삽입함수
void insert_directed_edge(GraphType*, Element);	//방향 그래프 삽입함수
void print_adj_list(GraphType*);				//그래프와 리스트를 형식에 맞게 출력하는 함수
int Check_Node(GraphNode*, char*);				//무방향 그래프 삽입시 같은 간선이 없도록 확인하는 함수
int Check_Same_String(char** , int , char *);	//정점 삽입시 중복되는 정점이 없도록 확인하는 함수
void Delete(GraphType*);						//그래프와 리스트를 삭제하는 함수

int main() {
	FILE *fp;
	GraphType*g, *g2;					//g는 무방향그래프, g2는 방향 그래프
	char **temp;					//temp는 정점의 이름을 임시로 저장하는 문자열 포인터 변수
	Element data;
	Element *insert_data;			//파일에 있는 데이터를 저장
	int count = 0, num = 0;			//count는 파일에 있는 데이터의 개수, num은 정점의 개수
	int i = 0;

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {								//파일을 끝까지 읽으며 데이터의 개수 증가
		fscanf(fp, "%s%s", data.start, data.end);
		count++;
	}
	g = (GraphType*)malloc(sizeof(GraphType));		//무방향그래프 g동적할당
	g2= (GraphType*)malloc(sizeof(GraphType));		//방향그래프 g2동적할당
	temp = (char**)malloc(sizeof(char*)*(count*2));		//temp를 데이터 파일의 개수로 동적할당
	insert_data = (Element*)malloc(sizeof(Element)*count);	//insert_data를 데이터 파일의 개수로 동적할당

	rewind(fp);													
	while (!feof(fp)) {
		fscanf(fp, "%s%s", data.start, data.end);
	//	printf("insert (%s, %s)\n", data.start, data.end);
		insert_data[i++] = data;						//파일을 처음부터 다시 입력받으며 데이터 파일 저장

		if (Check_Same_String(temp, num, data.start)) {	//현재 temp배열에 입력받은 문자열이 있는지 확인
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.start) + 1));
			strcpy(temp[num++], data.start);	//없다면 현재temp문자열을 동적할당하고 값을 저장, 저장후엔 개수 증가
		}
		if (Check_Same_String(temp, num, data.end)) {	//현재 temp배열에 입력받은 end문자열이 있는지 확인
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));
			strcpy(temp[num++], data.end);
		}
	}
//	printf("count = %d, num = %d\n", count, num);
//////////////////////////////////////////////////////////////////////////	
	init(g, num);											//무방향 그래프 g를 초기화 num은 정점의 개수
	init(g2, num);
	for (i = 0; i < num; i++) {									//정점 추가 num만큼 반복하며 vertex추가
		insert_vertex(g, num, temp[i]);							//i번째의 temp문자열을 전달하여 정점에 삽입
		insert_vertex(g2, num, temp[i]);
	}
	for(i=0; i<count; i++){										//데이터 파일의 개수인 count만큼 반복
		insert_undirected_edge(g, insert_data[i]);				//무방향그래프에 현재 data파일을 전달하여 간선삽입
		insert_directed_edge(g2, insert_data[i]);				//방향그래프에 현재 data파일을 전달하여 간선삽입
	}
	for (i = 0; i < count; i++) printf("(%s, %s), ", insert_data[i].start, insert_data[i].end);
	printf("\n-Undirected Graph-\n");
	print_adj_list(g);									//무방향 그래프 출력
	for (i = 0; i < count; i++) printf("<%s, %s>, ", insert_data[i].start, insert_data[i].end);
	printf("\n-Directed Graph-\n");
	print_adj_list(g2);									//방향 그래프 출력
	
	for (i = 0; i < num; i++) 	free(temp[i]);	//temp의 문자열은 그래프 정점 문자열과 같은 주소를 가지므로 메인에서 한번만 해제함
	free(insert_data); 							//파일의 데이터 배열을 담은 insert_data 해제
	free(temp);								
	Delete(g);								//Delete함수로 그래프 동적할당 해제
	Delete(g2);
	fclose(fp);								//파일포인터 닫음
	return 0;
}
int Check_Node(GraphNode*list, char*s) {				//리스트에서 같은 문자열이 있는지 체크하는 함수
	GraphNode*p = list;
	while (p != NULL) {
		if (strcmp(s, p->vertex) == 0)return FALSE;		//p를 끝까지 반복하며 같은 문자열이 있다면 FALSE리턴
		p = p->link;
	}
	return TRUE;
}
int Check_Same_String(char** ary, int num, char *s) {	//배열에서 같은 문자열이 있는지 체크하는 함수
	int i;
	for (i = 0; i < num; i++) {
		if (strcmp(ary[i], s) == 0)return FALSE;
	}
	return TRUE;										//만약 같은 문자열이 하나도 없다면 TRUE리턴
}
void init(GraphType*g, int VERTICES) {				//그래프를 초기화하는 함수
	int v;
	g->n = 0;
	g->adj_list = (GraphNode**)malloc(sizeof(GraphNode*)*VERTICES);	//리스트를 정점의 개수만큼 동적할당
	g->ary = (char**)malloc(sizeof(char*)*VERTICES);				//정점을 동적할당
	for (v = 0; v < VERTICES; v++) {
		g->adj_list[v] = NULL;	
	}
}
void insert_vertex(GraphType*g, int VERTICES, char*temp) {		//정점을 삽입하는 함수
	if (((g->n) + 1) > VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}	
	g->ary[g->n] = temp;										//temp로부터 정점 값을 입력받음
	g->n++;														//반복할때마다 정점의 개수 증가
}
void insert_directed_edge(GraphType*g, Element data) {			//방향그래프에 삽입하는 함수
	GraphNode *node;
	int u, v, i;
	for (i = 0; i < g->n; i++) {					//시작문자열의 인덱스값과 도착 문자열의 인덱스 값을 찾음
		if (strcmp(g->ary[i], data.start) == 0) u = i;
		if (strcmp(g->ary[i], data.end) == 0) v = i;
	}
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}															//방향그래프이므로 리스트 뒤에 end값만 추가하면 됨
	node = (GraphNode*)malloc(sizeof(GraphNode));				//새로운 노드 생성
	node->vertex = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));	//노드의 문자열을 end의 길이로 동적할당
	strcpy(node->vertex, data.end);								//end문자열을 복사

	node->link = g->adj_list[u];								//노드의 link가 adj_list의 처음을 가리킴(insert_first)
	g->adj_list[u] = node;										//adj_list의 head값이 node가 됨
	//	printf("%d-----%s\n",u, node->vertex);
}
void insert_undirected_edge(GraphType*g, Element data) {		//무방향 그래프에 삽입하는 함수
	GraphNode *node;
	GraphNode *node2;
	int u, v, i;
	for (i = 0; i < g->n; i++) {					//시작문자열의 인덱스값과 도착 문자열의 인덱스 값을 찾음
		if (strcmp(g->ary[i], data.start) == 0) u = i;
		if (strcmp(g->ary[i], data.end) == 0) v = i;
	}
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));		//node는 end문자열을 저장
	node2 = (GraphNode*)malloc(sizeof(GraphNode));		//node2는 start문자열을 저장
	if (Check_Node(g->adj_list[u], data.end)) {			//현재 리스트에 end문자열이 존재하는지 확인
		node->vertex = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));
		strcpy(node->vertex, data.end);				//존재하지 않는다면 node의 vertex를 동적할당하고 값을 복사
		node->link = g->adj_list[u];				//노드의 link가 리스트의 처음을 가리킴
		g->adj_list[u] = node;						//리스트의 처음이 node가 될수 있도록 함
	}
	if (Check_Node(g->adj_list[v], data.start)) {	//현재 리스트에 start문자열이 존재하는지 확인
		node2->vertex = (char*)malloc(sizeof(char)*(strlen(data.start) + 1));	
		strcpy(node2->vertex, data.start);			//존재하지 않는다면 node의 vertex를 동적할당하고 값을 복사
		node2->link = g->adj_list[v];
		g->adj_list[v] = node2;
	}
}
void print_adj_list(GraphType*g) {							//그래프를 형식에 맞게 출력하는 함수
	int i;
	for (i = 0; i < g->n; i++) {
		GraphNode*p = g->adj_list[i];						//리스트 배열의 값을 p에 저장
		printf("정점 %6s의 인접 리스트 ", g->ary[i]);	//현재 정점 출력
		while (p != NULL) {								//p리스트의 끝까지 반복하며 출력
			printf("-> %s ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}
void Delete(GraphType*g) {				//그래프를 동적할당 해제하는 함수
	int i;	
	GraphNode *p, *q; 
	for (i = 0; i < g->n; i++) {		
		p = g->adj_list[i];				//p에 리스트 배열의 값을 입력받음
		q = p;
		if (p != NULL) {				//만약 p가 NULL이면 리스트가 존재하지 않으므로 해제하지 않음
		//	printf("\n%d, ", i);
			while (p != NULL) {			
			//	printf("%s ", p->vertex);
				q = q->link;			//q가 다음링크 주소를 가리킴
				free(p->vertex); //== free(g->adj_list[i].vertex);	//현재 주소 p의 리스트노드 해제
				free(p);	// ==free(g->adj_list[i])				//p의 리스트노드 해제
				p = q;												//p에 다음 주소를 가리키는 q저장
			}
		}
	}
	free(g->ary);			//ary정점배열 해제 문자열은 메인에서 temp로 해제함
	free(g->adj_list);		//리스트포인터 해제
	free(g);
}








