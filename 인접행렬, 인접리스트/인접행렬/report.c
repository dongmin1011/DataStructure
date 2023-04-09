/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: ���� ����� �̿��� �׷��� �߻� ������ Ÿ���� ����
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
typedef struct Element {
	char start[10];							//���� ������ �� �� ���� ����
	char end[10];
}Element;                
typedef struct GraphType {
	int n;									//������ ����
	char **ary;								//������ ����
	int **adj_mat;							//�׷��� �迭
}GraphType;

void init(GraphType*g, int num);				//�׷��� �ʱ�ȭ �Լ�
void insert_vertex(GraphType*g, int count, char* temp);		//���� ���� ���� �Լ�
void insert_undirected_edge(GraphType*g, Element data);	//������׷��� �����Լ�
void insert_directed_edge(GraphType*g, Element data);	//����׷��� �����Լ�
void print_adj_mat(GraphType*g);							//���Ŀ� �°� �׷����� ����ϴ� �Լ�
int Check_Same_String(char** ary, int num, char *s);				//�迭�� ���� ������ �ִ��� Ȯ���ϴ� �Լ�
void Delete(GraphType*g);											//�׷����� �����͸� �����ϴ� �Լ�

int main() {
	FILE *fp;							//����������
	Element data;						//���Ϸκ��� �Է¹޴� ����
	Element *insert_data;				//���Ͽ� �ִ� �����͸� ����
	int count = 0, num = 0;				//count�� ���Ͽ� �ִ� �������� ����, num�� ������ ����
	char  **temp;					//temp�� ������ �̸��� �ӽ÷� �����ϴ� ���ڿ� ������ ����
	GraphType * g, *g2;					//g�� ������׷���, g2�� ���� �׷���
	int i=0;
	fp = fopen("data.txt", "r");		
	if (!fp) {
		printf("file not open");
		return;
	}
	while (!feof(fp)) {								//������ ������ ������ �������� ���� ����
		fscanf(fp, "%s%s", data.start, data.end);
		count++;
	}
	g = (GraphType*)malloc(sizeof(GraphType));		//������ �׷��� ����
	g2 = (GraphType*)malloc(sizeof(GraphType));		//���� �׷��� ����
	temp = (char**)malloc(sizeof(char*)*(count*2));		//������ ������ �°� temp���ڿ� �迭 �Ҵ�
	insert_data = (Element*)malloc(sizeof(Element)*count);

	rewind(fp);										//���������͸� ó������ �ǵ���
	while (!feof(fp)) {
		fscanf(fp, "%s%s", data.start, data.end);
		insert_data[i++] = data;					//���� ������ �����Ҵ��� �迭�� ���� �������� �� ����
	//	printf("%s, %s\n", data.start, data.end);											//(���������͸� ��� �ǵ����� �Է¹޴� ������ ����) 
		if (Check_Same_String(temp, num, data.start)) {		//temp�� ���� ������ �ִ��� �ľ� ���� ������ ���ٸ� TRUE����
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.start) + 1));	//start�� ������ temp�� ���ڿ��� �����Ҵ��Ͽ� temp�� ����
			strcpy(temp[num++], data.start);
		}
		if (Check_Same_String(temp, num, data.end)) {							//temp�� end�� ���� ������ �ִ��� �ľ�
			temp[num] = (char*)malloc(sizeof(char)*(strlen(data.end) + 1));		//���� ������ ���ٸ� temp�� �����Ҵ� �� ����
			strcpy(temp[num++], data.end);					//num���� �ߺ��� ������ ������ ������ �������
		}	
	}
/*
	printf("count = %d, num = %d\n", count, num);
	for (i = 0; i < num; i++) {
		printf("%s  ", temp[i]);
	}
	printf("\n\n\n");
*////////////////////////////////////////////////////////////////
	init(g, num);											//������ �׷��� g�� g2�� �ʱ�ȭ
	init(g2, num);
	for (i = 0; i < num; i++) {
		insert_vertex(g, num, temp[i]);		//�׷����� ������ ����(������ �ִ� ������ num���̹Ƿ� num�� ����)
		insert_vertex(g2, num, temp[i]);
	}
	for(i=0; i<count; i++){
		insert_undirected_edge(g, insert_data[i]);		//�׷����� ���� ����
		insert_directed_edge(g2, insert_data[i]);		//���� �׷����� ��������
	}
	for (i = 0; i < count; i++) printf("(%s, %s), ", insert_data[i].start, insert_data[i].end);	
	printf("\n-Undirected Graph-\n");
	print_adj_mat(g);									//������ �׷��� ���
	for (i = 0; i < count; i++) printf("<%s, %s>, ", insert_data[i].start, insert_data[i].end);
	printf("\n-Directed Graph-\n");
	print_adj_mat(g2);									//���� �׷��� ���
//	printf("%d, %d", count, num);
	for (i = 0; i < num; i++) 	free(temp[i]);	//temp�� ���ڿ��� �׷��� ���� ���ڿ��� ���� �ּҸ� �����Ƿ� ���ο��� �ѹ��� ������
	free(temp);					//���� Delete�Լ����� ary�� �����ϸ� ������, ���⿡�� �ι� �����ϴ� ���� �ǹ���
	free(insert_data);					//������ ������ �迭�� ���� insert_data ����
	Delete(g);								//Delete�Լ��� �׷��� �����Ҵ� ����
	Delete(g2);
	fclose(fp);							//���������� ����
	return 0;
}
int Check_Same_String(char** ary, int num, char *s) {	//������ ã�� �� ���� ���ڿ��� �ִ��� Ȯ���ϴ� �Լ�
	int i;
	for (i = 0; i < num; i++) {						//���ڿ� �迭�� ó������ ������ ���� �Է¹��� ���ڿ��� ������ Ȯ��
		if (strcmp(ary[i], s) == 0)return FALSE;	//���� ���� ���ڿ��� �����Ѵٸ� FALSE����
	}
	return TRUE;
}
void init(GraphType*g, int num) {							//�׷����� �ʱ�ȭ�ϴ� �Լ�
	int r;
	g->n = 0;												//������ ���� �ʱ�ȭ
	g->adj_mat = (int**)calloc(num, sizeof(int*));			//���������� adj_mat�� calloc�� �̿��� �ʱ�ȭ(0���� �ʱ�ȭ��)
	g->ary = (char**)malloc(sizeof(char*)*num);				//ary�� numũ�⸸ŭ �����Ҵ�(num�� ������ ������ ����)
	for (r = 0; r < num; r++) {
		g->adj_mat[r] = (int*)calloc(num, sizeof(int));
	}
}
void insert_vertex(GraphType*g, int count, char *temp) {//������ �����ϴ� �Լ� count�� ���ο����� num��(������ ����)
	if (((g->n) + 1) > count) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->ary[g->n] = temp;									//ary���� ���ڿ� �迭�� temp�� ����
	g->n++;													//������ ���� ����
}
void insert_undirected_edge(GraphType*g, Element data) {	//������׷��� �����Լ�
	int i, start, end;

	for (i = 0; i < g->n; i++) {
		if (strcmp(g->ary[i], data.start) == 0) start = i;	//���۹��ڿ��� �ε������� ���� ���ڿ��� �ε��� ���� ã��
		if (strcmp(g->ary[i], data.end) == 0)end = i;
	}
	if (start >= g->n || end >= g->n) {						//���� �ε��� ���� �׷��� ������ ũ�ٸ� ����
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;								//������׷����̹Ƿ� ���� �ݴ� �ε����� ����
	g->adj_mat[end][start] = 1;
}
void insert_directed_edge(GraphType*g, Element data) {	//����׷��� �����Լ�
	int i, start, end;
	for (i = 0; i < g->n; i++) {							//���۹��ڿ��� �ε������� ���� ���ڿ��� �ε��� ���� ã��
		if (strcmp(g->ary[i], data.start) == 0) start = i;
		if (strcmp(g->ary[i], data.end) == 0) end = i;
	}
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;							//����׷����̹Ƿ� ���� �ε������� ����
}
void print_adj_mat(GraphType*g) {			//�׷��� ����Լ�
	int i, j;

	printf(" %6c | ", ' ');
	for (i = 0; i < g->n; i++) {
		printf("%7s", g->ary[i]);					//ary�迭�� ���� ���
	}
	printf("\n--------|-");
	for (i = 0; i < g->n; i++) printf("-------");	//������ ���� �°� ǥ���̰� �޶���
	
	for (i = 0; i < g->n; i++) {
		printf("\n %-6s |", g->ary[i]);				//�� ���� ���� ���
		for (j = 0; j < g->n; j++) {
			printf("%6d ", g->adj_mat[i][j]);		//���� ������ 1, ������ 0 ���
		}
	}
	printf("\n\n");
}

void Delete(GraphType*g) {			//�׷��� ������ �����ϴ� �Լ�
	int i;
	for (i = 0; i < g->n; i++) {//������ ������ŭ �ݺ��ϸ� 2���� �迭 �����Ҵ��� ����
		free(g->adj_mat[i]);	//ary���ڿ� �迭�� �����Լ����� temp�� �����Ϸ�
	}
	free(g->ary);				//ary������ ����
	free(g->adj_mat);			//2���� �迭 adj_mat����
	free(g);					//�׷��� ����
}
