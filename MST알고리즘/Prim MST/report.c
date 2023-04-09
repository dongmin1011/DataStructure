/*
	�й� : 20184612
	�а� : ��ǻ�ͼ���Ʈ������а�
	�̸� : �赿��
	���� ��: Prim�� MST���α׷�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

#define TRUE 1
#define FALSE 0

#define INF 1000

typedef struct GraphType{
	int  n;			//������ ����
	int **weight;	// ���� ��� �׷��� ������
}GraphType;

int *selected;		//������ �湮�Ǿ����� ��Ƴ��� ����
int *distance;		//����ġ�� ����Ǿ��ִ� ����

void init(GraphType*g, int num);		//�׷���, selected, distance ���� �ʱ�ȭ �Լ�

void insert_vertex(GraphType*g, int num);	//���� ���� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight);	//���� ���� �Լ�(������׷���)

int get_min_vertex(int n);		//�ּ� dist[v] ���� ���� ���� ��ȯ�Լ�
void prim(GraphType*g, int s);	//Prim �ּ� ��� ���� Ʈ�� �Լ�
void Delete(GraphType*g);		//�׷��� ���� �Լ�

int main() {
	FILE *fp;
	GraphType *g;
	int max = INT_MIN;			//max�� int�� �ּҰ� ����
	int start, end, weight;		//�����͸� �Է¹��� �ӽú���
	int i;

	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("file not open");
		return 0; 
	}
	while (!feof(fp)) {
		fscanf(fp, "%d%d%d", &start, &end, &weight);
		if (max < start)max = start;	//start�� end�߿��� ���� ū ������ ���� ã��
		if (max < end)max = end;
	}
	g = (GraphType*)malloc(sizeof(GraphType));	//�׷��� ����
	max++;
	init(g, max);		//max������ �ʱ�ȭ

	for (i = 0; i < max; i++) {	//���� ����
		insert_vertex(g, max);
	}
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%d%d%d", &start, &end, &weight);
		insert_edge(g, start, end, weight);	//�׷����� ���� ����
	}
	prim(g, 0);	//prim �ּ� ��� ����Ʈ�� �Լ� ȣ�� (0���� ����)

	Delete(g);	//�׷��� ���� �Լ� 
	fclose(fp);
	return 0;
}
void init(GraphType*g, int num) {		//�ʱ�ȭ �Լ�
	int i, j;
	g->n = 0;
	g->weight = (int**)malloc(sizeof(int*)*num);	//num������ weight�����Ҵ�
	selected = (int*)malloc(sizeof(int)*num);		//num������ selected�����Ҵ�
	distance = (int*)malloc(sizeof(int)*num);		//num������ distance�����Ҵ�
	for (i = 0; i < num; i++) {
		g->weight[i] = (int*)malloc(sizeof(int)*num);	//�׷��� �� �����Ҵ�
		selected[i] = 0;
		distance[i] = 0;
		for (j = 0; j < num; j++) {
			g->weight[i][j] = INF;	//�׷����� ���� INF�� �ʱ�ȭ
		}
	}
}

void insert_vertex(GraphType*g, int num) {	//������ �����ϴ� �Լ�
	if ((g->n) + 1 > num) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;		//������ ���� ����
}
void insert_edge(GraphType* g, int start, int end, int weight) {//������ �׷����� ������ �����ϴ�  �Լ�
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->weight[start][end] = weight;		//������ �׷����̱� ������ start�� end��
	g->weight[end][start] = weight;		//end�� start�� �� �� ����
}

int get_min_vertex(int n) {	//�ּ� dist[v] ���� ���� ������ ��ȯ�ϴ� �Լ�
	int v, i;

	for (i = 0; i < n; i++) {	//0���� ������ �������� �ݺ�
		if (!selected[i]) { //���� �湮���� �ʾҴٸ� 
			v = i;			//���� �ε����� v�� ��� break;
			break;
		}
	}
	for (i = 0; i < n; i++) {	//0���� ������ �������� �ݺ�
		//������ �湮���� �ʾҰ�, ���� ����ġ���� �� ���� ����ġ�� �ִٸ� v�� ������Ʈ
		if (!selected[i] && (distance[i] < distance[v]))v = i;	//������ �����߿� �ּ� distance�� ã��
	}
	return v;	//v����
}
void prim(GraphType*g, int s) {	//Prim �ּ� ��� ���� Ʈ�� �Լ�
	int i, u, v;
	int *ary;
	int sum = 0;

	ary = (int*)malloc(sizeof(int)*g->n);	//������ ������ ary���� �����Ҵ�
	printf("-Prim�� �ּ� ��� ���� Ʈ�� ���α׷�-\n\n");
	printf(">> ����\n");
	for (u = 0; u < g->n; u++)
		distance[u] = INF;	//��� distance���� INF�� �ʱ�ȭ
	distance[s] = 0;		//���� ������ distance���� 0 ����
	
	for (i = 0; i < g->n; i++) {

		u = get_min_vertex(g->n);	//�ּ� distance�� u�� ����

		selected[u] = TRUE;	//���� ������ �湮�Ǿ��ٰ� ǥ��
		if (distance[u] == INF) return;	//distance���� INF�̸� return

		ary[i] = u;			//ary�� �ּ� ���� ���� u�� ����
		sum += distance[u];	//sum�� disance���� ���س���
		
		
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {	//weight���� INF�� �ƴ϶��
				//���� ������ �湮���� �ʾҰ� weight���� distance���� �۴ٸ�
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];	//distance���� wegiht�� ������Ʈ

				}
			}
		}
		
		
		printf("%d >> ", i+1);
		for (v = 0; v <= i; v++) {
			printf("%d ", ary[v]);	//i�� ������ŭ ���� ���
		}
		printf(": %d\n", sum);	//���� ���

	}
	printf("\n<�ʿ��� �ּ� ��� : %d>", sum);
	free(ary);
}
void Delete(GraphType*g) {		//�޸� ���� �Լ�
	int i;
	for (i = 0; i < g->n; i++) {
		free(g->weight[i]);		//�׷��� �� ����
	}
	free(g->weight);		//�׷��� �� ����
	free(g);				//�׷��� ����
	free(distance);		//distance���� �޸� ����
	free(selected);		//selected���� �޸� ����
}