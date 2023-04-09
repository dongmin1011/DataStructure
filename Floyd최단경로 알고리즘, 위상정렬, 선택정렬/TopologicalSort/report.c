/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: �������� �˰��� ���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct GraphNode {	//�׷��� ��� ����ü ����
	char *subject;			//���� ���ڿ� ����
	int vertex;				//���� ���� ����
	struct GraphNode *link;	//���� ��带 ����Ű�� ��ũ
}GraphNode;
typedef struct Vertex {		//������ ������ ������ ����ü
	int num;				//���� ���� ����
	char *str;				//���� ���ڿ� ����
}Vertex;
typedef struct GraphType {	//�׷��� Ÿ�� ����ü ����
	int n;					//������ ���� n����
	Vertex *ary;			//������ ������ ������ Vertex�ڷ��� ������ ����
	GraphNode **adj_list;	//��ũ����Ʈ�� ������ �׷��� ��� ������ ����
}GraphType;

int Find_index(Vertex list[], int find, int count);	//���� �迭���� �ε��� ���� ã�� �Լ�
void graph_init(GraphType *g, int n);	//�׷��� �ʱ�ȭ �Լ�
void insert_vertex(GraphType*g, int v, int index, char *str);	//���� �����Լ�
void insert_edge(GraphType*g, int start, int end);		//���� �����Լ�, ���� ����Ʈ�� ����
int topo_sort(GraphType *g);			//�������� �Լ�
void Delete(GraphType *g);			//�׷��� ���� �Լ�
 void print_adj_list(GraphType*g) {							//�׷����� ���Ŀ� �°� ����ϴ� �Լ�
	int i;
	for (i = 0; i < g->n; i++) {
		GraphNode*p = g->adj_list[i];						//����Ʈ �迭�� ���� p�� ����
		printf("���� %6s�� ���� ����Ʈ ", g->ary[i].str);	//���� ���� ���
		while (p != NULL) {								//p����Ʈ�� ������ �ݺ��ϸ� ���
			printf("-> %d ", p->vertex);
			printf(" %s ", p->subject);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}

typedef int element;
typedef struct {						//���� Ÿ�� ����ü ����
	element *stack;						//element�� ���� ������
	int Stack_size;						//���� ������ ����
	int top;							//���� ������ ��ġ ����
}StackType;

void init(StackType *s, int n) {		//���� �ʱ�ȭ �Լ�
	s->top = -1;						//top���� -1�� �ʱ�ȭ
	s->stack = (element*)malloc(sizeof(element)*n);	//n������ ���� �迭 �����Ҵ�
	s->Stack_size = n;					//������ ũ�⸦ n������ ����
}
int is_empty(StackType *s) {			//������ ����������� Ȯ��
	return (s->top == -1);				//top���� -1�̸� TRUE����
}
int is_full(StackType*s) {				//������ ��ȭ�������� Ȯ��
	return(s->top == (s->Stack_size - 1));	//top���� size-1�̸� TRUE����
}
void push(StackType*s, element item) {		//���ÿ� ���� �����ϴ� �Լ�
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	s->stack[++(s->top)] = item;		//top�� ������Ű�� item������ ���ÿ� ����
}
element pop(StackType*s) {			//���ÿ��� pop�ϴ� �Լ�
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	return s->stack[s->top--];		//top�� �ε����� �����ϰ� ����
}


int main() {
	FILE *fp;				//����������
	GraphType *g;			//�׷��� ����
	char str[20], *stemp;	//���Ϸκ��� ���ڿ��� �Է¹��� ����
	int temp1, temp2;		//���Ϸκ��� ������ �Է¹��� ����
	char c;					//� ������ ���� �Է�
	int count = 0, i;

	fp = fopen("data.txt", "r");	//������ �б��������� open
	if (!fp) {
		printf("file not opne");
		return 0;
	}
	while (!feof(fp)) {				//���ϳ����� �ݺ�
		fscanf(fp, "%c", &c);
		if (c == 'v') {				//v�� ���������� ��Ÿ��
			fscanf(fp, "%d%s", &temp1, str);
			count++;				//������ ���� ����
		}
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//�׷��� �����Ҵ� ����
	rewind(fp);					//���������͸� ó������ �ű�
	graph_init(g, count);		//count���� �׷��� �ʱ�ȭ
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);	//���� ������ �Է�
		if (c == 'v') {			//v�� ���� ���� ���� ����
			fscanf(fp, "%d%s", &temp1, str);
			stemp = (char*)malloc(sizeof(char)*(strlen(str)+1));//stemp�� str�� ���̷� �����Ҵ�	
			strcpy(stemp, str);		//str���� stemp�� ����
			insert_vertex(g, count, temp1, stemp);	//���� ����
		}
	}

	rewind(fp);				//���������͸� ó������ �ű�
	while (!feof(fp)) {
		fscanf(fp, "%c", &c);
		if (c == 'e') {		//e�� ���� ���� ���� ����
			fscanf(fp, "%d%d", &temp1, &temp2);
			insert_edge(g, temp1, temp2);	//���� ���� insert_edgeȣ��
		}
	}
	printf("< ������ >\n");
	printf("------------------\n");
	for (i = 0; i < count; i++) {
		printf("%-2d - %s\n", g->ary[i].num, g->ary[i].str);	//�������� �� ���� ���� ���
	}
	printf("------------------\n\n");
	topo_sort(g);				//�������� �Լ� ȣ��
	Delete(g);					//�׷��� ����
	fclose(fp);					//���� ������ ����
	return 0;
}
int Find_index(Vertex list[], int find, int count) {	//���� �迭���� �ε��� ���� ã�� �Լ�
	int i;
	for (i = 0; i < count; i++) {
		if (list[i].num == find) return i;	//���� ������ ���� ���� ã���� ���� �ε��� ����
	}
	return -1;		//���� ���� �ε����� ���ٸ� -1����
}

void graph_init(GraphType *g, int n) {	//�׷��� �ʱ�ȭ �Լ�
	int v;
	g->n = 0;			//������ ���� �ʱ�ȭ
	g->adj_list = (GraphNode**)malloc(sizeof(GraphNode*)*n);	//��ũ����Ʈ �ʱ�ȭ
	for (v = 0; v < n; v++) {
		g->adj_list[v] = NULL;	//�ʱⰪ�� NULL����
	}
	g->ary = (Vertex*)malloc(sizeof(Vertex)*n);		//���� ary�迭 �ʱ�ȭ
}
void insert_vertex(GraphType*g, int v, int index, char *str) {	//���� �����Լ�
	if (((g->n) + 1) > v) {
		fprintf(stderr, "�׷��� : ������ ���� �ʰ�");
		return;
	}
	g->ary[g->n].num = index;	//ary���� �迭�� ���� �� ����
	g->ary[g->n].str = str;
	g->n++;		//������ ���� ����
}

void insert_edge(GraphType*g, int start, int end) {		//���� �����Լ�, ���� ����Ʈ�� ����
	GraphNode *node;
	int u = 0, v = 0;						//�迭�� ���� ���� ���� �ε��� ���� ����

	u = Find_index(g->ary, start, g->n); //ary���� Find_index�Լ��� ���� �ε������� ã��
	v = Find_index(g->ary, end, g->n);
	//	printf("%d, %d\n", u, v);
	if (u >= g->n || v >= g->n) {			//���� �ε��� ���� ���� �������� ũ�ٸ� ����
		fprintf(stderr, "�׷��� : ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode)); //��带 ���� ����

	node->vertex = g->ary[v].num;		//����� vertex���� ary�� ����
	node->subject = g->ary[v].str;

	node->link = g->adj_list[u];		//insert_first���� ����
	g->adj_list[u] = node;				//ù ����� ��ũ�� ���� ����Ʈ�� ����Ű��
}											//����Ʈ�� ó���� node�� ��

int topo_sort(GraphType *g) {			//�������� �Լ�
	int i;
	StackType s;						//���� ����
	GraphNode *node;					//�ӽ� ��� ����
	int count = 0, n = 0;
	int *in_degree = (int *)malloc(g->n * sizeof(int));
	//��� ������ ���� ������ ���
	for (i = 0; i < g->n; i++) {
		in_degree[i] = 0;			//in_degree�� 0���� �ʱ�ȭ
	}
	
	for (i = 0; i < g->n; i++) {
		GraphNode *node = g->adj_list[i];	//���� i���� ������ ������
		while (node != NULL) {
			n = Find_index(g->ary, node->vertex, g->n);	//�����迭���� �ε��� ���� ã��
			in_degree[n]++;					//�� �ε����� �´� in_degree�� ����
			node = node->link;
		}
	}
	/*	for (i = 0; i < g->n; i++) {
			printf("%d ", in_degree[i]);
		}
		printf("\n\n");
		*/
	init(&s, g->n);						//���� �ʱ�ȭ
	for (i = 0; i < g->n; i++) {	//���� ������ 0�� ������ ���ÿ� ����
		if (in_degree[i] == 0)push(&s, i);
	}
	printf("< ���� ���� ��� >\n");
	printf("------------------\n");
	while (!is_empty(&s)) {			//������ ������°� �ɶ����� �ݺ�
		int w;
		
		w = pop(&s);				//���� ���������� ���Ե� �ε��� ���� pop
		printf("%d. %-2d  - %s\n", ++count, g->ary[w].num, g->ary[w].str);	//pop�� �ε��� ���� �´� ���� ���
		node = g->adj_list[w];		//�� ������ ���� ������ ����
		while (node != NULL) {
			n = Find_index(g->ary, node->vertex, g->n);	//�����迭���� �ε��� ���� ã��
			in_degree[n]--;			//ã�� �ε��� ���� ���� ������ ����
			if (in_degree[n] == 0)push(&s, n);	//���� ������ 0�� �����ε����� ����
			node = node->link;

		}
		
	}
	printf("------------------\n");
	free(in_degree);		//in_degree�迭 ����
	free(s.stack);			//���� ����
	printf("\n");
	return (i == g->n);
}
void Delete(GraphType *g) {			//�׷��� ���� �Լ�
	int i;
	GraphNode *p, *q;
	for (i = 0; i < g->n; i++) {
		free(g->ary[i].str);		//ary�迭�� str���ڿ� ����
		p = g->adj_list[i];
		q = p;
		if (p != NULL) {
			while (p != NULL) {
				q = q->link;
				free(p);		//��ũ����Ʈ ���� 
				p = q;
			}
		}
		
	}
	//����Ʈ�� ������ str�� ���� ������ �����Ƿ� ���� x
	free(g->ary);			//ary������ ����
	free(g->adj_list);		//adj_list����
	free(g);				//�׷��� ����
}