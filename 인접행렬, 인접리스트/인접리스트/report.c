/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: ���� ����Ʈ�� �̿��� �׷��� �߻� ������ Ÿ���� ����
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Element {
	char start[10];					//���� ������ �� �� ���� �����ϴ� ����ü||������ ������ ����
	char end[10];
}Element;

typedef struct GraphNode {			//���� ����Ʈ�� �����ϴ� ���
	char *vertex;
	struct GraphNode *link;
}GraphNode;
typedef struct GraphType {			//���� ����Ʈ Ÿ��
	int n;							//������ ����
	char **ary;						//������ ����
	GraphNode ** adj_list;			//���� ����Ʈ ����
}GraphType;

void init(GraphType*, int );			//�׷����� �ʱ�ȭ�ϴ� �Լ�
void insert_vertex(GraphType*, int, char* );	//������ �����ϴ� �Լ�
void insert_undirected_edge(GraphType*, Element);//������ �׷��� �����Լ�
void insert_directed_edge(GraphType*, Element);	//���� �׷��� �����Լ�
void print_adj_list(GraphType*);				//�׷����� ����Ʈ�� ���Ŀ� �°� ����ϴ� �Լ�
int Check_Node(GraphNode*, char*);				//������ �׷��� ���Խ� ���� ������ ������ Ȯ���ϴ� �Լ�
int Check_Same_String(char** , int , char *);	//���� ���Խ� �ߺ��Ǵ� ������ ������ Ȯ���ϴ� �Լ�
void Delete(GraphType*);						//�׷����� ����Ʈ�� �����ϴ� �Լ�

int main() {
	FILE *fp;
	GraphType*g, *g2;					//g�� ������׷���, g2�� ���� �׷���
	char **temp;					//temp�� ������ �̸��� �ӽ÷� �����ϴ� ���ڿ� ������ ����
	Element data;
	Element *insert_data;			//���Ͽ� �ִ� �����͸� ����
	int count = 0, num = 0;			//count�� ���Ͽ� �ִ� �������� ����, num�� ������ ����
	int i = 0;

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0;
	}
	while (!feof(fp)) {								//������ ������ ������ �������� ���� ����
		fscanf(fp, "%s%s", data.start, data.end);
		count++;
	}
	g = (GraphType*)malloc(sizeof(GraphType));		//������׷��� g�����Ҵ�
	g2= (GraphType*)malloc(sizeof(GraphType));		//����׷��� g2�����Ҵ�
	temp = (char**)malloc(sizeof(char*)*(count*2));		//temp�� ������ ������ ������ �����Ҵ�
	insert_data = (Element*)malloc(sizeof(Element)*count);	//insert_data�� ������ ������ ������ �����Ҵ�

	rewind(fp);													
	while (!feof(fp)) {
		fscanf(fp, "%s%s", data.start, data.end);
	//	printf("insert (%s, %s)\n", data.start, data.end);
		insert_data[i++] = data;						//������ ó������ �ٽ� �Է¹����� ������ ���� ����

		if (Check_Same_String(temp, num, data.start)) {	//���� temp�迭�� �Է¹��� ���ڿ��� �ִ��� Ȯ��
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.start) + 1));
			strcpy(temp[num++], data.start);	//���ٸ� ����temp���ڿ��� �����Ҵ��ϰ� ���� ����, �����Ŀ� ���� ����
		}
		if (Check_Same_String(temp, num, data.end)) {	//���� temp�迭�� �Է¹��� end���ڿ��� �ִ��� Ȯ��
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));
			strcpy(temp[num++], data.end);
		}
	}
//	printf("count = %d, num = %d\n", count, num);
//////////////////////////////////////////////////////////////////////////	
	init(g, num);											//������ �׷��� g�� �ʱ�ȭ num�� ������ ����
	init(g2, num);
	for (i = 0; i < num; i++) {									//���� �߰� num��ŭ �ݺ��ϸ� vertex�߰�
		insert_vertex(g, num, temp[i]);							//i��°�� temp���ڿ��� �����Ͽ� ������ ����
		insert_vertex(g2, num, temp[i]);
	}
	for(i=0; i<count; i++){										//������ ������ ������ count��ŭ �ݺ�
		insert_undirected_edge(g, insert_data[i]);				//������׷����� ���� data������ �����Ͽ� ��������
		insert_directed_edge(g2, insert_data[i]);				//����׷����� ���� data������ �����Ͽ� ��������
	}
	for (i = 0; i < count; i++) printf("(%s, %s), ", insert_data[i].start, insert_data[i].end);
	printf("\n-Undirected Graph-\n");
	print_adj_list(g);									//������ �׷��� ���
	for (i = 0; i < count; i++) printf("<%s, %s>, ", insert_data[i].start, insert_data[i].end);
	printf("\n-Directed Graph-\n");
	print_adj_list(g2);									//���� �׷��� ���
	
	for (i = 0; i < num; i++) 	free(temp[i]);	//temp�� ���ڿ��� �׷��� ���� ���ڿ��� ���� �ּҸ� �����Ƿ� ���ο��� �ѹ��� ������
	free(insert_data); 							//������ ������ �迭�� ���� insert_data ����
	free(temp);								
	Delete(g);								//Delete�Լ��� �׷��� �����Ҵ� ����
	Delete(g2);
	fclose(fp);								//���������� ����
	return 0;
}
int Check_Node(GraphNode*list, char*s) {				//����Ʈ���� ���� ���ڿ��� �ִ��� üũ�ϴ� �Լ�
	GraphNode*p = list;
	while (p != NULL) {
		if (strcmp(s, p->vertex) == 0)return FALSE;		//p�� ������ �ݺ��ϸ� ���� ���ڿ��� �ִٸ� FALSE����
		p = p->link;
	}
	return TRUE;
}
int Check_Same_String(char** ary, int num, char *s) {	//�迭���� ���� ���ڿ��� �ִ��� üũ�ϴ� �Լ�
	int i;
	for (i = 0; i < num; i++) {
		if (strcmp(ary[i], s) == 0)return FALSE;
	}
	return TRUE;										//���� ���� ���ڿ��� �ϳ��� ���ٸ� TRUE����
}
void init(GraphType*g, int VERTICES) {				//�׷����� �ʱ�ȭ�ϴ� �Լ�
	int v;
	g->n = 0;
	g->adj_list = (GraphNode**)malloc(sizeof(GraphNode*)*VERTICES);	//����Ʈ�� ������ ������ŭ �����Ҵ�
	g->ary = (char**)malloc(sizeof(char*)*VERTICES);				//������ �����Ҵ�
	for (v = 0; v < VERTICES; v++) {
		g->adj_list[v] = NULL;	
	}
}
void insert_vertex(GraphType*g, int VERTICES, char*temp) {		//������ �����ϴ� �Լ�
	if (((g->n) + 1) > VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}	
	g->ary[g->n] = temp;										//temp�κ��� ���� ���� �Է¹���
	g->n++;														//�ݺ��Ҷ����� ������ ���� ����
}
void insert_directed_edge(GraphType*g, Element data) {			//����׷����� �����ϴ� �Լ�
	GraphNode *node;
	int u, v, i;
	for (i = 0; i < g->n; i++) {					//���۹��ڿ��� �ε������� ���� ���ڿ��� �ε��� ���� ã��
		if (strcmp(g->ary[i], data.start) == 0) u = i;
		if (strcmp(g->ary[i], data.end) == 0) v = i;
	}
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}															//����׷����̹Ƿ� ����Ʈ �ڿ� end���� �߰��ϸ� ��
	node = (GraphNode*)malloc(sizeof(GraphNode));				//���ο� ��� ����
	node->vertex = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));	//����� ���ڿ��� end�� ���̷� �����Ҵ�
	strcpy(node->vertex, data.end);								//end���ڿ��� ����

	node->link = g->adj_list[u];								//����� link�� adj_list�� ó���� ����Ŵ(insert_first)
	g->adj_list[u] = node;										//adj_list�� head���� node�� ��
	//	printf("%d-----%s\n",u, node->vertex);
}
void insert_undirected_edge(GraphType*g, Element data) {		//������ �׷����� �����ϴ� �Լ�
	GraphNode *node;
	GraphNode *node2;
	int u, v, i;
	for (i = 0; i < g->n; i++) {					//���۹��ڿ��� �ε������� ���� ���ڿ��� �ε��� ���� ã��
		if (strcmp(g->ary[i], data.start) == 0) u = i;
		if (strcmp(g->ary[i], data.end) == 0) v = i;
	}
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));		//node�� end���ڿ��� ����
	node2 = (GraphNode*)malloc(sizeof(GraphNode));		//node2�� start���ڿ��� ����
	if (Check_Node(g->adj_list[u], data.end)) {			//���� ����Ʈ�� end���ڿ��� �����ϴ��� Ȯ��
		node->vertex = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));
		strcpy(node->vertex, data.end);				//�������� �ʴ´ٸ� node�� vertex�� �����Ҵ��ϰ� ���� ����
		node->link = g->adj_list[u];				//����� link�� ����Ʈ�� ó���� ����Ŵ
		g->adj_list[u] = node;						//����Ʈ�� ó���� node�� �ɼ� �ֵ��� ��
	}
	if (Check_Node(g->adj_list[v], data.start)) {	//���� ����Ʈ�� start���ڿ��� �����ϴ��� Ȯ��
		node2->vertex = (char*)malloc(sizeof(char)*(strlen(data.start) + 1));	
		strcpy(node2->vertex, data.start);			//�������� �ʴ´ٸ� node�� vertex�� �����Ҵ��ϰ� ���� ����
		node2->link = g->adj_list[v];
		g->adj_list[v] = node2;
	}
}
void print_adj_list(GraphType*g) {							//�׷����� ���Ŀ� �°� ����ϴ� �Լ�
	int i;
	for (i = 0; i < g->n; i++) {
		GraphNode*p = g->adj_list[i];						//����Ʈ �迭�� ���� p�� ����
		printf("���� %6s�� ���� ����Ʈ ", g->ary[i]);	//���� ���� ���
		while (p != NULL) {								//p����Ʈ�� ������ �ݺ��ϸ� ���
			printf("-> %s ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}
void Delete(GraphType*g) {				//�׷����� �����Ҵ� �����ϴ� �Լ�
	int i;	
	GraphNode *p, *q; 
	for (i = 0; i < g->n; i++) {		
		p = g->adj_list[i];				//p�� ����Ʈ �迭�� ���� �Է¹���
		q = p;
		if (p != NULL) {				//���� p�� NULL�̸� ����Ʈ�� �������� �����Ƿ� �������� ����
		//	printf("\n%d, ", i);
			while (p != NULL) {			
			//	printf("%s ", p->vertex);
				q = q->link;			//q�� ������ũ �ּҸ� ����Ŵ
				free(p->vertex); //== free(g->adj_list[i].vertex);	//���� �ּ� p�� ����Ʈ��� ����
				free(p);	// ==free(g->adj_list[i])				//p�� ����Ʈ��� ����
				p = q;												//p�� ���� �ּҸ� ����Ű�� q����
			}
		}
	}
	free(g->ary);			//ary�����迭 ���� ���ڿ��� ���ο��� temp�� ������
	free(g->adj_list);		//����Ʈ������ ����
	free(g);
}








